/**
 * TextureShader
 *
 * Simple texture shader
 */
open Revery_Shaders;
open Revery_Shaders.Shader;

let attribute: list(ShaderAttribute.t) =
  SolidShader.attribute
  @ [
    {
      dataType: ShaderDataType.Vector2,
      name: "aTexCoord",
      channel: TextureCoordinate,
    },
  ];

let uniform: list(ShaderUniform.t) =
  SolidShader.uniform
  @ [
    {
      dataType: ShaderDataType.Sampler2D,
      name: "uSampler",
      usage: FragmentShader,
    },
    {
      dataType: ShaderDataType.Vector2,
      name: "uAtlasOrigin",
      usage: FragmentShader,
    },
    {
      dataType: ShaderDataType.Vector2,
      name: "uAtlasSize",
      usage: FragmentShader,
    },
  ];

let varying =
  SolidShader.varying
  @ [
    {
      dataType: ShaderDataType.Vector2,
      name: "vTexCoord",
      precision: ShaderPrecision.Low,
    },
  ];

let vsShader = SolidShader.vsShader ++ "\n" ++ {|
   vTexCoord = aTexCoord;
|};

let fsShader = {|
    vec4 t = texture2D(uSampler, uAtlasOrigin + uAtlasSize * vTexCoord);
    gl_FragColor = vec4(vColor.r, vColor.g, vColor.b, t.a * vColor.a);
|};

let create = () => {
  let shader =
    Shader.create(
      ~attributes=attribute,
      ~uniforms=uniform,
      ~varying,
      ~vertexShader=vsShader,
      ~fragmentShader=fsShader,
    );
  Shader.compile(shader);
};