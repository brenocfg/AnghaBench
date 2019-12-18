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
struct task_struct {int dummy; } ;
typedef  int /*<<< orphan*/  compat_long_t ;

/* Variables and functions */
 long EPERM ; 
#define  PPC_PTRACE_GETREGS 129 
#define  PPC_PTRACE_SETREGS 128 
 int /*<<< orphan*/  compat_ptr (long) ; 
 long copy_regset_from_user (struct task_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 long copy_regset_to_user (struct task_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  task_user_regset_view (int /*<<< orphan*/ ) ; 

__attribute__((used)) static long compat_ptrace_old(struct task_struct *child, long request,
			      long addr, long data)
{
	switch (request) {
	case PPC_PTRACE_GETREGS:	/* Get GPRs 0 - 31. */
		return copy_regset_to_user(child,
					   task_user_regset_view(current), 0,
					   0, 32 * sizeof(compat_long_t),
					   compat_ptr(data));

	case PPC_PTRACE_SETREGS:	/* Set GPRs 0 - 31. */
		return copy_regset_from_user(child,
					     task_user_regset_view(current), 0,
					     0, 32 * sizeof(compat_long_t),
					     compat_ptr(data));
	}

	return -EPERM;
}