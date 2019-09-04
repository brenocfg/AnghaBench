#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ user_addr_t ;
typedef  void* uint64_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/ * thread_t ;
struct TYPE_4__ {scalar_t__ pc; scalar_t__ sp; } ;
typedef  TYPE_1__ savearea_t ;
struct TYPE_6__ {size_t cpu_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  cpuc_dtrace_flags; } ;

/* Variables and functions */
 TYPE_3__* CPU ; 
 int /*<<< orphan*/  CPU_DTRACE_ENTRY ; 
 int volatile CPU_DTRACE_FAULT ; 
 scalar_t__ DTRACE_CPUFLAG_ISSET (int /*<<< orphan*/ ) ; 
 scalar_t__ RETURN_OFFSET ; 
 TYPE_2__* cpu_core ; 
 int /*<<< orphan*/ * current_thread () ; 
 scalar_t__ dtrace_fuword32 (scalar_t__) ; 
 scalar_t__ dtrace_proc_selfpid () ; 
 scalar_t__ find_user_regs (int /*<<< orphan*/ *) ; 

void
dtrace_getufpstack(uint64_t * pcstack, uint64_t * fpstack, int pcstack_limit)
{
	/* XXX ARMTODO 64vs32 */
	thread_t        thread = current_thread();
	savearea_t      *regs;
	user_addr_t     pc, sp;
	
	volatile        uint16_t  *flags = (volatile uint16_t *) & cpu_core[CPU->cpu_id].cpuc_dtrace_flags;

#if 0
	uintptr_t oldcontext;
	size_t          s1, s2;
#endif

	if (*flags & CPU_DTRACE_FAULT)
		return;

	if (pcstack_limit <= 0)
		return;

        /*
	 * If there's no user context we still need to zero the stack.
	 */
	if (thread == NULL)
		goto zero;

	regs = (savearea_t *) find_user_regs(thread);
	if (regs == NULL)
		goto zero;
	
	*pcstack++ = (uint64_t)dtrace_proc_selfpid();
	pcstack_limit--;

	if (pcstack_limit <= 0)
		return;
	
	pc = regs->pc;
	sp = regs->sp;

#if 0				/* XXX signal stack crawl */
	oldcontext = lwp->lwp_oldcontext;

	if (p->p_model == DATAMODEL_NATIVE) {
		s1 = sizeof(struct frame) + 2 * sizeof(long);
		s2 = s1 + sizeof(siginfo_t);
	} else {
		s1 = sizeof(struct frame32) + 3 * sizeof(int);
		s2 = s1 + sizeof(siginfo32_t);
	}
#endif

	if (DTRACE_CPUFLAG_ISSET(CPU_DTRACE_ENTRY)) {
		*pcstack++ = (uint64_t) pc;
		*fpstack++ = 0;
		pcstack_limit--;
		if (pcstack_limit <= 0)
			return;

		pc = dtrace_fuword32(sp);
	}
	while (pc != 0 && sp != 0) {
		*pcstack++ = (uint64_t) pc;
		*fpstack++ = sp;
		pcstack_limit--;
		if (pcstack_limit <= 0)
			break;

#if 0				/* XXX signal stack crawl */
		if (oldcontext == sp + s1 || oldcontext == sp + s2) {
			if (p->p_model == DATAMODEL_NATIVE) {
				ucontext_t     *ucp = (ucontext_t *) oldcontext;
				greg_t         *gregs = ucp->uc_mcontext.gregs;

				sp = dtrace_fulword(&gregs[REG_FP]);
				pc = dtrace_fulword(&gregs[REG_PC]);

				oldcontext = dtrace_fulword(&ucp->uc_link);
			} else {
				ucontext_t     *ucp = (ucontext_t *) oldcontext;
				greg_t         *gregs = ucp->uc_mcontext.gregs;

				sp = dtrace_fuword32(&gregs[EBP]);
				pc = dtrace_fuword32(&gregs[EIP]);

				oldcontext = dtrace_fuword32(&ucp->uc_link);
			}
		} else
#endif
		{
			pc = dtrace_fuword32((sp + RETURN_OFFSET));
			sp = dtrace_fuword32(sp);
		}

#if 0
		/* XXX ARMTODO*/
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
		*pcstack++ = 0ULL;
}