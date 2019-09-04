#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct start_args {int /*<<< orphan*/  b; TYPE_2__* sev; } ;
typedef  TYPE_3__* pthread_t ;
struct TYPE_7__ {void* (* start ) (void*) ;int timer_id; int /*<<< orphan*/  start_arg; } ;
struct TYPE_5__ {int /*<<< orphan*/  sival_ptr; } ;
struct TYPE_6__ {TYPE_1__ sigev_value; scalar_t__ sigev_notify_function; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGTIMER_SET ; 
 int /*<<< orphan*/  SIG_UNBLOCK ; 
 int /*<<< orphan*/  SYS_rt_sigprocmask ; 
 int /*<<< orphan*/  SYS_timer_delete ; 
 int _NSIG ; 
 TYPE_3__* __pthread_self () ; 
 int /*<<< orphan*/  __syscall (int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  __wait (int*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pthread_barrier_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *start(void *arg)
{
	pthread_t self = __pthread_self();
	struct start_args *args = arg;
	int id;

	/* Reuse no-longer-needed thread structure fields to avoid
	 * needing the timer address in the signal handler. */
	self->start = (void *(*)(void *))args->sev->sigev_notify_function;
	self->start_arg = args->sev->sigev_value.sival_ptr;

	pthread_barrier_wait(&args->b);
	if ((id = self->timer_id) >= 0) {
		__syscall(SYS_rt_sigprocmask, SIG_UNBLOCK,
			SIGTIMER_SET, 0, _NSIG/8);
		__wait(&self->timer_id, 0, id, 1);
		__syscall(SYS_timer_delete, id);
	}
	return 0;
}