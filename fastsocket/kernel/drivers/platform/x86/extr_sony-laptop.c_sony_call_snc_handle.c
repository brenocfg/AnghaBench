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

/* Variables and functions */
 int acpi_callsetfunc (int /*<<< orphan*/ ,char*,int,int*) ; 
 int sony_find_snc_handle (int) ; 
 int /*<<< orphan*/  sony_nc_acpi_handle ; 

__attribute__((used)) static int sony_call_snc_handle(int handle, int argument, int *result)
{
	int offset = sony_find_snc_handle(handle);

	if (offset < 0)
		return -1;

	return acpi_callsetfunc(sony_nc_acpi_handle, "SN07", offset | argument,
				result);
}