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
typedef  int /*<<< orphan*/  pos_and_idx ;
struct TYPE_4__ {int majorVersion; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  TYPE_1__ EmscriptenWebGLContextAttributes ;
typedef  int /*<<< orphan*/  EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_FLOAT ; 
 int /*<<< orphan*/  GL_FRAGMENT_SHADER ; 
 int /*<<< orphan*/  GL_INT ; 
 int /*<<< orphan*/  GL_STATIC_DRAW ; 
 int /*<<< orphan*/  GL_TRIANGLES ; 
 int /*<<< orphan*/  GL_VERTEX_SHADER ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  compile_shader (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  create_program (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_webgl_create_context (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  emscripten_webgl_init_context_attributes (TYPE_1__*) ; 
 int /*<<< orphan*/  emscripten_webgl_make_context_current (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBufferData (int /*<<< orphan*/ ,int,struct P const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClearColor (float,float,float,int) ; 
 int /*<<< orphan*/  glDrawArrays (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glEnableVertexAttribArray (int) ; 
 int /*<<< orphan*/  glGenBuffers (int,int /*<<< orphan*/ *) ; 
 int glGetUniformLocation (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  glUniform4fv (int,int,float*) ; 
 int /*<<< orphan*/  glUseProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glVertexAttribIPointer (int,int,int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/  glVertexAttribPointer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int main()
{
  EmscriptenWebGLContextAttributes attr;
  emscripten_webgl_init_context_attributes(&attr);
  attr.majorVersion = 2;
  EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx = emscripten_webgl_create_context("#canvas", &attr);
  emscripten_webgl_make_context_current(ctx);

  static const char vertex_shader[] =
    "#version 300 es\n"
    "in vec4 apos;\n"
    "in int idx;\n"
    "struct S { vec4 color; };\n"
    "uniform S colors[3];\n"
    "out vec4 color;\n"
    "void main() {\n"
      "color = colors[idx].color;\n"
      "gl_Position = apos;\n"
    "}\n";
  GLuint vs = compile_shader(GL_VERTEX_SHADER, vertex_shader);

  static const char fragment_shader[] =
    "#version 300 es\n"
    "precision lowp float;\n"
    "in vec4 color;\n"
    "out vec4 fragColor;\n"
    "void main() {\n"
      "fragColor = color;\n"
    "}\n";
  GLuint fs = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);

  GLuint program = create_program(vs, fs);
  glUseProgram(program);

  struct P
  {
    float x, y;
    int idx;
  };

  static const struct P pos_and_idx[] = {
     { -0.6f, -0.6f, 0 },
     {  0.6f, -0.6f, 1 },
     {  0.f,   0.6f, 2 }
  };

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(pos_and_idx), pos_and_idx, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 12, 0);
  glVertexAttribIPointer(1, 1, GL_INT, 12, (void*)8);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  float red[4]   = { 1.0f, 0.f, 0.0f, 1.0f };
  float green[4] = { 0.0f, 1.f, 0.0f, 1.0f };
  float blue[4]  = { 0.0f, 0.f, 1.0f, 1.0f };
  int loc = glGetUniformLocation(program, "colors[0].color");
  assert(loc >= 0);
  glUniform4fv(loc, 1, red);
  loc = glGetUniformLocation(program, "colors[1].color");
  assert(loc >= 0);
  glUniform4fv(loc, 1, green);
  loc = glGetUniformLocation(program, "colors[2].color");
  assert(loc >= 0);
  glUniform4fv(loc, 1, blue);
  glClearColor(0.3f,0.3f,0.3f,1);
  glClear(GL_COLOR_BUFFER_BIT);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}