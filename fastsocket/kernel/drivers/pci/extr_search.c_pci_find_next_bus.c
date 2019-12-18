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
struct TYPE_2__ {struct list_head* next; } ;
struct pci_bus {TYPE_1__ node; } ;
struct list_head {struct list_head* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 struct pci_bus* pci_bus_b (struct list_head*) ; 
 int /*<<< orphan*/  pci_bus_sem ; 
 struct list_head pci_root_buses ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

struct pci_bus * 
pci_find_next_bus(const struct pci_bus *from)
{
	struct list_head *n;
	struct pci_bus *b = NULL;

	WARN_ON(in_interrupt());
	down_read(&pci_bus_sem);
	n = from ? from->node.next : pci_root_buses.next;
	if (n != &pci_root_buses)
		b = pci_bus_b(n);
	up_read(&pci_bus_sem);
	return b;
}