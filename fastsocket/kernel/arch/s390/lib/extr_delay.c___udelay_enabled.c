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
 unsigned long PSW_MASK_IO ; 
 unsigned long PSW_MASK_WAIT ; 
 TYPE_1__ S390_lowcore ; 
 int /*<<< orphan*/  __load_psw_mask (unsigned long) ; 
 scalar_t__ get_clock () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 scalar_t__ local_tick_disable () ; 
 int /*<<< orphan*/  local_tick_enable (scalar_t__) ; 
 unsigned long psw_kernel_bits ; 
 int /*<<< orphan*/  set_clock_comparator (scalar_t__) ; 
 int /*<<< orphan*/  trace_hardirqs_on () ; 

__attribute__((used)) static void __udelay_enabled(unsigned long long usecs)
{
	unsigned long mask;
	u64 clock_saved;
	u64 end;

	mask = psw_kernel_bits | PSW_MASK_WAIT | PSW_MASK_EXT | PSW_MASK_IO;
	end = get_clock() + (usecs << 12);
	do {
		clock_saved = 0;
		if (end < S390_lowcore.clock_comparator) {
			clock_saved = local_tick_disable();
			set_clock_comparator(end);
		}
		trace_hardirqs_on();
		__load_psw_mask(mask);
		local_irq_disable();
		if (clock_saved)
			local_tick_enable(clock_saved);
	} while (get_clock() < end);
	set_clock_comparator(S390_lowcore.clock_comparator);
}