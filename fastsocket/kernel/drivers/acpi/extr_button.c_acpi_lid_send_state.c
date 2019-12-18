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
struct acpi_device {int /*<<< orphan*/  handle; } ;
struct acpi_button {int /*<<< orphan*/  input; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int NOTIFY_DONE ; 
 int NOTIFY_OK ; 
 int /*<<< orphan*/  SW_LID ; 
 struct acpi_button* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 int /*<<< orphan*/  acpi_lid_notifier ; 
 int blocking_notifier_call_chain (int /*<<< orphan*/ *,unsigned long long,struct acpi_device*) ; 
 int /*<<< orphan*/  input_report_switch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acpi_lid_send_state(struct acpi_device *device)
{
	struct acpi_button *button = acpi_driver_data(device);
	unsigned long long state;
	acpi_status status;
	int ret;

	status = acpi_evaluate_integer(device->handle, "_LID", NULL, &state);
	if (ACPI_FAILURE(status))
		return -ENODEV;

	/* input layer checks if event is redundant */
	input_report_switch(button->input, SW_LID, !state);
	input_sync(button->input);

	ret = blocking_notifier_call_chain(&acpi_lid_notifier, state, device);
	if (ret == NOTIFY_DONE)
		ret = blocking_notifier_call_chain(&acpi_lid_notifier, state,
						   device);
	if (ret == NOTIFY_DONE || ret == NOTIFY_OK) {
		/*
		 * It is also regarded as success if the notifier_chain
		 * returns NOTIFY_OK or NOTIFY_DONE.
		 */
		ret = 0;
	}
	return ret;
}