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
struct TYPE_4__ {int length; scalar_t__ pointer; } ;
union acpi_object {scalar_t__ type; TYPE_1__ buffer; } ;
struct wmab_ret {int eax; } ;
struct wmab_args {int ebx; scalar_t__ edx; scalar_t__ ecx; int /*<<< orphan*/  eax; } ;
struct acpi_buffer {scalar_t__ pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_6__ {int /*<<< orphan*/  capability; } ;
struct TYPE_5__ {scalar_t__ brightness; } ;

/* Variables and functions */
 int ACER_AMW0_BLUETOOTH_MASK ; 
 int ACER_AMW0_WIRELESS_MASK ; 
 int /*<<< orphan*/  ACER_AMW0_WRITE ; 
 int /*<<< orphan*/  ACER_CAP_BLUETOOTH ; 
 int /*<<< orphan*/  ACER_CAP_BRIGHTNESS ; 
 int /*<<< orphan*/  ACER_CAP_WIRELESS ; 
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_BUFFER ; 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AMW0_GUID2 ; 
 TYPE_3__* interface ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 TYPE_2__* quirks ; 
 int /*<<< orphan*/  wmab_execute (struct wmab_args*,struct acpi_buffer*) ; 
 scalar_t__ wmi_has_guid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_status AMW0_set_capabilities(void)
{
	struct wmab_args args;
	struct wmab_ret ret;
	acpi_status status = AE_OK;
	struct acpi_buffer out = { ACPI_ALLOCATE_BUFFER, NULL };
	union acpi_object *obj;

	/*
	 * On laptops with this strange GUID (non Acer), normal probing doesn't
	 * work.
	 */
	if (wmi_has_guid(AMW0_GUID2)) {
		interface->capability |= ACER_CAP_WIRELESS;
		return AE_OK;
	}

	args.eax = ACER_AMW0_WRITE;
	args.ecx = args.edx = 0;

	args.ebx = 0xa2 << 8;
	args.ebx |= ACER_AMW0_WIRELESS_MASK;

	status = wmab_execute(&args, &out);
	if (ACPI_FAILURE(status))
		return status;

	obj = (union acpi_object *) out.pointer;
	if (obj && obj->type == ACPI_TYPE_BUFFER &&
	obj->buffer.length == sizeof(struct wmab_ret)) {
		ret = *((struct wmab_ret *) obj->buffer.pointer);
	} else {
		return AE_ERROR;
	}

	if (ret.eax & 0x1)
		interface->capability |= ACER_CAP_WIRELESS;

	args.ebx = 2 << 8;
	args.ebx |= ACER_AMW0_BLUETOOTH_MASK;

	status = wmab_execute(&args, &out);
	if (ACPI_FAILURE(status))
		return status;

	obj = (union acpi_object *) out.pointer;
	if (obj && obj->type == ACPI_TYPE_BUFFER
	&& obj->buffer.length == sizeof(struct wmab_ret)) {
		ret = *((struct wmab_ret *) obj->buffer.pointer);
	} else {
		return AE_ERROR;
	}

	if (ret.eax & 0x1)
		interface->capability |= ACER_CAP_BLUETOOTH;

	kfree(out.pointer);

	/*
	 * This appears to be safe to enable, since all Wistron based laptops
	 * appear to use the same EC register for brightness, even if they
	 * differ for wireless, etc
	 */
	if (quirks->brightness >= 0)
		interface->capability |= ACER_CAP_BRIGHTNESS;

	return AE_OK;
}