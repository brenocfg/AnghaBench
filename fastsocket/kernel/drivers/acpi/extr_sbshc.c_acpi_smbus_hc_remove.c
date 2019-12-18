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
struct acpi_smb_hc {int /*<<< orphan*/  query_bit; int /*<<< orphan*/  ec; } ;
struct acpi_device {int /*<<< orphan*/ * driver_data; } ;

/* Variables and functions */
 int EINVAL ; 
 struct acpi_smb_hc* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_ec_remove_query_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct acpi_smb_hc*) ; 

__attribute__((used)) static int acpi_smbus_hc_remove(struct acpi_device *device, int type)
{
	struct acpi_smb_hc *hc;

	if (!device)
		return -EINVAL;

	hc = acpi_driver_data(device);
	acpi_ec_remove_query_handler(hc->ec, hc->query_bit);
	kfree(hc);
	device->driver_data = NULL;
	return 0;
}