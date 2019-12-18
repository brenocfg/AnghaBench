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
struct TYPE_3__ {int /*<<< orphan*/ * orig_task_timer_expiration_routine; int /*<<< orphan*/  task_timer; int /*<<< orphan*/  task_timer_created; } ;
typedef  TYPE_1__ VCOS_THREAD_T ;

/* Variables and functions */
 TYPE_1__* vcos_thread_current () ; 
 int /*<<< orphan*/  vcos_timer_cancel (int /*<<< orphan*/ *) ; 

void _vcos_task_timer_cancel(void)
{
   VCOS_THREAD_T *thread = vcos_thread_current();

   if (thread == NULL || !thread->task_timer_created)
     return;

   vcos_timer_cancel(&thread->task_timer);
   thread->orig_task_timer_expiration_routine = NULL;
}