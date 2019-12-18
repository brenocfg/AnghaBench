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
struct acpi_ioremap {int /*<<< orphan*/  virt; int /*<<< orphan*/  phys; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct acpi_ioremap*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static void acpi_os_map_cleanup(struct acpi_ioremap *map)
{
	if (!map->refcount) {
		synchronize_rcu();
		acpi_unmap(map->phys, map->virt);
		kfree(map);
	}
}