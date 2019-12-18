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
struct topstar_hkey {int /*<<< orphan*/  inputdev; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 struct topstar_hkey* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_topstar_fncx_switch (struct acpi_device*,int) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct topstar_hkey*) ; 

__attribute__((used)) static int acpi_topstar_remove(struct acpi_device *device, int type)
{
	struct topstar_hkey *tps_hkey = acpi_driver_data(device);

	acpi_topstar_fncx_switch(device, false);

	input_unregister_device(tps_hkey->inputdev);
	kfree(tps_hkey);

	return 0;
}