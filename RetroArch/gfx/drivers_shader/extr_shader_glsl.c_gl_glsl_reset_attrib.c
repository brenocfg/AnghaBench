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
struct TYPE_3__ {unsigned int attribs_index; int /*<<< orphan*/ * attribs_elems; } ;
typedef  TYPE_1__ glsl_shader_data_t ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glDisableVertexAttribArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  retro_assert (int) ; 

__attribute__((used)) static void gl_glsl_reset_attrib(glsl_shader_data_t *glsl)
{
   unsigned i;

   /* Add sanity check that we did not overflow. */
   retro_assert(glsl->attribs_index <= ARRAY_SIZE(glsl->attribs_elems));

   for (i = 0; i < glsl->attribs_index; i++)
      glDisableVertexAttribArray(glsl->attribs_elems[i]);
   glsl->attribs_index = 0;
}