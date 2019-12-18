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
struct rcu_random_state {scalar_t__ rrs_count; unsigned long rrs_state; } ;

/* Variables and functions */
 int RCU_RANDOM_ADD ; 
 int RCU_RANDOM_MULT ; 
 scalar_t__ RCU_RANDOM_REFRESH ; 
 scalar_t__ cpu_clock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_smp_processor_id () ; 
 unsigned long swahw32 (int) ; 

__attribute__((used)) static unsigned long
rcu_random(struct rcu_random_state *rrsp)
{
	if (--rrsp->rrs_count < 0) {
		rrsp->rrs_state +=
			(unsigned long)cpu_clock(raw_smp_processor_id());
		rrsp->rrs_count = RCU_RANDOM_REFRESH;
	}
	rrsp->rrs_state = rrsp->rrs_state * RCU_RANDOM_MULT + RCU_RANDOM_ADD;
	return swahw32(rrsp->rrs_state);
}