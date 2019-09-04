#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pos ;
struct TYPE_4__ {scalar_t__ alpha; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  TYPE_1__ EmscriptenWebGLContextAttributes ;

/* Variables and functions */
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_BLEND ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_FLOAT ; 
 int /*<<< orphan*/  GL_FRAGMENT_SHADER ; 
 int /*<<< orphan*/  GL_ONE_MINUS_SRC_ALPHA ; 
 int /*<<< orphan*/  GL_RGBA ; 
 int /*<<< orphan*/  GL_SRC_ALPHA ; 
 int /*<<< orphan*/  GL_STATIC_DRAW ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 int /*<<< orphan*/  GL_VERTEX_SHADER ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 void* colorPos ; 
 int /*<<< orphan*/  compile_shader (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  create_program (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_texture () ; 
 double emscripten_get_device_pixel_ratio () ; 
 int /*<<< orphan*/  emscripten_set_canvas_element_size (char*,int,int) ; 
 int /*<<< orphan*/  emscripten_set_element_css_size (char*,int,int) ; 
 int /*<<< orphan*/  emscripten_webgl_create_context (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  emscripten_webgl_init_context_attributes (TYPE_1__*) ; 
 int /*<<< orphan*/  emscripten_webgl_make_context_current (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBlendFunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBufferData (int /*<<< orphan*/ ,int,float const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glContext ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnableVertexAttribArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGenBuffers (int,int /*<<< orphan*/ *) ; 
 void* glGetUniformLocation (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  glTexImage2D (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  glVertexAttribPointer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* matPos ; 
 float pixelHeight ; 
 float pixelWidth ; 
 int /*<<< orphan*/  quad ; 
 int /*<<< orphan*/  solidColor ; 

void init_webgl(int width, int height)
{
  double dpr = emscripten_get_device_pixel_ratio();
  emscripten_set_element_css_size("canvas", width / dpr, height / dpr);
  emscripten_set_canvas_element_size("canvas", width, height);

  EmscriptenWebGLContextAttributes attrs;
  emscripten_webgl_init_context_attributes(&attrs);
  attrs.alpha = 0;
#ifdef USE_WEBGL2
  attrs.majorVersion = 2;
#endif
  glContext = emscripten_webgl_create_context("canvas", &attrs);
  assert(glContext);
  emscripten_webgl_make_context_current(glContext);

  pixelWidth = 2.f / width;
  pixelHeight = 2.f / height;

  static const char vertex_shader[] =
    "attribute vec4 pos;"
    "varying vec2 uv;"
    "uniform mat4 mat;"
    "void main(){"
      "uv=pos.xy;"
      "gl_Position=mat*pos;"
    "}";
  GLuint vs = compile_shader(GL_VERTEX_SHADER, vertex_shader);

  static const char fragment_shader[] =
    "precision lowp float;"
    "uniform sampler2D tex;"
    "varying vec2 uv;"
    "uniform vec4 color;"
    "void main(){"
      "gl_FragColor=color*texture2D(tex,uv);"
    "}";
  GLuint fs = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);

  GLuint program = create_program(vs, fs);
  colorPos = glGetUniformLocation(program, "color");
  matPos = glGetUniformLocation(program, "mat");
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glGenBuffers(1, &quad);
  glBindBuffer(GL_ARRAY_BUFFER, quad);
  const float pos[] = { 0, 0, 1, 0, 0, 1, 1, 1 };
  glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);

  solidColor = create_texture();
  unsigned int whitePixel = 0xFFFFFFFFu;
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &whitePixel);
}