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
struct TYPE_2__ {int value; } ;
union acpi_object {TYPE_1__ integer; void* type; } ;
typedef  scalar_t__ u8 ;
struct guid_block {scalar_t__ instance_count; int flags; int /*<<< orphan*/  object_id; } ;
struct wmi_block {int /*<<< orphan*/  handle; struct guid_block gblock; } ;
struct acpi_object_list {int count; union acpi_object* pointer; } ;
struct acpi_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 void* ACPI_TYPE_INTEGER ; 
 int ACPI_WMI_EVENT ; 
 int ACPI_WMI_EXPENSIVE ; 
 int ACPI_WMI_METHOD ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,struct acpi_object_list*,struct acpi_buffer*) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_guid (char const*,struct wmi_block**) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strncat (char*,int /*<<< orphan*/ ,int) ; 

acpi_status wmi_query_block(const char *guid_string, u8 instance,
struct acpi_buffer *out)
{
	struct guid_block *block = NULL;
	struct wmi_block *wblock = NULL;
	acpi_handle handle, wc_handle;
	acpi_status status, wc_status = AE_ERROR;
	struct acpi_object_list input, wc_input;
	union acpi_object wc_params[1], wq_params[1];
	char method[5];
	char wc_method[5] = "WC";

	if (!guid_string || !out)
		return AE_BAD_PARAMETER;

	if (!find_guid(guid_string, &wblock))
		return AE_ERROR;

	block = &wblock->gblock;
	handle = wblock->handle;

	if (block->instance_count < instance)
		return AE_BAD_PARAMETER;

	/* Check GUID is a data block */
	if (block->flags & (ACPI_WMI_EVENT | ACPI_WMI_METHOD))
		return AE_ERROR;

	input.count = 1;
	input.pointer = wq_params;
	wq_params[0].type = ACPI_TYPE_INTEGER;
	wq_params[0].integer.value = instance;

	/*
	 * If ACPI_WMI_EXPENSIVE, call the relevant WCxx method first to
	 * enable collection.
	 */
	if (block->flags & ACPI_WMI_EXPENSIVE) {
		wc_input.count = 1;
		wc_input.pointer = wc_params;
		wc_params[0].type = ACPI_TYPE_INTEGER;
		wc_params[0].integer.value = 1;

		strncat(wc_method, block->object_id, 2);

		/*
		 * Some GUIDs break the specification by declaring themselves
		 * expensive, but have no corresponding WCxx method. So we
		 * should not fail if this happens.
		 */
		wc_status = acpi_get_handle(handle, wc_method, &wc_handle);
		if (ACPI_SUCCESS(wc_status))
			wc_status = acpi_evaluate_object(handle, wc_method,
				&wc_input, NULL);
	}

	strcpy(method, "WQ");
	strncat(method, block->object_id, 2);

	status = acpi_evaluate_object(handle, method, &input, out);

	/*
	 * If ACPI_WMI_EXPENSIVE, call the relevant WCxx method, even if
	 * the WQxx method failed - we should disable collection anyway.
	 */
	if ((block->flags & ACPI_WMI_EXPENSIVE) && ACPI_SUCCESS(wc_status)) {
		wc_params[0].integer.value = 0;
		status = acpi_evaluate_object(handle,
		wc_method, &wc_input, NULL);
	}

	return status;
}