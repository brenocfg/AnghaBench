#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* orig_task_timer_expiration_routine ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  orig_task_timer_context; } ;
typedef  TYPE_1__ VCOS_THREAD_T ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_assert (int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 

__attribute__((used)) static void _task_timer_expiration_routine(void *cxt)
{
   VCOS_THREAD_T *thread = (VCOS_THREAD_T *)cxt;

   vcos_assert(thread->orig_task_timer_expiration_routine);
   thread->orig_task_timer_expiration_routine(thread->orig_task_timer_context);
   thread->orig_task_timer_expiration_routine = NULL;
}