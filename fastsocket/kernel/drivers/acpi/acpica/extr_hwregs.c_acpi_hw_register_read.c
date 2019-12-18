#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_2__ {int /*<<< orphan*/  smi_command; int /*<<< orphan*/  xpm_timer_block; int /*<<< orphan*/  xpm2_control_block; int /*<<< orphan*/  xpm1b_control_block; int /*<<< orphan*/  xpm1a_control_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int ACPI_PM1_CONTROL_WRITEONLY_BITS ; 
#define  ACPI_REGISTER_PM1_CONTROL 133 
#define  ACPI_REGISTER_PM1_ENABLE 132 
#define  ACPI_REGISTER_PM1_STATUS 131 
#define  ACPI_REGISTER_PM2_CONTROL 130 
#define  ACPI_REGISTER_PM_TIMER 129 
#define  ACPI_REGISTER_SMI_COMMAND_BLOCK 128 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_INFO ; 
 TYPE_1__ acpi_gbl_FADT ; 
 int /*<<< orphan*/  acpi_gbl_xpm1a_enable ; 
 int /*<<< orphan*/  acpi_gbl_xpm1a_status ; 
 int /*<<< orphan*/  acpi_gbl_xpm1b_enable ; 
 int /*<<< orphan*/  acpi_gbl_xpm1b_status ; 
 int /*<<< orphan*/  acpi_hw_read (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_hw_read_multiple (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_hw_read_port (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  hw_register_read ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_hw_register_read(u32 register_id, u32 * return_value)
{
	u32 value = 0;
	acpi_status status;

	ACPI_FUNCTION_TRACE(hw_register_read);

	switch (register_id) {
	case ACPI_REGISTER_PM1_STATUS:	/* PM1 A/B: 16-bit access each */

		status = acpi_hw_read_multiple(&value,
					       &acpi_gbl_xpm1a_status,
					       &acpi_gbl_xpm1b_status);
		break;

	case ACPI_REGISTER_PM1_ENABLE:	/* PM1 A/B: 16-bit access each */

		status = acpi_hw_read_multiple(&value,
					       &acpi_gbl_xpm1a_enable,
					       &acpi_gbl_xpm1b_enable);
		break;

	case ACPI_REGISTER_PM1_CONTROL:	/* PM1 A/B: 16-bit access each */

		status = acpi_hw_read_multiple(&value,
					       &acpi_gbl_FADT.
					       xpm1a_control_block,
					       &acpi_gbl_FADT.
					       xpm1b_control_block);

		/*
		 * Zero the write-only bits. From the ACPI specification, "Hardware
		 * Write-Only Bits": "Upon reads to registers with write-only bits,
		 * software masks out all write-only bits."
		 */
		value &= ~ACPI_PM1_CONTROL_WRITEONLY_BITS;
		break;

	case ACPI_REGISTER_PM2_CONTROL:	/* 8-bit access */

		status =
		    acpi_hw_read(&value, &acpi_gbl_FADT.xpm2_control_block);
		break;

	case ACPI_REGISTER_PM_TIMER:	/* 32-bit access */

		status = acpi_hw_read(&value, &acpi_gbl_FADT.xpm_timer_block);
		break;

	case ACPI_REGISTER_SMI_COMMAND_BLOCK:	/* 8-bit access */

		status =
		    acpi_hw_read_port(acpi_gbl_FADT.smi_command, &value, 8);
		break;

	default:
		ACPI_ERROR((AE_INFO, "Unknown Register ID: %X", register_id));
		status = AE_BAD_PARAMETER;
		break;
	}

	if (ACPI_SUCCESS(status)) {
		*return_value = value;
	}

	return_ACPI_STATUS(status);
}