#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int length; int /*<<< orphan*/ * pointer; } ;
union acpi_object {TYPE_1__ buffer; void* type; } ;
typedef  int /*<<< orphan*/  u8 ;
struct ide_acpi_drive_link {int /*<<< orphan*/  idbuff; } ;
struct acpi_object_list {int count; union acpi_object* pointer; } ;
struct GTM_buffer {int dummy; } ;
struct TYPE_7__ {TYPE_2__* acpidata; } ;
typedef  TYPE_3__ ide_hwif_t ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_6__ {int /*<<< orphan*/  obj_handle; int /*<<< orphan*/  gtm; struct ide_acpi_drive_link slave; struct ide_acpi_drive_link master; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 void* ACPI_TYPE_BUFFER ; 
 int ATA_ID_WORDS ; 
 int /*<<< orphan*/  DEBPRINT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,struct acpi_object_list*,int /*<<< orphan*/ *) ; 

void ide_acpi_push_timing(ide_hwif_t *hwif)
{
	acpi_status		status;
	struct acpi_object_list	input;
	union acpi_object 	in_params[3];
	struct ide_acpi_drive_link	*master = &hwif->acpidata->master;
	struct ide_acpi_drive_link	*slave = &hwif->acpidata->slave;

	/* Give the GTM buffer + drive Identify data to the channel via the
	 * _STM method: */
	/* setup input parameters buffer for _STM */
	input.count = 3;
	input.pointer = in_params;
	in_params[0].type = ACPI_TYPE_BUFFER;
	in_params[0].buffer.length = sizeof(struct GTM_buffer);
	in_params[0].buffer.pointer = (u8 *)&hwif->acpidata->gtm;
	in_params[1].type = ACPI_TYPE_BUFFER;
	in_params[1].buffer.length = ATA_ID_WORDS * 2;
	in_params[1].buffer.pointer = (u8 *)&master->idbuff;
	in_params[2].type = ACPI_TYPE_BUFFER;
	in_params[2].buffer.length = ATA_ID_WORDS * 2;
	in_params[2].buffer.pointer = (u8 *)&slave->idbuff;
	/* Output buffer: _STM has no output */

	status = acpi_evaluate_object(hwif->acpidata->obj_handle, "_STM",
				      &input, NULL);

	if (ACPI_FAILURE(status)) {
		DEBPRINT("Run _STM error: status = 0x%x\n", status);
	}
	DEBPRINT("_STM status: %d\n", status);
}