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
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_COMPILE_STATUS ; 
 int /*<<< orphan*/  GL_FRAGMENT_SHADER ; 
 int /*<<< orphan*/  GL_LINK_STATUS ; 
 int /*<<< orphan*/  GL_VERTEX_SHADER ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glAttachShader (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glCompileShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glCreateProgram () ; 
 int /*<<< orphan*/  glCreateShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGetProgramiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glGetShaderiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glLinkProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glShaderSource (int /*<<< orphan*/ ,int,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glUseProgram (int /*<<< orphan*/ ) ; 

void shaders() {
#if USE_GLEW
  glewInit();
#endif

  GLint ok;

  const char *vertexShader = "void main(void) \n"
                             "{ \n"
                             "    gl_Position = ftransform(); \n"
                             "    gl_TexCoord[0] = gl_MultiTexCoord0; \n"
                             "    gl_FrontColor = gl_Color; \n"
                             "} \n";
  const char *fragmentShader = "uniform sampler2D tex0; \n"
                               "void main(void) \n"
                               "{ \n"
                               "    gl_FragColor = gl_Color * texture2D(tex0, gl_TexCoord[0].xy); \n"
                               "} \n";

  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vertexShader, NULL);
  glCompileShader(vs);
  glGetShaderiv(vs, GL_COMPILE_STATUS, &ok);
  assert(ok);

  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fragmentShader, NULL);
  glCompileShader(fs);
  glGetShaderiv(fs, GL_COMPILE_STATUS, &ok);
  assert(ok);

  GLuint program = glCreateProgram();

  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &ok);
  assert(ok);

  glUseProgram(program);
}