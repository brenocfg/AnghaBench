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
struct TYPE_2__ {int /*<<< orphan*/ * cgCtx; } ;
typedef  TYPE_1__ cg_shader_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*) ; 
 int /*<<< orphan*/  cgDestroyContext (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gl_cg_deinit_context_state(void *data)
{
   cg_shader_data_t *cg = (cg_shader_data_t*)data;
   if (cg->cgCtx)
   {
      RARCH_LOG("[CG]: Destroying context.\n");
      cgDestroyContext(cg->cgCtx);
   }
   cg->cgCtx = NULL;
}