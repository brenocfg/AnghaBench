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
typedef  scalar_t__ user_addr_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ RETURN_OFFSET ; 
 scalar_t__ RETURN_OFFSET64 ; 
 int /*<<< orphan*/  current_proc () ; 
 scalar_t__ dtrace_fuword32 (scalar_t__) ; 
 scalar_t__ dtrace_fuword64 (scalar_t__) ; 
 scalar_t__ proc_is64bit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dtrace_getustack_common(uint64_t *pcstack, int pcstack_limit, user_addr_t pc,
    user_addr_t sp)
{
#if 0
	volatile uint16_t *flags =
	    (volatile uint16_t *)&cpu_core[CPU->cpu_id].cpuc_dtrace_flags;

	uintptr_t oldcontext = lwp->lwp_oldcontext; /* XXX signal stack crawl */
	size_t s1, s2;
#endif
	int ret = 0;
	boolean_t is64Bit = proc_is64bit(current_proc());

	ASSERT(pcstack == NULL || pcstack_limit > 0);
	
#if 0 /* XXX signal stack crawl */
	if (p->p_model == DATAMODEL_NATIVE) {
		s1 = sizeof (struct frame) + 2 * sizeof (long);
		s2 = s1 + sizeof (siginfo_t);
	} else {
		s1 = sizeof (struct frame32) + 3 * sizeof (int);
		s2 = s1 + sizeof (siginfo32_t);
	}
#endif

	while (pc != 0) {
		ret++;
		if (pcstack != NULL) {
			*pcstack++ = (uint64_t)pc;
			pcstack_limit--;
			if (pcstack_limit <= 0)
				break;
		}

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
				ucontext32_t *ucp = (ucontext32_t *)oldcontext;
				greg32_t *gregs = ucp->uc_mcontext.gregs;

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

	return (ret);
}