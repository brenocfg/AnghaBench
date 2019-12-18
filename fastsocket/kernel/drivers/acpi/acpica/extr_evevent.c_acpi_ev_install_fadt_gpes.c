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
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_MTX_NAMESPACE ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ev_initialize_gpe_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_gbl_fadt_gpe_device ; 
 int /*<<< orphan*/ * acpi_gbl_gpe_fadt_blocks ; 
 int /*<<< orphan*/  acpi_ut_acquire_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_release_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_install_fadt_gpes ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status acpi_ev_install_fadt_gpes(void)
{
	acpi_status status;

	ACPI_FUNCTION_TRACE(ev_install_fadt_gpes);

	/* Namespace must be locked */

	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	if (ACPI_FAILURE(status)) {
		return (status);
	}

	/* FADT GPE Block 0 */

	(void)acpi_ev_initialize_gpe_block(acpi_gbl_fadt_gpe_device,
					   acpi_gbl_gpe_fadt_blocks[0]);

	/* FADT GPE Block 1 */

	(void)acpi_ev_initialize_gpe_block(acpi_gbl_fadt_gpe_device,
					   acpi_gbl_gpe_fadt_blocks[1]);

	(void)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
	return_ACPI_STATUS(AE_OK);
}