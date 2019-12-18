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
typedef  int u64 ;
struct acpi_device {int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  METHOD_NAME__CRS ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  acpi_walk_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_notifier_chain_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic_notifier_list ; 
 int /*<<< orphan*/  port ; 
 int /*<<< orphan*/  pvpanic_panic_nb ; 
 int /*<<< orphan*/  pvpanic_walk_resources ; 

__attribute__((used)) static int pvpanic_add(struct acpi_device *device)
{
	acpi_status status;
	u64 ret;

	status = acpi_evaluate_integer(device->handle, "_STA", NULL,
				       &ret);

	if (ACPI_FAILURE(status) || (ret & 0x0B) != 0x0B)
		return -ENODEV;

	acpi_walk_resources(device->handle, METHOD_NAME__CRS,
			    pvpanic_walk_resources, NULL);

	if (!port)
		return -ENODEV;

	atomic_notifier_chain_register(&panic_notifier_list,
				       &pvpanic_panic_nb);

	return 0;
}