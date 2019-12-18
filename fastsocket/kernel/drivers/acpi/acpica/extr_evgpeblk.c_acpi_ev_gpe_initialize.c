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
typedef  int u32 ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_4__ {scalar_t__ address; } ;
struct TYPE_3__ {int gpe0_block_length; int gpe1_block_length; int gpe1_base; int /*<<< orphan*/  sci_interrupt; TYPE_2__ xgpe1_block; TYPE_2__ xgpe0_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INIT ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int ACPI_GPE_MAX ; 
 int ACPI_GPE_REGISTER_WIDTH ; 
 int /*<<< orphan*/  ACPI_MTX_NAMESPACE ; 
 int /*<<< orphan*/  AE_BAD_VALUE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ev_create_gpe_block (int /*<<< orphan*/ ,TYPE_2__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ acpi_gbl_FADT ; 
 int /*<<< orphan*/  acpi_gbl_fadt_gpe_device ; 
 int /*<<< orphan*/ * acpi_gbl_gpe_fadt_blocks ; 
 int /*<<< orphan*/  acpi_ut_acquire_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_release_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_gpe_initialize ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status acpi_ev_gpe_initialize(void)
{
	u32 register_count0 = 0;
	u32 register_count1 = 0;
	u32 gpe_number_max = 0;
	acpi_status status;

	ACPI_FUNCTION_TRACE(ev_gpe_initialize);

	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAILURE(status)) {
		return_ACPI_STATUS(status);
	}

	/*
	 * Initialize the GPE Block(s) defined in the FADT
	 *
	 * Why the GPE register block lengths are divided by 2:  From the ACPI
	 * Spec, section "General-Purpose Event Registers", we have:
	 *
	 * "Each register block contains two registers of equal length
	 *  GPEx_STS and GPEx_EN (where x is 0 or 1). The length of the
	 *  GPE0_STS and GPE0_EN registers is equal to half the GPE0_LEN
	 *  The length of the GPE1_STS and GPE1_EN registers is equal to
	 *  half the GPE1_LEN. If a generic register block is not supported
	 *  then its respective block pointer and block length values in the
	 *  FADT table contain zeros. The GPE0_LEN and GPE1_LEN do not need
	 *  to be the same size."
	 */

	/*
	 * Determine the maximum GPE number for this machine.
	 *
	 * Note: both GPE0 and GPE1 are optional, and either can exist without
	 * the other.
	 *
	 * If EITHER the register length OR the block address are zero, then that
	 * particular block is not supported.
	 */
	if (acpi_gbl_FADT.gpe0_block_length &&
	    acpi_gbl_FADT.xgpe0_block.address) {

		/* GPE block 0 exists (has both length and address > 0) */

		register_count0 = (u16) (acpi_gbl_FADT.gpe0_block_length / 2);

		gpe_number_max =
		    (register_count0 * ACPI_GPE_REGISTER_WIDTH) - 1;

		/* Install GPE Block 0 */

		status = acpi_ev_create_gpe_block(acpi_gbl_fadt_gpe_device,
						  &acpi_gbl_FADT.xgpe0_block,
						  register_count0, 0,
						  acpi_gbl_FADT.sci_interrupt,
						  &acpi_gbl_gpe_fadt_blocks[0]);

		if (ACPI_FAILURE(status)) {
			ACPI_EXCEPTION((AE_INFO, status,
					"Could not create GPE Block 0"));
		}
	}

	if (acpi_gbl_FADT.gpe1_block_length &&
	    acpi_gbl_FADT.xgpe1_block.address) {

		/* GPE block 1 exists (has both length and address > 0) */

		register_count1 = (u16) (acpi_gbl_FADT.gpe1_block_length / 2);

		/* Check for GPE0/GPE1 overlap (if both banks exist) */

		if ((register_count0) &&
		    (gpe_number_max >= acpi_gbl_FADT.gpe1_base)) {
			ACPI_ERROR((AE_INFO,
				    "GPE0 block (GPE 0 to %d) overlaps the GPE1 block "
				    "(GPE %d to %d) - Ignoring GPE1",
				    gpe_number_max, acpi_gbl_FADT.gpe1_base,
				    acpi_gbl_FADT.gpe1_base +
				    ((register_count1 *
				      ACPI_GPE_REGISTER_WIDTH) - 1)));

			/* Ignore GPE1 block by setting the register count to zero */

			register_count1 = 0;
		} else {
			/* Install GPE Block 1 */

			status =
			    acpi_ev_create_gpe_block(acpi_gbl_fadt_gpe_device,
						     &acpi_gbl_FADT.xgpe1_block,
						     register_count1,
						     acpi_gbl_FADT.gpe1_base,
						     acpi_gbl_FADT.
						     sci_interrupt,
						     &acpi_gbl_gpe_fadt_blocks
						     [1]);

			if (ACPI_FAILURE(status)) {
				ACPI_EXCEPTION((AE_INFO, status,
						"Could not create GPE Block 1"));
			}

			/*
			 * GPE0 and GPE1 do not have to be contiguous in the GPE number
			 * space. However, GPE0 always starts at GPE number zero.
			 */
			gpe_number_max = acpi_gbl_FADT.gpe1_base +
			    ((register_count1 * ACPI_GPE_REGISTER_WIDTH) - 1);
		}
	}

	/* Exit if there are no GPE registers */

	if ((register_count0 + register_count1) == 0) {

		/* GPEs are not required by ACPI, this is OK */

		ACPI_DEBUG_PRINT((ACPI_DB_INIT,
				  "There are no GPE blocks defined in the FADT\n"));
		status = AE_OK;
		goto cleanup;
	}

	/* Check for Max GPE number out-of-range */

	if (gpe_number_max > ACPI_GPE_MAX) {
		ACPI_ERROR((AE_INFO,
			    "Maximum GPE number from FADT is too large: 0x%X",
			    gpe_number_max));
		status = AE_BAD_VALUE;
		goto cleanup;
	}

      cleanup:
	(void)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
	return_ACPI_STATUS(AE_OK);
}