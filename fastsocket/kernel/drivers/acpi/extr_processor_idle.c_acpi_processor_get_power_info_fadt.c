#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* states; } ;
struct acpi_processor {TYPE_2__ power; scalar_t__ pblk; } ;
struct TYPE_6__ {int flags; scalar_t__ C2latency; scalar_t__ C3latency; } ;
struct TYPE_4__ {size_t type; scalar_t__ latency; scalar_t__ address; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int ACPI_FADT_C2_MP_SUPPORTED ; 
 scalar_t__ ACPI_PROCESSOR_MAX_C2_LATENCY ; 
 scalar_t__ ACPI_PROCESSOR_MAX_C3_LATENCY ; 
 size_t ACPI_STATE_C2 ; 
 size_t ACPI_STATE_C3 ; 
 int EINVAL ; 
 int ENODEV ; 
 TYPE_3__ acpi_gbl_FADT ; 
 int num_online_cpus () ; 

__attribute__((used)) static int acpi_processor_get_power_info_fadt(struct acpi_processor *pr)
{

	if (!pr)
		return -EINVAL;

	if (!pr->pblk)
		return -ENODEV;

	/* if info is obtained from pblk/fadt, type equals state */
	pr->power.states[ACPI_STATE_C2].type = ACPI_STATE_C2;
	pr->power.states[ACPI_STATE_C3].type = ACPI_STATE_C3;

#ifndef CONFIG_HOTPLUG_CPU
	/*
	 * Check for P_LVL2_UP flag before entering C2 and above on
	 * an SMP system.
	 */
	if ((num_online_cpus() > 1) &&
	    !(acpi_gbl_FADT.flags & ACPI_FADT_C2_MP_SUPPORTED))
		return -ENODEV;
#endif

	/* determine C2 and C3 address from pblk */
	pr->power.states[ACPI_STATE_C2].address = pr->pblk + 4;
	pr->power.states[ACPI_STATE_C3].address = pr->pblk + 5;

	/* determine latencies from FADT */
	pr->power.states[ACPI_STATE_C2].latency = acpi_gbl_FADT.C2latency;
	pr->power.states[ACPI_STATE_C3].latency = acpi_gbl_FADT.C3latency;

	/*
	 * FADT specified C2 latency must be less than or equal to
	 * 100 microseconds.
	 */
	if (acpi_gbl_FADT.C2latency > ACPI_PROCESSOR_MAX_C2_LATENCY) {
		ACPI_DEBUG_PRINT((ACPI_DB_INFO,
			"C2 latency too large [%d]\n", acpi_gbl_FADT.C2latency));
		/* invalidate C2 */
		pr->power.states[ACPI_STATE_C2].address = 0;
	}

	/*
	 * FADT supplied C3 latency must be less than or equal to
	 * 1000 microseconds.
	 */
	if (acpi_gbl_FADT.C3latency > ACPI_PROCESSOR_MAX_C3_LATENCY) {
		ACPI_DEBUG_PRINT((ACPI_DB_INFO,
			"C3 latency too large [%d]\n", acpi_gbl_FADT.C3latency));
		/* invalidate C3 */
		pr->power.states[ACPI_STATE_C3].address = 0;
	}

	ACPI_DEBUG_PRINT((ACPI_DB_INFO,
			  "lvl2[0x%08x] lvl3[0x%08x]\n",
			  pr->power.states[ACPI_STATE_C2].address,
			  pr->power.states[ACPI_STATE_C3].address));

	return 0;
}