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
typedef  int /*<<< orphan*/  u8 ;
struct pci_dev {int /*<<< orphan*/  devfn; } ;
struct i7core_dev {int n_devs; struct pci_dev** pdev; } ;

/* Variables and functions */
 unsigned int PCI_FUNC (int /*<<< orphan*/ ) ; 
 unsigned int PCI_SLOT (int /*<<< orphan*/ ) ; 
 struct i7core_dev* get_i7core_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pci_dev *get_pdev_slot_func(u8 socket, unsigned slot,
					  unsigned func)
{
	struct i7core_dev *i7core_dev = get_i7core_dev(socket);
	int i;

	if (!i7core_dev)
		return NULL;

	for (i = 0; i < i7core_dev->n_devs; i++) {
		if (!i7core_dev->pdev[i])
			continue;

		if (PCI_SLOT(i7core_dev->pdev[i]->devfn) == slot &&
		    PCI_FUNC(i7core_dev->pdev[i]->devfn) == func) {
			return i7core_dev->pdev[i];
		}
	}

	return NULL;
}