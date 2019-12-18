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
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_BRIDGE_CONTROL ; 
 int /*<<< orphan*/  PCI_BRIDGE_CTL_BUS_RESET ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void aer_do_secondary_bus_reset(struct pci_dev *dev)
{
	u16 p2p_ctrl;

	/* Assert Secondary Bus Reset */
	pci_read_config_word(dev, PCI_BRIDGE_CONTROL, &p2p_ctrl);
	p2p_ctrl |= PCI_BRIDGE_CTL_BUS_RESET;
	pci_write_config_word(dev, PCI_BRIDGE_CONTROL, p2p_ctrl);

	/*
	 * we should send hot reset message for 2ms to allow it time to
	 * propagate to all downstream ports
	 */
	msleep(2);

	/* De-assert Secondary Bus Reset */
	p2p_ctrl &= ~PCI_BRIDGE_CTL_BUS_RESET;
	pci_write_config_word(dev, PCI_BRIDGE_CONTROL, p2p_ctrl);

	/*
	 * System software must wait for at least 100ms from the end
	 * of a reset of one or more device before it is permitted
	 * to issue Configuration Requests to those devices.
	 */
	msleep(200);
}