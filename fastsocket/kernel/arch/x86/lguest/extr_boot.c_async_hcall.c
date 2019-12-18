#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* hcall_status; TYPE_1__* hcalls; } ;
struct TYPE_3__ {unsigned long arg0; unsigned long arg1; unsigned long arg2; unsigned long arg3; unsigned long arg4; } ;

/* Variables and functions */
 unsigned int LHCALL_RING_SIZE ; 
 int /*<<< orphan*/  kvm_hypercall4 (unsigned long,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 TYPE_2__ lguest_data ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void async_hcall(unsigned long call, unsigned long arg1,
			unsigned long arg2, unsigned long arg3,
			unsigned long arg4)
{
	/* Note: This code assumes we're uniprocessor. */
	static unsigned int next_call;
	unsigned long flags;

	/*
	 * Disable interrupts if not already disabled: we don't want an
	 * interrupt handler making a hypercall while we're already doing
	 * one!
	 */
	local_irq_save(flags);
	if (lguest_data.hcall_status[next_call] != 0xFF) {
		/* Table full, so do normal hcall which will flush table. */
		kvm_hypercall4(call, arg1, arg2, arg3, arg4);
	} else {
		lguest_data.hcalls[next_call].arg0 = call;
		lguest_data.hcalls[next_call].arg1 = arg1;
		lguest_data.hcalls[next_call].arg2 = arg2;
		lguest_data.hcalls[next_call].arg3 = arg3;
		lguest_data.hcalls[next_call].arg4 = arg4;
		/* Arguments must all be written before we mark it to go */
		wmb();
		lguest_data.hcall_status[next_call] = 0;
		if (++next_call == LHCALL_RING_SIZE)
			next_call = 0;
	}
	local_irq_restore(flags);
}