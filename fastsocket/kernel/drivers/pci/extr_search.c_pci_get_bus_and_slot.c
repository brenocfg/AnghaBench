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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 struct pci_dev* pci_get_domain_bus_and_slot (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

struct pci_dev *pci_get_bus_and_slot(unsigned int bus, unsigned int devfn)
{
	return pci_get_domain_bus_and_slot(0, bus, devfn);
}