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
typedef  int /*<<< orphan*/  u64 ;
struct acpi_ioremap {int dummy; } ;
struct acpi_generic_address {scalar_t__ space_id; int bit_width; int /*<<< orphan*/  address; } ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 scalar_t__ ACPI_ADR_SPACE_SYSTEM_MEMORY ; 
 int /*<<< orphan*/  acpi_ioremap_lock ; 
 struct acpi_ioremap* acpi_map_lookup (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  acpi_os_drop_map_ref (struct acpi_ioremap*) ; 
 int /*<<< orphan*/  acpi_os_map_cleanup (struct acpi_ioremap*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void acpi_os_unmap_generic_address(struct acpi_generic_address *gas)
{
	u64 addr;
	struct acpi_ioremap *map;

	if (gas->space_id != ACPI_ADR_SPACE_SYSTEM_MEMORY)
		return;

	/* Handle possible alignment issues */
	memcpy(&addr, &gas->address, sizeof(addr));
	if (!addr || !gas->bit_width)
		return;

	mutex_lock(&acpi_ioremap_lock);
	map = acpi_map_lookup(addr, gas->bit_width / 8);
	if (!map) {
		mutex_unlock(&acpi_ioremap_lock);
		return;
	}
	acpi_os_drop_map_ref(map);
	mutex_unlock(&acpi_ioremap_lock);

	acpi_os_map_cleanup(map);
}