#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {size_t size; int /*<<< orphan*/  completed_sem; scalar_t__ request; int /*<<< orphan*/ * buffer; } ;
struct TYPE_6__ {scalar_t__ (* capture ) (TYPE_3__*,int /*<<< orphan*/ **,size_t*) ;} ;
struct TYPE_8__ {TYPE_2__ capture; TYPE_1__ ops; } ;
typedef  TYPE_3__ RASPITEX_STATE ;

/* Variables and functions */
 scalar_t__ stub1 (TYPE_3__*,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  vcos_semaphore_post (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void raspitex_do_capture(RASPITEX_STATE *state)
{
   uint8_t *buffer = NULL;
   size_t size = 0;

   if (state->capture.request)
   {
      if (state->ops.capture(state, &buffer, &size) == 0)
      {
         /* Pass ownership of buffer to main thread via capture state */
         state->capture.buffer = buffer;
         state->capture.size = size;
      }
      else
      {
         state->capture.buffer = NULL; // Null indicates an error
         state->capture.size = 0;
      }

      state->capture.request = 0; // Always clear request and post sem
      vcos_semaphore_post(&state->capture.completed_sem);
   }
}