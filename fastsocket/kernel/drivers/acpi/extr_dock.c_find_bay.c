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
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  dock_add (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_dock (int /*<<< orphan*/ ) ; 
 scalar_t__ is_ejectable_bay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_status
find_bay(acpi_handle handle, u32 lvl, void *context, void **rv)
{
	/* If bay is a dock, it's already handled */
	if (is_ejectable_bay(handle) && !is_dock(handle))
		dock_add(handle);
	return AE_OK;
}