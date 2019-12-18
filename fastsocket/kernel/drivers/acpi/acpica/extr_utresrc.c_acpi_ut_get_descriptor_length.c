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

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 scalar_t__ acpi_ut_get_resource_header_length (void*) ; 
 scalar_t__ acpi_ut_get_resource_length (void*) ; 

u32 acpi_ut_get_descriptor_length(void *aml)
{
	ACPI_FUNCTION_ENTRY();

	/*
	 * Get the Resource Length (does not include header length) and add
	 * the header length (depends on if this is a small or large resource)
	 */
	return (acpi_ut_get_resource_length(aml) +
		acpi_ut_get_resource_header_length(aml));
}