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
 int /*<<< orphan*/  acpi_callsetfunc (int /*<<< orphan*/ ,char*,int,int*) ; 
 int /*<<< orphan*/  sony_nc_acpi_handle ; 

__attribute__((used)) static int sony_find_snc_handle(int handle)
{
	int i;
	int result;

	for (i = 0x20; i < 0x30; i++) {
		acpi_callsetfunc(sony_nc_acpi_handle, "SN00", i, &result);
		if (result == handle)
			return i-0x20;
	}

	return -1;
}