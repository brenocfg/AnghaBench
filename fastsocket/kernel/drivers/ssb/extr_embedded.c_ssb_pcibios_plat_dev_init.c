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
 int ENODEV ; 
 int /*<<< orphan*/  gige_pci_init_callback ; 
 int ssb_for_each_bus_call (unsigned long,int /*<<< orphan*/ ) ; 
 int ssb_pcicore_plat_dev_init (struct pci_dev*) ; 

int ssb_pcibios_plat_dev_init(struct pci_dev *dev)
{
	int err;

	err = ssb_pcicore_plat_dev_init(dev);
	if (!err)
		return 0;
#ifdef CONFIG_SSB_DRIVER_GIGE
	err = ssb_for_each_bus_call((unsigned long)dev, gige_pci_init_callback);
	if (err >= 0)
		return err;
#endif
	/* This is not a PCI device on any SSB device. */

	return -ENODEV;
}