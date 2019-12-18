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
struct TYPE_2__ {scalar_t__ pointer; } ;
union acpi_object {scalar_t__ type; TYPE_1__ buffer; } ;
struct bios_return {int return_code; int value; } ;
struct bios_args {int signature; int command; int commandtype; int datasize; int data; } ;
struct acpi_buffer {int member_0; union acpi_object* pointer; struct bios_args* member_1; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_TYPE_BUFFER ; 
 int EINVAL ; 
 int /*<<< orphan*/  HPWMI_BIOS_GUID ; 
 int /*<<< orphan*/  wmi_evaluate_method (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct acpi_buffer*,struct acpi_buffer*) ; 

__attribute__((used)) static int hp_wmi_perform_query(int query, int write, int value)
{
	struct bios_return bios_return;
	acpi_status status;
	union acpi_object *obj;
	struct bios_args args = {
		.signature = 0x55434553,
		.command = write ? 0x2 : 0x1,
		.commandtype = query,
		.datasize = write ? 0x4 : 0,
		.data = value,
	};
	struct acpi_buffer input = { sizeof(struct bios_args), &args };
	struct acpi_buffer output = { ACPI_ALLOCATE_BUFFER, NULL };

	status = wmi_evaluate_method(HPWMI_BIOS_GUID, 0, 0x3, &input, &output);

	obj = output.pointer;

	if (!obj || obj->type != ACPI_TYPE_BUFFER)
		return -EINVAL;

	bios_return = *((struct bios_return *)obj->buffer.pointer);
	if (bios_return.return_code > 0)
		return bios_return.return_code * -1;
	else
		return bios_return.value;
}