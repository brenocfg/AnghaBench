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
struct acpi_buffer {int /*<<< orphan*/  pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
struct acpi_battery {int quirks; int rate_now; scalar_t__ update_time; int /*<<< orphan*/  lock; TYPE_1__* device; } ;
typedef  int /*<<< orphan*/  s16 ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int QUIRK_SIGNED16_CURRENT ; 
 int abs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_battery_present (struct acpi_battery*) ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,struct acpi_buffer*) ; 
 int /*<<< orphan*/  cache_time ; 
 int extract_package (struct acpi_battery*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  state_offsets ; 
 scalar_t__ time_before (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int acpi_battery_get_state(struct acpi_battery *battery)
{
	int result = 0;
	acpi_status status = 0;
	struct acpi_buffer buffer = { ACPI_ALLOCATE_BUFFER, NULL };

	if (!acpi_battery_present(battery))
		return 0;

	if (battery->update_time &&
	    time_before(jiffies, battery->update_time +
			msecs_to_jiffies(cache_time)))
		return 0;

	mutex_lock(&battery->lock);
	status = acpi_evaluate_object(battery->device->handle, "_BST",
				      NULL, &buffer);
	mutex_unlock(&battery->lock);

	if (ACPI_FAILURE(status)) {
		ACPI_EXCEPTION((AE_INFO, status, "Evaluating _BST"));
		return -ENODEV;
	}

	result = extract_package(battery, buffer.pointer,
				 state_offsets, ARRAY_SIZE(state_offsets));
	battery->update_time = jiffies;
	kfree(buffer.pointer);

	if ((battery->quirks & QUIRK_SIGNED16_CURRENT) &&
	    battery->rate_now != -1)
		battery->rate_now = abs((s16)battery->rate_now);

	return result;
}