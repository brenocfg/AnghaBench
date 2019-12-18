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
typedef  scalar_t__ thread_t ;
struct uthread {int uu_flag; struct proc* uu_proc; } ;
struct proc {int p_lflag; void* p_vforkact; } ;

/* Variables and functions */
 int P_LINVFORK ; 
 int UT_VFORK ; 
 int /*<<< orphan*/  current_task () ; 
 scalar_t__ current_thread () ; 
 scalar_t__ get_bsdtask_info (int /*<<< orphan*/ ) ; 
 scalar_t__ get_bsdthread_info (scalar_t__) ; 
 struct proc* kernproc ; 
 int /*<<< orphan*/  panic (char*) ; 

struct proc *
current_proc(void)
{
	/* Never returns a NULL */
	struct uthread * ut;
	struct proc * p;
	thread_t thread = current_thread();

	ut = (struct uthread *)get_bsdthread_info(thread);
	if (ut && (ut->uu_flag & UT_VFORK) && ut->uu_proc) {
		p = ut->uu_proc;
		if ((p->p_lflag & P_LINVFORK) == 0)
			panic("returning child proc not under vfork");
		if (p->p_vforkact != (void *)thread)
			panic("returning child proc which is not cur_act");
		return (p);
	}

	p = (struct proc *)get_bsdtask_info(current_task());

	if (p == NULL)
		return (kernproc);

	return (p);
}