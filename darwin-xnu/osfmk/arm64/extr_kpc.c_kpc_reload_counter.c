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
typedef  unsigned long long uint64_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  FIXED_RELOAD (scalar_t__) ; 
 unsigned long long KPC_ARM64_COUNTER_MASK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ kpc_configurable_count () ; 
 int /*<<< orphan*/  kpc_controls_counter (scalar_t__) ; 
 scalar_t__ kpc_fixed_count () ; 
 unsigned long long read_counter (scalar_t__) ; 
 int /*<<< orphan*/  write_counter (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
kpc_reload_counter(uint32_t ctr)
{
	assert(ctr < (kpc_configurable_count() + kpc_fixed_count()));

	/* don't reload counters reserved for power management */
	if (!kpc_controls_counter(ctr))
		return 0ULL;

	uint64_t old = read_counter(ctr);
	write_counter(ctr, FIXED_RELOAD(ctr));
	return old & KPC_ARM64_COUNTER_MASK;
}