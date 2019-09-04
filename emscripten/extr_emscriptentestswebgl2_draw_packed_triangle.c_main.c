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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  pos_and_color ;
struct TYPE_4__ {int majorVersion; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  TYPE_1__ EmscriptenWebGLContextAttributes ;
typedef  scalar_t__ EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_FRAGMENT_SHADER ; 
 int /*<<< orphan*/  GL_INT_2_10_10_10_REV ; 
 scalar_t__ GL_NO_ERROR ; 
 int /*<<< orphan*/  GL_STATIC_DRAW ; 
 int /*<<< orphan*/  GL_TRIANGLES ; 
 int /*<<< orphan*/  GL_TRUE ; 
 int /*<<< orphan*/  GL_UNSIGNED_INT_2_10_10_10_REV ; 
 int /*<<< orphan*/  GL_VERTEX_SHADER ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  compile_shader (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  create_program (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ emscripten_webgl_create_context (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  emscripten_webgl_init_context_attributes (TYPE_1__*) ; 
 int /*<<< orphan*/  emscripten_webgl_make_context_current (scalar_t__) ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBufferData (int /*<<< orphan*/ ,int,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClearColor (float,float,float,int) ; 
 int /*<<< orphan*/  glDrawArrays (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glEnableVertexAttribArray (int) ; 
 int /*<<< orphan*/  glGenBuffers (int,int /*<<< orphan*/ *) ; 
 scalar_t__ glGetError () ; 
 int /*<<< orphan*/  glUseProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glVertexAttribPointer (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*) ; 

int main()
{
  EmscriptenWebGLContextAttributes attr;
  emscripten_webgl_init_context_attributes(&attr);
#ifdef EXPLICIT_SWAP
  attr.explicitSwapControl = 1;
#endif
  attr.majorVersion = 2;
  EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx = emscripten_webgl_create_context("#canvas", &attr);
  assert(ctx && "Failed to create WebGL2 context");
  emscripten_webgl_make_context_current(ctx);

  static const char vertex_shader[] =
    "#version 100\n"
    "attribute vec4 apos;"
    "attribute vec4 acolor;"
    "varying vec4 color;"
    "void main() {"
      "color = acolor;"
      "gl_Position = apos;"
    "}";
  GLuint vs = compile_shader(GL_VERTEX_SHADER, vertex_shader);

  static const char fragment_shader[] =
    "#version 100\n"
    "precision lowp float;"
    "varying vec4 color;"
    "void main() {"
      "gl_FragColor = color;"
    "}";
  GLuint fs = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);

  GLuint program = create_program(vs, fs);
  glUseProgram(program);

  static const uint32_t pos_and_color[] = {
  //  1,0,y,x,    a,b,g,r
    0x400b36cd, 0xc00003ff,
    0x400b3533, 0xc00ffc00,
    0x4004cc00, 0xfff00000,
  };

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(pos_and_color), pos_and_color, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 4, GL_INT_2_10_10_10_REV, GL_TRUE, 8, 0);
  assert(glGetError() == GL_NO_ERROR && "glVertexAttribPointer with GL_INT_2_10_10_10_REV failed");
  glVertexAttribPointer(1, 4, GL_UNSIGNED_INT_2_10_10_10_REV, GL_TRUE, 8, (void*)4);
  assert(glGetError() == GL_NO_ERROR && "glVertexAttribPointer with GL_UNSIGNED_INT_2_10_10_10_REV failed");

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

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