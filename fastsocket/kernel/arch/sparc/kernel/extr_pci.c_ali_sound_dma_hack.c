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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DEVICE_ID_AL_M1533 ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_AL ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 

__attribute__((used)) static void ali_sound_dma_hack(struct pci_dev *pdev, int set_bit)
{
	struct pci_dev *ali_isa_bridge;
	u8 val;

	/* ALI sound chips generate 31-bits of DMA, a special register
	 * determines what bit 31 is emitted as.
	 */
	ali_isa_bridge = pci_get_device(PCI_VENDOR_ID_AL,
					 PCI_DEVICE_ID_AL_M1533,
					 NULL);

	pci_read_config_byte(ali_isa_bridge, 0x7e, &val);
	if (set_bit)
		val |= 0x01;
	else
		val &= ~0x01;
	pci_write_config_byte(ali_isa_bridge, 0x7e, val);
	pci_dev_put(ali_isa_bridge);
}