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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  acpi_handle ;
typedef  int /*<<< orphan*/  acpi_event_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_NOT_ISR ; 
 scalar_t__ ACPI_NUM_FIXED_EVENTS ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NOT_FOUND ; 
 int acpi_get_event_status (scalar_t__,int /*<<< orphan*/ *) ; 
 int acpi_get_gpe_device (scalar_t__,int /*<<< orphan*/ *) ; 
 int acpi_get_gpe_status (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ num_gpes ; 

__attribute__((used)) static int get_status(u32 index, acpi_event_status *status, acpi_handle *handle)
{
	int result = 0;

	if (index >= num_gpes + ACPI_NUM_FIXED_EVENTS)
		goto end;

	if (index < num_gpes) {
		result = acpi_get_gpe_device(index, handle);
		if (result) {
			ACPI_EXCEPTION((AE_INFO, AE_NOT_FOUND,
				"Invalid GPE 0x%x\n", index));
			goto end;
		}
		result = acpi_get_gpe_status(*handle, index,
						ACPI_NOT_ISR, status);
	} else if (index < (num_gpes + ACPI_NUM_FIXED_EVENTS))
		result = acpi_get_event_status(index - num_gpes, status);

end:
	return result;
}