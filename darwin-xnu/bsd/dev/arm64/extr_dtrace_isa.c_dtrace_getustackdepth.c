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
typedef  int /*<<< orphan*/ * thread_t ;
typedef  int /*<<< orphan*/  savearea_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_DTRACE_ENTRY ; 
 int /*<<< orphan*/  CPU_DTRACE_FAULT ; 
 scalar_t__ DTRACE_CPUFLAG_ISSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * current_thread () ; 
 scalar_t__ dtrace_getustack_common (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ find_user_regs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_saved_state_fp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_saved_state_lr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_saved_state_pc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_saved_state_sp (int /*<<< orphan*/ *) ; 

int
dtrace_getustackdepth(void)
{
	thread_t        thread = current_thread();
	savearea_t     *regs;
	user_addr_t     pc, sp, fp;
	int             n = 0;

	if (thread == NULL)
		return 0;

	if (DTRACE_CPUFLAG_ISSET(CPU_DTRACE_FAULT))
		return (-1);

	regs = (savearea_t *) find_user_regs(thread);
	if (regs == NULL)
		return 0;
	
	pc = get_saved_state_pc(regs);
	sp = get_saved_state_sp(regs);
	fp = get_saved_state_fp(regs);

	if (DTRACE_CPUFLAG_ISSET(CPU_DTRACE_ENTRY)) {
		n++;
		pc = get_saved_state_lr(regs);
	}

	/*
	 * Note that unlike ppc, the arm code does not use
	 * CPU_DTRACE_USTACK_FP. This is because arm always
	 * traces from the sp, even in syscall/profile/fbt
	 * providers.
	 */
	
	n += dtrace_getustack_common(NULL, 0, pc, fp);

	return (n);
}