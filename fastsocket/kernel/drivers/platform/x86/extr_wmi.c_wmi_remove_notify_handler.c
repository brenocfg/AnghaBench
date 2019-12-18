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
struct wmi_block {int /*<<< orphan*/ * handler_data; int /*<<< orphan*/ * handler; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_NOT_EXIST ; 
 int /*<<< orphan*/  AE_NULL_ENTRY ; 
 int /*<<< orphan*/  find_guid (char const*,struct wmi_block**) ; 
 int /*<<< orphan*/  wmi_method_enable (struct wmi_block*,int /*<<< orphan*/ ) ; 

acpi_status wmi_remove_notify_handler(const char *guid)
{
	struct wmi_block *block;
	acpi_status status;

	if (!guid)
		return AE_BAD_PARAMETER;

	find_guid(guid, &block);
	if (!block)
		return AE_NOT_EXIST;

	if (!block->handler)
		return AE_NULL_ENTRY;

	status = wmi_method_enable(block, 0);

	block->handler = NULL;
	block->handler_data = NULL;

	return status;
}