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
 int /*<<< orphan*/  GL_SYNC_GPU_COMMANDS_COMPLETE ; 
 int /*<<< orphan*/  glClientWaitSync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glDeleteSync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glFenceSync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void gl2_renderchain_fence_iterate(
      void *data,
      gl2_renderchain_data_t *chain,
      unsigned hard_sync_frames)
{
#ifndef HAVE_OPENGLES
#ifdef HAVE_GL_SYNC
   chain->fences[chain->fence_count++] =
      glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);

   while (chain->fence_count > hard_sync_frames)
   {
      glClientWaitSync(chain->fences[0],
            GL_SYNC_FLUSH_COMMANDS_BIT, 1000000000);
      glDeleteSync(chain->fences[0]);

      chain->fence_count--;
      memmove(chain->fences, chain->fences + 1,
            chain->fence_count * sizeof(void*));
   }
#endif
#endif
}