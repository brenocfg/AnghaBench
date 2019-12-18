#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  list_pending; int /*<<< orphan*/  list_free; } ;
struct TYPE_6__ {int /*<<< orphan*/  timer; int /*<<< orphan*/  event; TYPE_1__ request; int /*<<< orphan*/  clock; } ;
typedef  TYPE_2__ MMAL_CLOCK_PRIVATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  mmal_clock_request_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmal_clock_stop_thread (TYPE_2__*) ; 
 int /*<<< orphan*/  mmal_clock_timer_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmal_list_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_semaphore_delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mmal_clock_destroy_scheduling(MMAL_CLOCK_PRIVATE_T *private)
{
   mmal_clock_stop_thread(private);

   mmal_clock_request_flush(&private->clock);

   mmal_list_destroy(private->request.list_free);
   mmal_list_destroy(private->request.list_pending);

   vcos_semaphore_delete(&private->event);

   mmal_clock_timer_destroy(&private->timer);
}