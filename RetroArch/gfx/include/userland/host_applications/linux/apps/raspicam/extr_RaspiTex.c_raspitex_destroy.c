#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  completed_sem; int /*<<< orphan*/  start_sem; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* close ) (TYPE_3__*) ;int /*<<< orphan*/  (* destroy_native_window ) (TYPE_3__*) ;} ;
struct TYPE_9__ {TYPE_2__ capture; TYPE_1__ ops; int /*<<< orphan*/ * preview_queue; int /*<<< orphan*/ * preview_pool; } ;
typedef  TYPE_3__ RASPITEX_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 int /*<<< orphan*/  mmal_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmal_queue_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_semaphore_delete (int /*<<< orphan*/ *) ; 

void raspitex_destroy(RASPITEX_STATE *state)
{
   vcos_log_trace("%s", VCOS_FUNCTION);
   if (state->preview_pool)
   {
      mmal_pool_destroy(state->preview_pool);
      state->preview_pool = NULL;
   }

   if (state->preview_queue)
   {
      mmal_queue_destroy(state->preview_queue);
      state->preview_queue = NULL;
   }

   if (state->ops.destroy_native_window)
      state->ops.destroy_native_window(state);

   if (state->ops.close)
      state->ops.close(state);

   vcos_semaphore_delete(&state->capture.start_sem);
   vcos_semaphore_delete(&state->capture.completed_sem);
}