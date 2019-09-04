#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ebp; int /*<<< orphan*/  uesp; int /*<<< orphan*/  eip; } ;
struct TYPE_5__ {int /*<<< orphan*/  rsp; int /*<<< orphan*/  rip; } ;
struct TYPE_6__ {int /*<<< orphan*/  rbp; TYPE_1__ isf; } ;
struct TYPE_8__ {TYPE_3__ ss_32; TYPE_2__ ss_64; } ;
typedef  TYPE_4__ x86_saved_state_t ;
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int /*<<< orphan*/ * thread_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_DTRACE_FAULT ; 
 scalar_t__ DTRACE_CPUFLAG_ISSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALID ; 
 int /*<<< orphan*/  current_proc () ; 
 int /*<<< orphan*/ * current_thread () ; 
 int dtrace_adjust_stack (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dtrace_getustack_common (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ find_user_regs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pal_register_cache_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ proc_is64bit (int /*<<< orphan*/ ) ; 

int
dtrace_getustackdepth(void)
{
	thread_t thread = current_thread();
	x86_saved_state_t *regs;
	user_addr_t pc, sp, fp;
	int n = 0;
	boolean_t is64Bit = proc_is64bit(current_proc());

	if (thread == NULL)
		return 0;

	if (DTRACE_CPUFLAG_ISSET(CPU_DTRACE_FAULT))
		return (-1);

	pal_register_cache_state(thread, VALID);
	regs = (x86_saved_state_t *)find_user_regs(thread);
	if (regs == NULL)
		return 0;

	if (is64Bit) {
		pc = regs->ss_64.isf.rip;
		sp = regs->ss_64.isf.rsp;
		fp = regs->ss_64.rbp;
	} else {
		pc = regs->ss_32.eip;
		sp = regs->ss_32.uesp;
		fp = regs->ss_32.ebp;
	}

	if (dtrace_adjust_stack(NULL, NULL, &pc, sp) == 1) {
	    /*
	     * we would have adjusted the stack if we had
	     * supplied one (that is what rc == 1 means).
	     * Also, as a side effect, the pc might have
	     * been fixed up, which is good for calling
	     * in to dtrace_getustack_common.
	     */
	    n++;
	}
	
	/*
	 * Note that unlike ppc, the x86 code does not use
	 * CPU_DTRACE_USTACK_FP. This is because x86 always
	 * traces from the fp, even in syscall/profile/fbt
	 * providers.
	 */

	n += dtrace_getustack_common(NULL, 0, pc, fp);

	return (n);
}