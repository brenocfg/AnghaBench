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
typedef  scalar_t__ user_addr_t ;
typedef  void* uint64_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/ * thread_t ;
struct TYPE_5__ {scalar_t__ eip; scalar_t__ ebp; } ;
struct TYPE_6__ {TYPE_1__ ss_32; } ;
typedef  TYPE_2__ savearea_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_8__ {size_t cpu_id; } ;
struct TYPE_7__ {int /*<<< orphan*/  cpuc_dtrace_flags; } ;

/* Variables and functions */
 TYPE_4__* CPU ; 
 int volatile CPU_DTRACE_FAULT ; 
 scalar_t__ RETURN_OFFSET ; 
 scalar_t__ RETURN_OFFSET64 ; 
 TYPE_3__* cpu_core ; 
 int /*<<< orphan*/  current_proc () ; 
 int /*<<< orphan*/ * current_thread () ; 
 int dtrace_adjust_stack (void***,int*,scalar_t__*,scalar_t__) ; 
 scalar_t__ dtrace_fuword32 (scalar_t__) ; 
 scalar_t__ dtrace_fuword64 (scalar_t__) ; 
 scalar_t__ dtrace_proc_selfpid () ; 
 scalar_t__ find_user_regs (int /*<<< orphan*/ *) ; 
 scalar_t__ proc_is64bit (int /*<<< orphan*/ ) ; 

void
dtrace_getufpstack(uint64_t *pcstack, uint64_t *fpstack, int pcstack_limit)
{
	thread_t thread = current_thread();
	savearea_t *regs;
	user_addr_t pc, sp;
	volatile uint16_t *flags =
	    (volatile uint16_t *)&cpu_core[CPU->cpu_id].cpuc_dtrace_flags;
#if 0
	uintptr_t oldcontext;
	size_t s1, s2;
#endif
	boolean_t is64Bit = proc_is64bit(current_proc());

	if (*flags & CPU_DTRACE_FAULT)
		return;

	if (pcstack_limit <= 0)
		return;

	/*
	 * If there's no user context we still need to zero the stack.
	 */
	if (thread == NULL)
		goto zero;

	regs = (savearea_t *)find_user_regs(thread);
	if (regs == NULL)
		goto zero;
		
	*pcstack++ = (uint64_t)dtrace_proc_selfpid();
	pcstack_limit--;

	if (pcstack_limit <= 0)
		return;

	pc = regs->ss_32.eip;
	sp = regs->ss_32.ebp;
	
#if 0 /* XXX signal stack crawl */
	oldcontext = lwp->lwp_oldcontext;

	if (p->p_model == DATAMODEL_NATIVE) {
		s1 = sizeof (struct frame) + 2 * sizeof (long);
		s2 = s1 + sizeof (siginfo_t);
	} else {
		s1 = sizeof (struct frame32) + 3 * sizeof (int);
		s2 = s1 + sizeof (siginfo32_t);
	}
#endif

	if(dtrace_adjust_stack(&pcstack, &pcstack_limit, &pc, sp) == 1) {
            /*
	     * we made a change.
	     */
	    *fpstack++ = 0;
	    if (pcstack_limit <= 0)
		return;
	}

	while (pc != 0) {
		*pcstack++ = (uint64_t)pc;
		*fpstack++ = sp;
		pcstack_limit--;
		if (pcstack_limit <= 0)
			break;

		if (sp == 0)
			break;

#if 0 /* XXX signal stack crawl */
		if (oldcontext == sp + s1 || oldcontext == sp + s2) {
			if (p->p_model == DATAMODEL_NATIVE) {
				ucontext_t *ucp = (ucontext_t *)oldcontext;
				greg_t *gregs = ucp->uc_mcontext.gregs;

				sp = dtrace_fulword(&gregs[REG_FP]);
				pc = dtrace_fulword(&gregs[REG_PC]);

				oldcontext = dtrace_fulword(&ucp->uc_link);
			} else {
				ucontext_t *ucp = (ucontext_t *)oldcontext;
				greg_t *gregs = ucp->uc_mcontext.gregs;

				sp = dtrace_fuword32(&gregs[EBP]);
				pc = dtrace_fuword32(&gregs[EIP]);

				oldcontext = dtrace_fuword32(&ucp->uc_link);
			}
		} 
		else
#endif
		{
			if (is64Bit) {
				pc = dtrace_fuword64((sp + RETURN_OFFSET64));
				sp = dtrace_fuword64(sp);
			} else {
				pc = dtrace_fuword32((sp + RETURN_OFFSET));
				sp = dtrace_fuword32(sp);
			}
		}

#if 0 /* XXX */
		/*
		 * This is totally bogus:  if we faulted, we're going to clear
		 * the fault and break.  This is to deal with the apparently
		 * broken Java stacks on x86.
		 */
		if (*flags & CPU_DTRACE_FAULT) {
			*flags &= ~CPU_DTRACE_FAULT;
			break;
		}
#endif
	}

zero:
	while (pcstack_limit-- > 0)
		*pcstack++ = 0;
}