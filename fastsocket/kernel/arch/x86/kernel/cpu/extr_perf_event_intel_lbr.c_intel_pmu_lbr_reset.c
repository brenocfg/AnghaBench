#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ lbr_format; } ;
struct TYPE_4__ {TYPE_1__ intel_cap; int /*<<< orphan*/  lbr_nr; } ;

/* Variables and functions */
 scalar_t__ LBR_FORMAT_32 ; 
 int /*<<< orphan*/  intel_pmu_lbr_reset_32 () ; 
 int /*<<< orphan*/  intel_pmu_lbr_reset_64 () ; 
 TYPE_2__ x86_pmu ; 

void intel_pmu_lbr_reset(void)
{
	if (!x86_pmu.lbr_nr)
		return;

	if (x86_pmu.intel_cap.lbr_format == LBR_FORMAT_32)
		intel_pmu_lbr_reset_32();
	else
		intel_pmu_lbr_reset_64();
}