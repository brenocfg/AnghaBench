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
struct sched_param {int dummy; } ;
typedef  TYPE_1__* pthread_t ;
struct TYPE_3__ {int /*<<< orphan*/  killlock; int /*<<< orphan*/  tid; scalar_t__ dead; } ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  SYS_sched_setscheduler ; 
 int /*<<< orphan*/  __lock (int /*<<< orphan*/ ) ; 
 int __syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct sched_param const*) ; 
 int /*<<< orphan*/  __unlock (int /*<<< orphan*/ ) ; 

int pthread_setschedparam(pthread_t t, int policy, const struct sched_param *param)
{
	int r;
	__lock(t->killlock);
	r = t->dead ? ESRCH : -__syscall(SYS_sched_setscheduler, t->tid, policy, param);
	__unlock(t->killlock);
	return r;
}