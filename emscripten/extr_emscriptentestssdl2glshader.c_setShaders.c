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
 int /*<<< orphan*/  GL_FRAGMENT_SHADER ; 
 int /*<<< orphan*/  GL_OBJECT_COMPILE_STATUS_ARB ; 
 int /*<<< orphan*/  GL_OBJECT_LINK_STATUS_ARB ; 
 int /*<<< orphan*/  GL_VERTEX_SHADER ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glAttachObject_ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glCompileShader_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glCreateProgramObject_ () ; 
 int /*<<< orphan*/  glCreateShaderObject_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGetInfoLog_ (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  glGetObjectParameteriv_ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glLinkProgram_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glShaderSource_ (int /*<<< orphan*/ ,int,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glUseProgramObject_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

void setShaders() {
  GLuint v, f, p;
  GLint ok;

	const char *vv = "void main()                   \n"
                   "{                             \n"
	                 "  gl_Position = ftransform() + vec4(0.1, -0.25, 0, 0); \n"
                   "}";
  const char *ff = "void main()                \n"
                   "{	                         \n"
	                 "  gl_FragColor = vec4(gl_FragCoord.y/480.0, gl_FragCoord.x/640.0, 0.66, 1.0); \n"
                   "}";

	v = glCreateShaderObject_(GL_VERTEX_SHADER);
	f = glCreateShaderObject_(GL_FRAGMENT_SHADER);

	glShaderSource_(v, 1, &vv,NULL);
	glShaderSource_(f, 1, &ff,NULL);

	glCompileShader_(v);
  glGetObjectParameteriv_(v, GL_OBJECT_COMPILE_STATUS_ARB, &ok);
  if (!ok) {
    char msg[512];
    glGetInfoLog_(v, sizeof msg, NULL, msg);
    printf("shader compilation issue: %s\n", msg);
  }
  assert(ok);

	glCompileShader_(f);
  glGetObjectParameteriv_(f, GL_OBJECT_COMPILE_STATUS_ARB, &ok);
  assert(ok);

	p = glCreateProgramObject_();
	glAttachObject_(p,f);
	glAttachObject_(p,v);

	glLinkProgram_(p);
  glGetObjectParameteriv_(p, GL_OBJECT_LINK_STATUS_ARB, &ok);
  assert(ok);

	glUseProgramObject_(p);
}