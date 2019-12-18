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
struct TYPE_3__ {unsigned int fence_count; int /*<<< orphan*/ * fences; } ;
typedef  TYPE_1__ gl2_renderchain_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  GL_SYNC_FLUSH_COMMANDS_BIT ; 
 int /*<<< orphan*/  glClientWaitSync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glDeleteSync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gl2_renderchain_fence_free(void *data,
      gl2_renderchain_data_t *chain)
{
#ifndef HAVE_OPENGLES
#ifdef HAVE_GL_SYNC
   unsigned i;

   for (i = 0; i < chain->fence_count; i++)
   {
      glClientWaitSync(chain->fences[i],
            GL_SYNC_FLUSH_COMMANDS_BIT, 1000000000);
      glDeleteSync(chain->fences[i]);
   }
   chain->fence_count = 0;
#endif
#endif
}