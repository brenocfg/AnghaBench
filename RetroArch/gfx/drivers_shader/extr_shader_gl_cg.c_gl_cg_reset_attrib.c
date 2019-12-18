#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int attribs_index; int /*<<< orphan*/ * attribs_elems; } ;
typedef  TYPE_1__ cg_shader_data_t ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cgGLDisableClientState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  retro_assert (int) ; 

__attribute__((used)) static void gl_cg_reset_attrib(void *data)
{
   unsigned i;
   cg_shader_data_t *cg = (cg_shader_data_t*)data;

   /* Add sanity check that we did not overflow. */
   retro_assert(cg->attribs_index <= ARRAY_SIZE(cg->attribs_elems));

   for (i = 0; i < cg->attribs_index; i++)
      cgGLDisableClientState(cg->attribs_elems[i]);
   cg->attribs_index = 0;
}