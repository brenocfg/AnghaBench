#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  OSTime ;

/* Variables and functions */
 int /*<<< orphan*/  OSGetSystemTime () ; 
 int runloop_iterate () ; 
 int /*<<< orphan*/ * swap_is_pending ; 
 int /*<<< orphan*/  task_queue_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ video_driver_get_ptr (int) ; 

__attribute__((used)) static void main_loop(void)
{
   OSTime start_time;
   int status;

   do
   {
      if(video_driver_get_ptr(false))
      {
         start_time = OSGetSystemTime();
         task_queue_wait(swap_is_pending, &start_time);
      }
      else
         task_queue_wait(NULL, NULL);

      status = runloop_iterate();

      if (status == -1)
         break;
   } while(true);
}