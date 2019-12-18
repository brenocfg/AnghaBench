#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct st_hba {TYPE_1__* pdev; } ;
struct pci_bus {int /*<<< orphan*/  self; } ;
struct TYPE_4__ {int /*<<< orphan*/ * saved_config_space; struct pci_bus* bus; } ;

/* Variables and functions */
 int MU_HARD_RESET_WAIT ; 
 int /*<<< orphan*/  PCI_BRIDGE_CONTROL ; 
 int /*<<< orphan*/  PCI_BRIDGE_CTL_BUS_RESET ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int PCI_COMMAND_MASTER ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pci_read_config_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_dword (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_word (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_dword (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssleep (int) ; 

__attribute__((used)) static void stex_hard_reset(struct st_hba *hba)
{
	struct pci_bus *bus;
	int i;
	u16 pci_cmd;
	u8 pci_bctl;

	for (i = 0; i < 16; i++)
		pci_read_config_dword(hba->pdev, i * 4,
			&hba->pdev->saved_config_space[i]);

	/* Reset secondary bus. Our controller(MU/ATU) is the only device on
	   secondary bus. Consult Intel 80331/3 developer's manual for detail */
	bus = hba->pdev->bus;
	pci_read_config_byte(bus->self, PCI_BRIDGE_CONTROL, &pci_bctl);
	pci_bctl |= PCI_BRIDGE_CTL_BUS_RESET;
	pci_write_config_byte(bus->self, PCI_BRIDGE_CONTROL, pci_bctl);

	/*
	 * 1 ms may be enough for 8-port controllers. But 16-port controllers
	 * require more time to finish bus reset. Use 100 ms here for safety
	 */
	msleep(100);
	pci_bctl &= ~PCI_BRIDGE_CTL_BUS_RESET;
	pci_write_config_byte(bus->self, PCI_BRIDGE_CONTROL, pci_bctl);

	for (i = 0; i < MU_HARD_RESET_WAIT; i++) {
		pci_read_config_word(hba->pdev, PCI_COMMAND, &pci_cmd);
		if (pci_cmd != 0xffff && (pci_cmd & PCI_COMMAND_MASTER))
			break;
		msleep(1);
	}

	ssleep(5);
	for (i = 0; i < 16; i++)
		pci_write_config_dword(hba->pdev, i * 4,
			hba->pdev->saved_config_space[i]);
}