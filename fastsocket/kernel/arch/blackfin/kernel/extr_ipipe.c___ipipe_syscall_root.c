#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {scalar_t__ orig_p0; } ;
struct ipipe_percpu_domain_data {int irqpend_himask; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPIPE_EVENT_SYSCALL ; 
 int IPIPE_IRQMASK_VIRT ; 
 scalar_t__ NR_syscalls ; 
 int PF_EVNOTIFY ; 
 int __ipipe_dispatch_event (int /*<<< orphan*/ ,struct pt_regs*) ; 
 int /*<<< orphan*/  __ipipe_event_monitored_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ipipe_irq_tail_hook ; 
 int /*<<< orphan*/  __ipipe_root_domain_p ; 
 int /*<<< orphan*/  __ipipe_sync_pipeline (int) ; 
 TYPE_1__* current ; 
 struct ipipe_percpu_domain_data* ipipe_root_cpudom_ptr () ; 
 int /*<<< orphan*/  local_irq_restore_hw (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save_hw (unsigned long) ; 

int __ipipe_syscall_root(struct pt_regs *regs)
{
	struct ipipe_percpu_domain_data *p;
	unsigned long flags;
	int ret;

	/*
	 * We need to run the IRQ tail hook whenever we don't
	 * propagate a syscall to higher domains, because we know that
	 * important operations might be pending there (e.g. Xenomai
	 * deferred rescheduling).
	 */

	if (regs->orig_p0 < NR_syscalls) {
		void (*hook)(void) = (void (*)(void))__ipipe_irq_tail_hook;
		hook();
		if ((current->flags & PF_EVNOTIFY) == 0)
			return 0;
	}

	/*
	 * This routine either returns:
	 * 0 -- if the syscall is to be passed to Linux;
	 * >0 -- if the syscall should not be passed to Linux, and no
	 * tail work should be performed;
	 * <0 -- if the syscall should not be passed to Linux but the
	 * tail work has to be performed (for handling signals etc).
	 */

	if (!__ipipe_event_monitored_p(IPIPE_EVENT_SYSCALL))
		return 0;

	ret = __ipipe_dispatch_event(IPIPE_EVENT_SYSCALL, regs);

	local_irq_save_hw(flags);

	if (!__ipipe_root_domain_p) {
		local_irq_restore_hw(flags);
		return 1;
	}

	p = ipipe_root_cpudom_ptr();
	if ((p->irqpend_himask & IPIPE_IRQMASK_VIRT) != 0)
		__ipipe_sync_pipeline(IPIPE_IRQMASK_VIRT);

	local_irq_restore_hw(flags);

	return -ret;
}