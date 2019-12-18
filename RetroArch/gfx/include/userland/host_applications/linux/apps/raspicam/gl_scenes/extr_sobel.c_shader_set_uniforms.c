#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * attribute_locations; int /*<<< orphan*/ * uniform_locations; int /*<<< orphan*/  program; } ;
typedef  TYPE_1__ RASPITEXUTIL_SHADER_PROGRAM_T ;

/* Variables and functions */
 int /*<<< orphan*/  GLCHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnableVertexAttribArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUniform1i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUniform2f (int /*<<< orphan*/ ,double,double) ; 
 int /*<<< orphan*/  glUseProgram (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int shader_set_uniforms(RASPITEXUTIL_SHADER_PROGRAM_T *shader,
      int width, int height)
{
   GLCHK(glUseProgram(shader->program));
   GLCHK(glUniform1i(shader->uniform_locations[0], 0)); // Texture unit

   /* Dimensions of a single pixel in texture co-ordinates */
   GLCHK(glUniform2f(shader->uniform_locations[1],
            1.0 / (float) width, 1.0 / (float) height));

   /* Enable attrib 0 as vertex array */
   GLCHK(glEnableVertexAttribArray(shader->attribute_locations[0]));
   return 0;
}