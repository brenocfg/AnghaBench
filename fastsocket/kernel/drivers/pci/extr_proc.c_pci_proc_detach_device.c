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
struct proc_dir_entry {int /*<<< orphan*/  name; } ;
struct pci_dev {struct proc_dir_entry* procent; TYPE_1__* bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  procdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  remove_proc_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pci_proc_detach_device(struct pci_dev *dev)
{
	struct proc_dir_entry *e;

	if ((e = dev->procent)) {
		remove_proc_entry(e->name, dev->bus->procdir);
		dev->procent = NULL;
	}
	return 0;
}