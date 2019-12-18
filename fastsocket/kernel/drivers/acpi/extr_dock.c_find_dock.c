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
 scalar_t__ dock_add (int /*<<< orphan*/ ) ; 
 scalar_t__ is_dock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_status
find_dock(acpi_handle handle, u32 lvl, void *context, void **rv)
{
	acpi_status status = AE_OK;

	if (is_dock(handle)) {
		if (dock_add(handle) >= 0) {
			status = AE_CTRL_TERMINATE;
		}
	}
	return status;
}