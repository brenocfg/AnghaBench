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
struct intel_uncore_box {int /*<<< orphan*/  hrtimer; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_REL_PINNED ; 
 int /*<<< orphan*/  UNCORE_PMU_HRTIMER_INTERVAL ; 
 int /*<<< orphan*/  __hrtimer_start_range_ns (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uncore_pmu_start_hrtimer(struct intel_uncore_box *box)
{
	__hrtimer_start_range_ns(&box->hrtimer,
			ns_to_ktime(UNCORE_PMU_HRTIMER_INTERVAL), 0,
			HRTIMER_MODE_REL_PINNED, 0);
}