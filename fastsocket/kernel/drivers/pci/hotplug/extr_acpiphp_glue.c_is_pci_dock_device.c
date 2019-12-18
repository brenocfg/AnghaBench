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
 scalar_t__ is_dock_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_status
is_pci_dock_device(acpi_handle handle, u32 lvl, void *context, void **rv)
{
	int *count = (int *)context;

	if (is_dock_device(handle)) {
		(*count)++;
		return AE_CTRL_TERMINATE;
	} else {
		return AE_OK;
	}
}