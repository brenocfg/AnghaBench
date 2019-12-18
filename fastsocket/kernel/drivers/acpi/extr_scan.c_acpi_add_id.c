#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct acpi_hardware_id {int /*<<< orphan*/  list; void* id; } ;
struct TYPE_2__ {int /*<<< orphan*/  ids; } ;
struct acpi_device {TYPE_1__ pnp; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct acpi_hardware_id*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (void*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void acpi_add_id(struct acpi_device *device, const char *dev_id)
{
	struct acpi_hardware_id *id;

	id = kmalloc(sizeof(*id), GFP_KERNEL);
	if (!id)
		return;

	id->id = kmalloc(strlen(dev_id) + 1, GFP_KERNEL);
	if (!id->id) {
		kfree(id);
		return;
	}

	strcpy(id->id, dev_id);
	list_add_tail(&id->list, &device->pnp.ids);
}