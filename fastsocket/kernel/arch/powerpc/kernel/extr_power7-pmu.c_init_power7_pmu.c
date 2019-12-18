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
struct TYPE_5__ {int /*<<< orphan*/  oprofile_cpu_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  PPMU_SIAR_VALID ; 
 int /*<<< orphan*/  PVR_POWER7p ; 
 scalar_t__ __is_processor (int /*<<< orphan*/ ) ; 
 TYPE_3__* cur_cpu_spec ; 
 TYPE_1__ power7_pmu ; 
 int register_power_pmu (TYPE_1__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int init_power7_pmu(void)
{
	if (!cur_cpu_spec->oprofile_cpu_type ||
	    strcmp(cur_cpu_spec->oprofile_cpu_type, "ppc64/power7"))
		return -ENODEV;

	if (__is_processor(PVR_POWER7p))
		power7_pmu.flags |= PPMU_SIAR_VALID;

	return register_power_pmu(&power7_pmu);
}