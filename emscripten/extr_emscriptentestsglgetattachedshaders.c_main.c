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
typedef  int GLsizei ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FRAGMENT_SHADER ; 
 int /*<<< orphan*/  GL_VERTEX_SHADER ; 
 int /*<<< orphan*/  REPORT_RESULT (int) ; 
 int /*<<< orphan*/  create_context () ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  glAttachShader (scalar_t__,scalar_t__) ; 
 scalar_t__ glCreateProgram () ; 
 scalar_t__ glCreateShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGetAttachedShaders (scalar_t__,int,int*,scalar_t__*) ; 
 scalar_t__ glGetError () ; 

int main(int argc, char *argv[])
{
   unsigned i;

   create_context();

   GLuint prog = glCreateProgram();
   if (glGetError())
      die("failed to create program");

   GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
   if (glGetError())
      die("failed to create vertex shader");
   glAttachShader(prog, vertex);

   GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
   if (glGetError())
      die("failed to create fragment shader");
   glAttachShader(prog, fragment);

   GLuint shaders[2];
   GLsizei count;

   glGetAttachedShaders(prog, 2, &count, shaders);
   if (glGetError())
      die("failed to get attached shaders");
   if (count != 2)
      die("unknown number of shaders returned");
   if (shaders[0] == shaders[1])
      die("returned identical shaders");

   for (i = 0; i < count; i++)
   {
      if (shaders[i] == 0)
         die("returned 0");
      if (shaders[i] != vertex && shaders[i] != fragment)
         die("unknown shader returned");
   }

   REPORT_RESULT(1);

   return 0;
}