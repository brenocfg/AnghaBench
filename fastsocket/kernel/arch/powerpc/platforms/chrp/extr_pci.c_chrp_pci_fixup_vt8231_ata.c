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
typedef  int u8 ;
struct pci_dev {int irq; int class; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_CLASS_PROG ; 
 int /*<<< orphan*/  PCI_DEVICE_ID_VIA_8231 ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_VIA ; 
 scalar_t__ _CHRP_Pegasos ; 
 scalar_t__ _chrp_type ; 
 int /*<<< orphan*/  chrp ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  machine_is (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void chrp_pci_fixup_vt8231_ata(struct pci_dev *viaide)
{
	u8 progif;
	struct pci_dev *viaisa;

	if (!machine_is(chrp) || _chrp_type != _CHRP_Pegasos)
		return;
	if (viaide->irq != 14)
		return;

	viaisa = pci_get_device(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_8231, NULL);
	if (!viaisa)
		return;
	dev_info(&viaide->dev, "Fixing VIA IDE, force legacy mode on\n");

	pci_read_config_byte(viaide, PCI_CLASS_PROG, &progif);
	pci_write_config_byte(viaide, PCI_CLASS_PROG, progif & ~0x5);
	viaide->class &= ~0x5;

	pci_dev_put(viaisa);
}