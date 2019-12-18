#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char const* mod_name; struct module* owner; int /*<<< orphan*/ * bus; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  list; int /*<<< orphan*/  lock; } ;
struct pci_driver {TYPE_2__ driver; TYPE_1__ dynids; int /*<<< orphan*/  name; } ;
struct module {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int driver_register (TYPE_2__*) ; 
 int /*<<< orphan*/  driver_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  pci_bus_type ; 
 int pci_create_newid_file (struct pci_driver*) ; 
 int pci_create_removeid_file (struct pci_driver*) ; 
 int /*<<< orphan*/  pci_remove_newid_file (struct pci_driver*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int __pci_register_driver(struct pci_driver *drv, struct module *owner,
			  const char *mod_name)
{
	int error;

	/* initialize common driver fields */
	drv->driver.name = drv->name;
	drv->driver.bus = &pci_bus_type;
	drv->driver.owner = owner;
	drv->driver.mod_name = mod_name;

	spin_lock_init(&drv->dynids.lock);
	INIT_LIST_HEAD(&drv->dynids.list);

	/* register with core */
	error = driver_register(&drv->driver);
	if (error)
		goto out;

	error = pci_create_newid_file(drv);
	if (error)
		goto out_newid;

	error = pci_create_removeid_file(drv);
	if (error)
		goto out_removeid;
out:
	return error;

out_removeid:
	pci_remove_newid_file(drv);
out_newid:
	driver_unregister(&drv->driver);
	goto out;
}