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
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  devfn; TYPE_1__* bus; } ;
struct TYPE_2__ {int number; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int PCI_SLOT (int /*<<< orphan*/ ) ; 
 int comedi_auto_config (int /*<<< orphan*/ *,char const*,int*,int /*<<< orphan*/ ) ; 

int comedi_pci_auto_config(struct pci_dev *pcidev, const char *board_name)
{
	int options[2];

	/*  pci bus */
	options[0] = pcidev->bus->number;
	/*  pci slot */
	options[1] = PCI_SLOT(pcidev->devfn);

	return comedi_auto_config(&pcidev->dev, board_name,
				  options, ARRAY_SIZE(options));
}