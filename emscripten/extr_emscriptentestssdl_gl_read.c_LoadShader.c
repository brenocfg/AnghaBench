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
typedef  int /*<<< orphan*/  GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  GL_COMPILE_STATUS ; 
 int /*<<< orphan*/  GL_INFO_LOG_LENGTH ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  glCompileShader (scalar_t__) ; 
 scalar_t__ glCreateShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDeleteShader (scalar_t__) ; 
 int /*<<< orphan*/  glGetShaderInfoLog (scalar_t__,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  glGetShaderiv (scalar_t__,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  glShaderSource (scalar_t__,int,char const**,int /*<<< orphan*/ *) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

GLuint LoadShader ( GLenum type, const char *shaderSrc )
{
   GLuint shader;
   GLint compiled;
   
   shader = glCreateShader ( type );
   if ( shader == 0 )
   	return 0;

   glShaderSource ( shader, 1, &shaderSrc, NULL );
   glCompileShader ( shader );
   glGetShaderiv ( shader, GL_COMPILE_STATUS, &compiled );
   if ( !compiled ) 
   {
      GLint infoLen = 0;
      glGetShaderiv ( shader, GL_INFO_LOG_LENGTH, &infoLen );
      if ( infoLen > 1 )
      {
         char* infoLog = malloc (sizeof(char) * infoLen );
         glGetShaderInfoLog ( shader, infoLen, NULL, infoLog );
         printf ( "Error compiling shader:\n%s\n", infoLog );            
         free ( infoLog );
      }
      glDeleteShader ( shader );
      return 0;
   }
   return shader;
}