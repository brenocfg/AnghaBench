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
struct TYPE_3__ {int /*<<< orphan*/  task_timer; scalar_t__ task_timer_created; int /*<<< orphan*/  suspend; } ;
typedef  TYPE_1__ VCOS_THREAD_T ;

/* Variables and functions */
 int /*<<< orphan*/  vcos_semaphore_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_timer_delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vcos_thread_cleanup(VCOS_THREAD_T *thread)
{
   vcos_semaphore_delete(&thread->suspend);
   if (thread->task_timer_created)
   {
      vcos_timer_delete(&thread->task_timer);
   }
}