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
typedef  int u64 ;

/* Variables and functions */
 scalar_t__ cpu_khz ; 
 int /*<<< orphan*/  do_div (int,int) ; 

__attribute__((used)) static unsigned int adjust_for_32bit_ctr(unsigned int hz)
{
	u64 counter_val;
	unsigned int retval = hz;

	/*
	 * On Intel CPUs with P6/ARCH_PERFMON only 32 bits in the counter
	 * are writable, with higher bits sign extending from bit 31.
	 * So, we can only program the counter with 31 bit values and
	 * 32nd bit should be 1, for 33.. to be 1.
	 * Find the appropriate nmi_hz
	 */
	counter_val = (u64)cpu_khz * 1000;
	do_div(counter_val, retval);
	if (counter_val > 0x7fffffffULL) {
		u64 count = (u64)cpu_khz * 1000;
		do_div(count, 0x7fffffffUL);
		retval = count + 1;
	}
	return retval;
}