#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int /*<<< orphan*/  num_counters; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  num_counters; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUID_ID ; 
 int ENODEV ; 
 size_t PMU_XSC1 ; 
 size_t PMU_XSC2 ; 
 TYPE_3__ op_xscale_spec ; 
 TYPE_1__* pmu ; 
 TYPE_1__* pmu_parms ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int read_cpuid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xscale_detect_pmu(void)
{
	int ret = 0;
	u32 id;

	id = (read_cpuid(CPUID_ID) >> 13) & 0x7;

	switch (id) {
	case 1:
		pmu = &pmu_parms[PMU_XSC1];
		break;
	case 2:
		pmu = &pmu_parms[PMU_XSC2];
		break;
	default:
		ret = -ENODEV;
		break;
	}

	if (!ret) {
		op_xscale_spec.name = pmu->name;
		op_xscale_spec.num_counters = pmu->num_counters;
		pr_debug("xscale_detect_pmu: detected %s PMU\n", pmu->name);
	}

	return ret;
}