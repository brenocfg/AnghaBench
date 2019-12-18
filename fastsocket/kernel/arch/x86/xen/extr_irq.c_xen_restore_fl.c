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
struct vcpu_info {unsigned long evtchn_upcall_mask; int /*<<< orphan*/  evtchn_upcall_pending; } ;

/* Variables and functions */
 unsigned long X86_EFLAGS_IF ; 
 int /*<<< orphan*/  barrier () ; 
 struct vcpu_info* percpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preempt_check_resched () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable_no_resched () ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_force_evtchn_callback () ; 
 int /*<<< orphan*/  xen_vcpu ; 

__attribute__((used)) static void xen_restore_fl(unsigned long flags)
{
	struct vcpu_info *vcpu;

	/* convert from IF type flag */
	flags = !(flags & X86_EFLAGS_IF);

	/* There's a one instruction preempt window here.  We need to
	   make sure we're don't switch CPUs between getting the vcpu
	   pointer and updating the mask. */
	preempt_disable();
	vcpu = percpu_read(xen_vcpu);
	vcpu->evtchn_upcall_mask = flags;
	preempt_enable_no_resched();

	/* Doesn't matter if we get preempted here, because any
	   pending event will get dealt with anyway. */

	if (flags == 0) {
		preempt_check_resched();
		barrier(); /* unmask then check (avoid races) */
		if (unlikely(vcpu->evtchn_upcall_pending))
			xen_force_evtchn_callback();
	}
}