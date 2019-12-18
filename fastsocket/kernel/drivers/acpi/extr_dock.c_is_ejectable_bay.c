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
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_get_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ is_ata (int /*<<< orphan*/ ) ; 
 scalar_t__ is_battery (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_ejectable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_ejectable_bay(acpi_handle handle)
{
	acpi_handle phandle;
	if (!is_ejectable(handle))
		return 0;
	if (is_battery(handle) || is_ata(handle))
		return 1;
	if (!acpi_get_parent(handle, &phandle) && is_ata(phandle))
		return 1;
	return 0;
}