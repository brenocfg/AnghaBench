#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct acpi_processor_cx {int valid; int /*<<< orphan*/  latency; int /*<<< orphan*/  latency_ticks; int /*<<< orphan*/  address; } ;
struct TYPE_7__ {int bm_check; int bm_control; int has_cst; } ;
struct acpi_processor {TYPE_3__ flags; int /*<<< orphan*/  id; } ;
struct TYPE_8__ {int flags; } ;
struct TYPE_5__ {scalar_t__ fdma; } ;
struct TYPE_6__ {TYPE_1__ piix4; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BITREG_BUS_MASTER_RLD ; 
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int ACPI_FADT_WBINVD ; 
 TYPE_4__ acpi_gbl_FADT ; 
 int /*<<< orphan*/  acpi_processor_power_init_bm_check (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_write_bit_register (int /*<<< orphan*/ ,int) ; 
 TYPE_2__ errata ; 

__attribute__((used)) static void acpi_processor_power_verify_c3(struct acpi_processor *pr,
					   struct acpi_processor_cx *cx)
{
	static int bm_check_flag = -1;
	static int bm_control_flag = -1;


	if (!cx->address)
		return;

	/*
	 * PIIX4 Erratum #18: We don't support C3 when Type-F (fast)
	 * DMA transfers are used by any ISA device to avoid livelock.
	 * Note that we could disable Type-F DMA (as recommended by
	 * the erratum), but this is known to disrupt certain ISA
	 * devices thus we take the conservative approach.
	 */
	else if (errata.piix4.fdma) {
		ACPI_DEBUG_PRINT((ACPI_DB_INFO,
				  "C3 not supported on PIIX4 with Type-F DMA\n"));
		return;
	}

	/* All the logic here assumes flags.bm_check is same across all CPUs */
	if (bm_check_flag == -1) {
		/* Determine whether bm_check is needed based on CPU  */
		acpi_processor_power_init_bm_check(&(pr->flags), pr->id);
		bm_check_flag = pr->flags.bm_check;
		bm_control_flag = pr->flags.bm_control;
	} else {
		pr->flags.bm_check = bm_check_flag;
		pr->flags.bm_control = bm_control_flag;
	}

	if (pr->flags.bm_check) {
		if (!pr->flags.bm_control) {
			if (pr->flags.has_cst != 1) {
				/* bus mastering control is necessary */
				ACPI_DEBUG_PRINT((ACPI_DB_INFO,
					"C3 support requires BM control\n"));
				return;
			} else {
				/* Here we enter C3 without bus mastering */
				ACPI_DEBUG_PRINT((ACPI_DB_INFO,
					"C3 support without BM control\n"));
			}
		}
	} else {
		/*
		 * WBINVD should be set in fadt, for C3 state to be
		 * supported on when bm_check is not required.
		 */
		if (!(acpi_gbl_FADT.flags & ACPI_FADT_WBINVD)) {
			ACPI_DEBUG_PRINT((ACPI_DB_INFO,
					  "Cache invalidation should work properly"
					  " for C3 to be enabled on SMP systems\n"));
			return;
		}
	}

	/*
	 * Otherwise we've met all of our C3 requirements.
	 * Normalize the C3 latency to expidite policy.  Enable
	 * checking of bus mastering status (bm_check) so we can
	 * use this in our C3 policy
	 */
	cx->valid = 1;

	cx->latency_ticks = cx->latency;
	/*
	 * On older chipsets, BM_RLD needs to be set
	 * in order for Bus Master activity to wake the
	 * system from C3.  Newer chipsets handle DMA
	 * during C3 automatically and BM_RLD is a NOP.
	 * In either case, the proper way to
	 * handle BM_RLD is to set it and leave it set.
	 */
	acpi_write_bit_register(ACPI_BITREG_BUS_MASTER_RLD, 1);

	return;
}