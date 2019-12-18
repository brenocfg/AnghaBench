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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  AE_CTRL_TERMINATE ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ is_ejectable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_status
check_hotplug(acpi_handle handle, u32 lvl, void *context, void **rv)
{
	int *found = (int *)context;
	if (is_ejectable(handle)) {
		*found = 1;
		return AE_CTRL_TERMINATE;
	}
	return AE_OK;
}