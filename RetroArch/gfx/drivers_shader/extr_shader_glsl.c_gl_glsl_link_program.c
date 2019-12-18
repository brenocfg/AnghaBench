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

/* Variables and functions */
 int /*<<< orphan*/  GL_LINK_STATUS ; 
 scalar_t__ GL_TRUE ; 
 int /*<<< orphan*/  glGetProgramiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  glLinkProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUseProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_glsl_print_linker_log (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool gl_glsl_link_program(GLuint prog)
{
   GLint status;

   glLinkProgram(prog);

   glGetProgramiv(prog, GL_LINK_STATUS, &status);
   gl_glsl_print_linker_log(prog);

   if (status != GL_TRUE)
      return false;

   glUseProgram(prog);
   return true;
}