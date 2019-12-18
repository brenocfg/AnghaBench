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
typedef  int /*<<< orphan*/  u32 ;
struct pci_controller {TYPE_1__* io_space; } ;
struct pci_bus {struct pci_controller* sysdata; } ;
typedef  int loff_t ;
struct TYPE_2__ {scalar_t__ start; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (int,int /*<<< orphan*/ ) ; 

int pci_legacy_write(struct pci_bus *bus, loff_t port, u32 val, size_t size)
{
	struct pci_controller *hose = bus->sysdata;

	port += hose->io_space->start;

	switch(size) {
	case 1:
		outb(port, val);
		return 1;
	case 2:
		if (port & 1)
			return -EINVAL;
		outw(port, val);
		return 2;
	case 4:
		if (port & 3)
			return -EINVAL;
		outl(port, val);
		return 4;
	}
	return -EINVAL;
}