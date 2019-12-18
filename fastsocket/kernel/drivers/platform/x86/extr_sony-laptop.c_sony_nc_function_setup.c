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
struct acpi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_callsetfunc (int /*<<< orphan*/ ,char*,int,int*) ; 
 int /*<<< orphan*/  sony_call_snc_handle (int,int,int*) ; 
 int /*<<< orphan*/  sony_nc_acpi_handle ; 

__attribute__((used)) static int sony_nc_function_setup(struct acpi_device *device)
{
	int result;

	/* Enable all events */
	acpi_callsetfunc(sony_nc_acpi_handle, "SN02", 0xffff, &result);

	/* Setup hotkeys */
	sony_call_snc_handle(0x0100, 0, &result);
	sony_call_snc_handle(0x0101, 0, &result);
	sony_call_snc_handle(0x0102, 0x100, &result);
	sony_call_snc_handle(0x0127, 0, &result);

	return 0;
}