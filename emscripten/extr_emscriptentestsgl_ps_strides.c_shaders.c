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
typedef  scalar_t__ GLuint ;
typedef  int GLint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_COMPILE_STATUS ; 
 int /*<<< orphan*/  GL_FRAGMENT_SHADER ; 
 int /*<<< orphan*/  GL_INFO_LOG_LENGTH ; 
 int /*<<< orphan*/  GL_LINK_STATUS ; 
 int /*<<< orphan*/  GL_VERTEX_SHADER ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  glAttachShader (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  glCompileShader (scalar_t__) ; 
 scalar_t__ glCreateProgram () ; 
 scalar_t__ glCreateShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGetProgramiv (scalar_t__,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  glGetShaderiv (scalar_t__,int /*<<< orphan*/ ,int*) ; 
 int glIsProgram (scalar_t__) ; 
 int /*<<< orphan*/  glLinkProgram (scalar_t__) ; 
 int /*<<< orphan*/  glShaderSource (scalar_t__,int,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glUseProgram (scalar_t__) ; 

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
  assert(glIsProgram(program));
  assert(!glIsProgram(0));
  assert(!glIsProgram(program+1)); // a number that can't be a real shader

  glUseProgram(program);

  {
    // Also, check getting the error log
    const char *fakeVertexShader = "atbute ve4 blarg; ### AAA\n";
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &fakeVertexShader, NULL);
    glCompileShader(vs);
    glGetShaderiv(vs, GL_COMPILE_STATUS, &ok);
    assert(!ok);
    GLint infoLen = 0;
    glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &infoLen);
    assert(infoLen > 1);
  }
}