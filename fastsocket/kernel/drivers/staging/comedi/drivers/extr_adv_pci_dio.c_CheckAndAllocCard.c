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
struct pci_dio_private {struct pci_dev* pcidev; struct pci_dio_private* next; struct pci_dio_private* prev; } ;
struct pci_dev {int dummy; } ;
struct comedi_device {int dummy; } ;
struct comedi_devconfig {int dummy; } ;

/* Variables and functions */
 struct pci_dio_private* devpriv ; 
 struct pci_dio_private* pci_priv ; 

__attribute__((used)) static int CheckAndAllocCard(struct comedi_device *dev,
			     struct comedi_devconfig *it,
			     struct pci_dev *pcidev)
{
	struct pci_dio_private *pr, *prev;

	for (pr = pci_priv, prev = NULL; pr != NULL; prev = pr, pr = pr->next) {
		if (pr->pcidev == pcidev) {
			return 0;	/*  this card is used, look for another */
		}
	}

	if (prev) {
		devpriv->prev = prev;
		prev->next = devpriv;
	} else {
		pci_priv = devpriv;
	}

	devpriv->pcidev = pcidev;

	return 1;
}