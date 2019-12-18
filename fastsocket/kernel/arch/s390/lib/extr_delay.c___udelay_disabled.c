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
typedef  scalar_t__ u64 ;
struct TYPE_2__ {scalar_t__ clock_comparator; } ;

/* Variables and functions */
 unsigned long PSW_MASK_EXT ; 
 unsigned long PSW_MASK_WAIT ; 
 TYPE_1__ S390_lowcore ; 
 int /*<<< orphan*/  __ctl_load (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ctl_store (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __load_psw_mask (unsigned long) ; 
 scalar_t__ get_clock () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 scalar_t__ local_tick_disable () ; 
 int /*<<< orphan*/  local_tick_enable (scalar_t__) ; 
 int /*<<< orphan*/  lockdep_off () ; 
 int /*<<< orphan*/  lockdep_on () ; 
 unsigned long psw_kernel_bits ; 
 int /*<<< orphan*/  set_clock_comparator (scalar_t__) ; 
 int /*<<< orphan*/  trace_hardirqs_on () ; 

__attribute__((used)) static void __udelay_disabled(unsigned long long usecs)
{
	unsigned long mask, cr0, cr0_saved;
	u64 clock_saved;
	u64 end;

	mask = psw_kernel_bits | PSW_MASK_WAIT | PSW_MASK_EXT;
	end = get_clock() + (usecs << 12);
	clock_saved = local_tick_disable();
	__ctl_store(cr0_saved, 0, 0);
	cr0 = (cr0_saved & 0xffff00e0) | 0x00000800;
	__ctl_load(cr0 , 0, 0);
	lockdep_off();
	do {
		set_clock_comparator(end);
		trace_hardirqs_on();
		__load_psw_mask(mask);
		local_irq_disable();
	} while (get_clock() < end);
	lockdep_on();
	__ctl_load(cr0_saved, 0, 0);
	local_tick_enable(clock_saved);
	set_clock_comparator(S390_lowcore.clock_comparator);
}