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
typedef  scalar_t__ GLint ;
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  GL_COMPILE_STATUS ; 
 int /*<<< orphan*/  GL_INFO_LOG_LENGTH ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  glCompileShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glCreateShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGetShaderInfoLog (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,char*) ; 
 int /*<<< orphan*/  glGetShaderiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  glShaderSource (int /*<<< orphan*/ ,int,char const**,int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

GLuint compile_shader(GLenum shaderType, const char *src)
{
  GLuint shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, &src, NULL);
  glCompileShader(shader);

  GLint isCompiled = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
  if (!isCompiled)
  {
    GLint maxLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
    char *buf = (char*)malloc(maxLength+1);
    glGetShaderInfoLog(shader, maxLength, &maxLength, buf);
    printf("%s\n", buf);
    free(buf);
    return 0;
  }

   return shader;
}