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
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int /*<<< orphan*/  thread_qos_t ;
struct proc {int dummy; } ;
struct bsdthread_ctl_args {int cmd; scalar_t__ arg2; int /*<<< orphan*/  arg1; int /*<<< orphan*/  arg3; } ;
typedef  int /*<<< orphan*/  pthread_priority_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  enum workq_set_self_flags { ____Placeholder_workq_set_self_flags } workq_set_self_flags ;

/* Variables and functions */
#define  BSDTHREAD_CTL_QOS_DISPATCH_ASYNCHRONOUS_OVERRIDE_ADD 136 
#define  BSDTHREAD_CTL_QOS_DISPATCH_ASYNCHRONOUS_OVERRIDE_RESET 135 
#define  BSDTHREAD_CTL_QOS_MAX_PARALLELISM 134 
#define  BSDTHREAD_CTL_QOS_OVERRIDE_DISPATCH 133 
#define  BSDTHREAD_CTL_QOS_OVERRIDE_END 132 
#define  BSDTHREAD_CTL_QOS_OVERRIDE_RESET 131 
#define  BSDTHREAD_CTL_QOS_OVERRIDE_START 130 
#define  BSDTHREAD_CTL_SET_QOS 129 
#define  BSDTHREAD_CTL_SET_SELF 128 
 int EINVAL ; 
 int ENOTSUP ; 
 int /*<<< orphan*/  ENSURE_UNUSED (int /*<<< orphan*/ ) ; 
 int bsdthread_add_explicit_override (struct proc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bsdthread_get_max_parallelism (int /*<<< orphan*/ ,unsigned long,int*) ; 
 int bsdthread_remove_explicit_override (struct proc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bsdthread_set_self (struct proc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  current_thread () ; 
 int workq_thread_add_dispatch_override (struct proc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int workq_thread_reset_dispatch_override (struct proc*,int /*<<< orphan*/ ) ; 

int
bsdthread_ctl(struct proc *p, struct bsdthread_ctl_args *uap, int *retval)
{
	switch (uap->cmd) {
	case BSDTHREAD_CTL_QOS_OVERRIDE_START:
		return bsdthread_add_explicit_override(p, (mach_port_name_t)uap->arg1,
				(pthread_priority_t)uap->arg2, uap->arg3);
	case BSDTHREAD_CTL_QOS_OVERRIDE_END:
		ENSURE_UNUSED(uap->arg3);
		return bsdthread_remove_explicit_override(p, (mach_port_name_t)uap->arg1,
				(user_addr_t)uap->arg2);

	case BSDTHREAD_CTL_QOS_OVERRIDE_DISPATCH:
		return workq_thread_add_dispatch_override(p, (mach_port_name_t)uap->arg1,
				(pthread_priority_t)uap->arg2, uap->arg3);
	case BSDTHREAD_CTL_QOS_OVERRIDE_RESET:
		return workq_thread_reset_dispatch_override(p, current_thread());

	case BSDTHREAD_CTL_SET_SELF:
		return bsdthread_set_self(p, current_thread(),
				(pthread_priority_t)uap->arg1, (mach_port_name_t)uap->arg2,
				(enum workq_set_self_flags)uap->arg3);

	case BSDTHREAD_CTL_QOS_MAX_PARALLELISM:
		ENSURE_UNUSED(uap->arg3);
		return bsdthread_get_max_parallelism((thread_qos_t)uap->arg1,
				(unsigned long)uap->arg2, retval);

	case BSDTHREAD_CTL_SET_QOS:
	case BSDTHREAD_CTL_QOS_DISPATCH_ASYNCHRONOUS_OVERRIDE_ADD:
	case BSDTHREAD_CTL_QOS_DISPATCH_ASYNCHRONOUS_OVERRIDE_RESET:
		/* no longer supported */
		return ENOTSUP;

	default:
		return EINVAL;
	}
}