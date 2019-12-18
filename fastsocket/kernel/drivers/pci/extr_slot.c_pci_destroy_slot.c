#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  refcount; } ;
struct TYPE_6__ {TYPE_2__ kref; } ;
struct pci_slot {TYPE_3__ kobj; int /*<<< orphan*/  number; TYPE_1__* bus; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (TYPE_3__*) ; 
 int /*<<< orphan*/  pci_bus_sem ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void pci_destroy_slot(struct pci_slot *slot)
{
	dev_dbg(&slot->bus->dev, "dev %02x, dec refcount to %d\n",
		slot->number, atomic_read(&slot->kobj.kref.refcount) - 1);

	down_write(&pci_bus_sem);
	kobject_put(&slot->kobj);
	up_write(&pci_bus_sem);
}