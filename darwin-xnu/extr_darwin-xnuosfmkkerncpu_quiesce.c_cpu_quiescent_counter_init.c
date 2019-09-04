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

/* Variables and functions */
 int CPU_CHECKIN_MASK ; 
 int /*<<< orphan*/  CPU_CHECKIN_MIN_INTERVAL_US ; 
 int CPU_EXPECTED_MASK ; 
 int /*<<< orphan*/  MAX_CPUS ; 
 int /*<<< orphan*/  assert (int) ; 
 int cpu_checked_in_bit (int /*<<< orphan*/ ) ; 
 int cpu_expected_bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_quiescent_counter_set_min_interval_us (int /*<<< orphan*/ ) ; 

void
cpu_quiescent_counter_init(void)
{
	assert(CPU_CHECKIN_MASK & cpu_checked_in_bit(MAX_CPUS));
	assert(CPU_EXPECTED_MASK & cpu_expected_bit(MAX_CPUS));
	assert((CPU_CHECKIN_MASK & cpu_expected_bit(MAX_CPUS)) == 0);
	assert((CPU_EXPECTED_MASK & cpu_checked_in_bit(MAX_CPUS)) == 0);

	cpu_quiescent_counter_set_min_interval_us(CPU_CHECKIN_MIN_INTERVAL_US);
}