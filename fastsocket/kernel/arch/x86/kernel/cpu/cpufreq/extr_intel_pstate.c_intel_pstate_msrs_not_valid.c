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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  MSR_IA32_APERF ; 
 int /*<<< orphan*/  MSR_IA32_MPERF ; 
 int /*<<< orphan*/  intel_pstate_max_pstate () ; 
 int /*<<< orphan*/  intel_pstate_min_pstate () ; 
 int /*<<< orphan*/  intel_pstate_turbo_pstate () ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int intel_pstate_msrs_not_valid(void)
{
	/* Check that all the msr's we are using are valid. */
	u64 aperf, mperf, tmp;

	rdmsrl(MSR_IA32_APERF, aperf);
	rdmsrl(MSR_IA32_MPERF, mperf);

	if (!intel_pstate_min_pstate() ||
		!intel_pstate_max_pstate() ||
		!intel_pstate_turbo_pstate())
		return -ENODEV;

	rdmsrl(MSR_IA32_APERF, tmp);
	if (!(tmp - aperf))
		return -ENODEV;

	rdmsrl(MSR_IA32_MPERF, tmp);
	if (!(tmp - mperf))
		return -ENODEV;

	return 0;
}