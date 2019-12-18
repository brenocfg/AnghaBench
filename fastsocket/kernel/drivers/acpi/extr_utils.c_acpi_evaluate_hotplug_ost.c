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
struct TYPE_4__ {scalar_t__ length; int /*<<< orphan*/ * pointer; } ;
struct TYPE_3__ {void* value; } ;
union acpi_object {TYPE_2__ buffer; TYPE_1__ integer; int /*<<< orphan*/  type; } ;
typedef  void* u32 ;
struct acpi_object_list {int member_0; union acpi_object* member_1; } ;
struct acpi_buffer {scalar_t__ length; int /*<<< orphan*/ * pointer; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_TYPE_BUFFER ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,struct acpi_object_list*,int /*<<< orphan*/ *) ; 

acpi_status
acpi_evaluate_hotplug_ost(acpi_handle handle, u32 source_event,
		u32 status_code, struct acpi_buffer *status_buf)
{
#ifdef ACPI_HOTPLUG_OST
	union acpi_object params[3] = {
		{.type = ACPI_TYPE_INTEGER,},
		{.type = ACPI_TYPE_INTEGER,},
		{.type = ACPI_TYPE_BUFFER,}
	};
	struct acpi_object_list arg_list = {3, params};
	acpi_status status;

	params[0].integer.value = source_event;
	params[1].integer.value = status_code;
	if (status_buf != NULL) {
		params[2].buffer.pointer = status_buf->pointer;
		params[2].buffer.length = status_buf->length;
	} else {
		params[2].buffer.pointer = NULL;
		params[2].buffer.length = 0;
	}

	status = acpi_evaluate_object(handle, "_OST", &arg_list, NULL);
	return status;
#else
	return AE_OK;
#endif
}