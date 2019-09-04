#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  pos_and_color ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  EmscriptenWebGLContextAttributes ;
typedef  int /*<<< orphan*/  EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_FLOAT ; 
 int /*<<< orphan*/  GL_FRAGMENT_SHADER ; 
 int /*<<< orphan*/  GL_STATIC_DRAW ; 
 int /*<<< orphan*/  GL_TRIANGLES ; 
 int /*<<< orphan*/  GL_VERTEX_SHADER ; 
 int /*<<< orphan*/  compile_shader (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  create_program (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_webgl_create_context (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emscripten_webgl_init_context_attributes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emscripten_webgl_make_context_current (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBufferData (int /*<<< orphan*/ ,int,float const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClearColor (float,float,float,int) ; 
 int /*<<< orphan*/  glDrawArrays (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glEnableVertexAttribArray (int) ; 
 int /*<<< orphan*/  glGenBuffers (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glGetUniformLocation (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  glUniform4fv (int /*<<< orphan*/ ,int,float*) ; 
 int /*<<< orphan*/  glUseProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glVertexAttribPointer (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*) ; 

int main()
{
  EmscriptenWebGLContextAttributes attr;
  emscripten_webgl_init_context_attributes(&attr);
#ifdef EXPLICIT_SWAP
  attr.explicitSwapControl = 1;
#endif
#ifdef DRAW_FROM_CLIENT_MEMORY
  // This test verifies that drawing from client-side memory when enableExtensionsByDefault==false works.
  attr.enableExtensionsByDefault = 0;
#endif

  EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx = emscripten_webgl_create_context("#canvas", &attr);
  emscripten_webgl_make_context_current(ctx);

  static const char vertex_shader[] =
    "attribute vec4 apos;"
    "attribute vec4 acolor;"
    "varying vec4 color;"
    "void main() {"
      "color = acolor;"
      "gl_Position = apos;"
    "}";
  GLuint vs = compile_shader(GL_VERTEX_SHADER, vertex_shader);

  static const char fragment_shader[] =
    "precision lowp float;"
    "varying vec4 color;"
    "uniform vec4 color2;"
    "void main() {"
      "gl_FragColor = color*color2;"
    "}";
  GLuint fs = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);

  GLuint program = create_program(vs, fs);
  glUseProgram(program);

  static const float pos_and_color[] = {
  //     x,     y, r, g, b
     -0.6f, -0.6f, 1, 0, 0,
      0.6f, -0.6f, 0, 1, 0,
      0.f,   0.6f, 0, 0, 1,
  };

#ifdef DRAW_FROM_CLIENT_MEMORY
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 20, pos_and_color);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 20, (void*)(pos_and_color+2));
#else
  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(pos_and_color), pos_and_color, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 20, 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 20, (void*)8);
#endif
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  float color2[4] = { 0.0f, 1.f, 0.0f, 1.0f };
  glUniform4fv(glGetUniformLocation(program, "color2"), 1, color2);
  glClearColor(0.3f,0.3f,0.3f,1);
  glClear(GL_COLOR_BUFFER_BIT);
  glDrawArrays(GL_TRIANGLES, 0, 3);

#ifdef EXPLICIT_SWAP
  emscripten_webgl_commit_frame();
#endif

#ifdef REPORT_RESULT
  REPORT_RESULT(0);
#endif
}