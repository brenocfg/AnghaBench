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
struct TYPE_4__ {int /*<<< orphan*/  pointer; int /*<<< orphan*/  length; } ;
struct TYPE_3__ {scalar_t__ value; } ;
union acpi_object {TYPE_2__ buffer; int /*<<< orphan*/  type; TYPE_1__ integer; } ;
typedef  scalar_t__ u8 ;
struct guid_block {scalar_t__ instance_count; int flags; int /*<<< orphan*/  object_id; } ;
struct wmi_block {int /*<<< orphan*/  handle; struct guid_block gblock; } ;
struct acpi_object_list {int count; union acpi_object* pointer; } ;
struct acpi_buffer {int /*<<< orphan*/  pointer; int /*<<< orphan*/  length; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_TYPE_BUFFER ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  ACPI_TYPE_STRING ; 
 int ACPI_WMI_EVENT ; 
 int ACPI_WMI_METHOD ; 
 int ACPI_WMI_STRING ; 
 int /*<<< orphan*/  AE_BAD_DATA ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,struct acpi_object_list*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_guid (char const*,struct wmi_block**) ; 
 int /*<<< orphan*/  strncat (char*,int /*<<< orphan*/ ,int) ; 

acpi_status wmi_set_block(const char *guid_string, u8 instance,
const struct acpi_buffer *in)
{
	struct guid_block *block = NULL;
	struct wmi_block *wblock = NULL;
	acpi_handle handle;
	struct acpi_object_list input;
	union acpi_object params[2];
	char method[5] = "WS";

	if (!guid_string || !in)
		return AE_BAD_DATA;

	if (!find_guid(guid_string, &wblock))
		return AE_ERROR;

	block = &wblock->gblock;
	handle = wblock->handle;

	if (block->instance_count < instance)
		return AE_BAD_PARAMETER;

	/* Check GUID is a data block */
	if (block->flags & (ACPI_WMI_EVENT | ACPI_WMI_METHOD))
		return AE_ERROR;

	input.count = 2;
	input.pointer = params;
	params[0].type = ACPI_TYPE_INTEGER;
	params[0].integer.value = instance;

	if (block->flags & ACPI_WMI_STRING) {
		params[1].type = ACPI_TYPE_STRING;
	} else {
		params[1].type = ACPI_TYPE_BUFFER;
	}
	params[1].buffer.length = in->length;
	params[1].buffer.pointer = in->pointer;

	strncat(method, block->object_id, 2);

	return acpi_evaluate_object(handle, method, &input, NULL);
}