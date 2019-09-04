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
typedef  int /*<<< orphan*/  uthread_t ;
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int /*<<< orphan*/  proc_t ;
struct TYPE_3__ {scalar_t__ pc; } ;
typedef  TYPE_1__ arm_saved_state_t ;

/* Variables and functions */

__attribute__((used)) static void
fasttrap_sigsegv(proc_t *p, uthread_t t, user_addr_t addr, arm_saved_state_t *regs)
{
	/* TODO: This function isn't implemented yet. In debug mode, panic the system to
	 * find out why we're hitting this point. In other modes, kill the process.
	 */
#if DEBUG
#pragma unused(p,t,addr,arm_saved_state)
	panic("fasttrap: sigsegv not yet implemented");
#else
#pragma unused(p,t,addr)
	/* Kill the process */
	regs->pc = 0;
#endif

#if 0
	proc_lock(p);

	/* Set fault address and mark signal */
	t->uu_code = addr;
	t->uu_siglist |= sigmask(SIGSEGV);

	/* 
	 * XXX These two line may be redundant; if not, then we need
	 * XXX to potentially set the data address in the machine
	 * XXX specific thread state structure to indicate the address.
	 */         
	t->uu_exception = KERN_INVALID_ADDRESS;         /* SIGSEGV */
	t->uu_subcode = 0;      /* XXX pad */
                
	proc_unlock(p); 
                                     
	/* raise signal */
	signal_setast(t->uu_context.vc_thread);
#endif
}