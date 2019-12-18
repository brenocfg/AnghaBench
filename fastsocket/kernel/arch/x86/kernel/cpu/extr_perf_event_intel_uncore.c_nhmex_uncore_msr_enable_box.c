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
typedef  unsigned long long u64 ;
struct intel_uncore_box {int dummy; } ;

/* Variables and functions */
 unsigned long long NHMEX_W_PMON_GLOBAL_FIXED_EN ; 
 int /*<<< orphan*/  rdmsrl (unsigned int,unsigned long long) ; 
 unsigned int uncore_msr_box_ctl (struct intel_uncore_box*) ; 
 scalar_t__ uncore_msr_fixed_ctl (struct intel_uncore_box*) ; 
 unsigned long long uncore_num_counters (struct intel_uncore_box*) ; 
 int /*<<< orphan*/  wrmsrl (unsigned int,unsigned long long) ; 

__attribute__((used)) static void nhmex_uncore_msr_enable_box(struct intel_uncore_box *box)
{
	unsigned msr = uncore_msr_box_ctl(box);
	u64 config;

	if (msr) {
		rdmsrl(msr, config);
		config |= (1ULL << uncore_num_counters(box)) - 1;
		/* WBox has a fixed counter */
		if (uncore_msr_fixed_ctl(box))
			config |= NHMEX_W_PMON_GLOBAL_FIXED_EN;
		wrmsrl(msr, config);
	}
}