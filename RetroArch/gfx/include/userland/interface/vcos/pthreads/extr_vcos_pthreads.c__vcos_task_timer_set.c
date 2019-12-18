#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VCOS_UNSIGNED ;
struct TYPE_4__ {void (* orig_task_timer_expiration_routine ) (void*) ;int task_timer_created; int /*<<< orphan*/  task_timer; void* orig_task_timer_context; } ;
typedef  TYPE_1__ VCOS_THREAD_T ;
typedef  scalar_t__ VCOS_STATUS_T ;

/* Variables and functions */
 scalar_t__ VCOS_SUCCESS ; 
 int /*<<< orphan*/  _task_timer_expiration_routine ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 TYPE_1__* vcos_thread_current () ; 
 scalar_t__ vcos_timer_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  vcos_timer_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void _vcos_task_timer_set(void (*pfn)(void*), void *cxt, VCOS_UNSIGNED ms)
{
   VCOS_THREAD_T *thread = vcos_thread_current();

   if (thread == NULL)
      return;

   vcos_assert(thread->orig_task_timer_expiration_routine == NULL);

   if (!thread->task_timer_created)
   {
      VCOS_STATUS_T st = vcos_timer_create(&thread->task_timer, NULL,
                                _task_timer_expiration_routine, thread);
      (void)st;
      vcos_assert(st == VCOS_SUCCESS);
      thread->task_timer_created = 1;
   }

   thread->orig_task_timer_expiration_routine = pfn;
   thread->orig_task_timer_context = cxt;

   vcos_timer_set(&thread->task_timer, ms);
}