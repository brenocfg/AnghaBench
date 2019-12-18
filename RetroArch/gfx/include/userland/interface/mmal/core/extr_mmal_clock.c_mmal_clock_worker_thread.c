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
struct TYPE_3__ {scalar_t__ stop_thread; int /*<<< orphan*/  timer; int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ MMAL_CLOCK_PRIVATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  mmal_clock_process_requests (TYPE_1__*) ; 
 int /*<<< orphan*/  mmal_clock_timer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_semaphore_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void* mmal_clock_worker_thread(void *ctx)
{
   MMAL_CLOCK_PRIVATE_T *private = (MMAL_CLOCK_PRIVATE_T*)ctx;

   while (1)
   {
      vcos_semaphore_wait(&private->event);

      /* Either the timer has expired or a new request is pending */
      mmal_clock_timer_cancel(&private->timer);

      if (private->stop_thread)
         break;

      mmal_clock_process_requests(private);
   }
   return NULL;
}