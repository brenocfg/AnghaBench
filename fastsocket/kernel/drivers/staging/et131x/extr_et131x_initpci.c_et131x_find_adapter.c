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
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int u8 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct et131x_adapter {int RegistryNMIDisable; int has_eeprom; int* eepromData; int* PermanentAddress; } ;
typedef  int int32_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ET1310_NMI_DISABLE ; 
 int /*<<< orphan*/  ET1310_PCI_ACK_NACK ; 
 int ET1310_PCI_EEPROM_STATUS ; 
 int ET1310_PCI_L0L1LATENCY ; 
 int ET1310_PCI_MAC_ADDRESS ; 
 int ET1310_PCI_MAX_PYLD ; 
 int /*<<< orphan*/  ET1310_PCI_REPLAY ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  EepromReadByte (struct et131x_adapter*,int,int*) ; 
 int /*<<< orphan*/  EepromWriteByte (struct et131x_adapter*,int,int) ; 
 int PCIBIOS_SUCCESSFUL ; 
 int PCI_REVISION_ID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 
 int pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int pci_write_config_byte (struct pci_dev*,int,int) ; 
 int pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int const) ; 

int et131x_find_adapter(struct et131x_adapter *adapter, struct pci_dev *pdev)
{
	int result;
	uint8_t eepromStat;
	uint8_t maxPayload = 0;
	uint8_t read_size_reg;
	u8 rev;

	/* Allow disabling of Non-Maskable Interrupts in I/O space, to
	 * support validation.
	 */
	if (adapter->RegistryNMIDisable) {
		uint8_t RegisterVal;

		RegisterVal = inb(ET1310_NMI_DISABLE);
		RegisterVal &= 0xf3;

		if (adapter->RegistryNMIDisable == 2)
			RegisterVal |= 0xc;

		outb(ET1310_NMI_DISABLE, RegisterVal);
	}

	/* We first need to check the EEPROM Status code located at offset
	 * 0xB2 of config space
	 */
	result = pci_read_config_byte(pdev, ET1310_PCI_EEPROM_STATUS,
				      &eepromStat);

	/* THIS IS A WORKAROUND:
	 * I need to call this function twice to get my card in a
	 * LG M1 Express Dual running. I tried also a msleep before this
	 * function, because I thougth there could be some time condidions
	 * but it didn't work. Call the whole function twice also work.
	 */
	result = pci_read_config_byte(pdev, ET1310_PCI_EEPROM_STATUS,
				      &eepromStat);
	if (result != PCIBIOS_SUCCESSFUL) {
		dev_err(&pdev->dev, "Could not read PCI config space for "
			  "EEPROM Status\n");
		return -EIO;
	}

	/* Determine if the error(s) we care about are present.  If they are
	 * present, we need to fail.
	 */
	if (eepromStat & 0x4C) {
		result = pci_read_config_byte(pdev, PCI_REVISION_ID, &rev);
		if (result != PCIBIOS_SUCCESSFUL) {
			dev_err(&pdev->dev,
				  "Could not read PCI config space for "
				  "Revision ID\n");
			return -EIO;
		} else if (rev == 0x01) {
			int32_t nLoop;
			uint8_t temp[4] = { 0xFE, 0x13, 0x10, 0xFF };

			/* Re-write the first 4 bytes if we have an eeprom
			 * present and the revision id is 1, this fixes the
			 * corruption seen with 1310 B Silicon
			 */
			for (nLoop = 0; nLoop < 3; nLoop++) {
				EepromWriteByte(adapter, nLoop, temp[nLoop]);
			}
		}

		dev_err(&pdev->dev, "Fatal EEPROM Status Error - 0x%04x\n", eepromStat);

		/* This error could mean that there was an error reading the
		 * eeprom or that the eeprom doesn't exist.  We will treat
		 * each case the same and not try to gather additional
		 * information that normally would come from the eeprom, like
		 * MAC Address
		 */
		adapter->has_eeprom = 0;
		return -EIO;
	} else
		adapter->has_eeprom = 1;

	/* Read the EEPROM for information regarding LED behavior. Refer to
	 * ET1310_phy.c, et131x_xcvr_init(), for its use.
	 */
	EepromReadByte(adapter, 0x70, &adapter->eepromData[0]);
	EepromReadByte(adapter, 0x71, &adapter->eepromData[1]);

	if (adapter->eepromData[0] != 0xcd)
		/* Disable all optional features */
		adapter->eepromData[1] = 0x00;

	/* Let's set up the PORT LOGIC Register.  First we need to know what
	 * the max_payload_size is
	 */
	result = pci_read_config_byte(pdev, ET1310_PCI_MAX_PYLD, &maxPayload);
	if (result != PCIBIOS_SUCCESSFUL) {
		dev_err(&pdev->dev,
		    "Could not read PCI config space for Max Payload Size\n");
		return -EIO;
	}

	/* Program the Ack/Nak latency and replay timers */
	maxPayload &= 0x07;	/* Only the lower 3 bits are valid */

	if (maxPayload < 2) {
		const uint16_t AckNak[2] = { 0x76, 0xD0 };
		const uint16_t Replay[2] = { 0x1E0, 0x2ED };

		result = pci_write_config_word(pdev, ET1310_PCI_ACK_NACK,
					       AckNak[maxPayload]);
		if (result != PCIBIOS_SUCCESSFUL) {
			dev_err(&pdev->dev,
			  "Could not write PCI config space for ACK/NAK\n");
			return -EIO;
		}

		result = pci_write_config_word(pdev, ET1310_PCI_REPLAY,
					       Replay[maxPayload]);
		if (result != PCIBIOS_SUCCESSFUL) {
			dev_err(&pdev->dev,
			  "Could not write PCI config space for Replay Timer\n");
			return -EIO;
		}
	}

	/* l0s and l1 latency timers.  We are using default values.
	 * Representing 001 for L0s and 010 for L1
	 */
	result = pci_write_config_byte(pdev, ET1310_PCI_L0L1LATENCY, 0x11);
	if (result != PCIBIOS_SUCCESSFUL) {
		dev_err(&pdev->dev,
		  "Could not write PCI config space for Latency Timers\n");
		return -EIO;
	}

	/* Change the max read size to 2k */
	result = pci_read_config_byte(pdev, 0x51, &read_size_reg);
	if (result != PCIBIOS_SUCCESSFUL) {
		dev_err(&pdev->dev,
			"Could not read PCI config space for Max read size\n");
		return -EIO;
	}

	read_size_reg &= 0x8f;
	read_size_reg |= 0x40;

	result = pci_write_config_byte(pdev, 0x51, read_size_reg);
	if (result != PCIBIOS_SUCCESSFUL) {
		dev_err(&pdev->dev,
		      "Could not write PCI config space for Max read size\n");
		return -EIO;
	}

	/* Get MAC address from config space if an eeprom exists, otherwise
	 * the MAC address there will not be valid
	 */
	if (adapter->has_eeprom) {
		int i;

		for (i = 0; i < ETH_ALEN; i++) {
			result = pci_read_config_byte(
					pdev, ET1310_PCI_MAC_ADDRESS + i,
					adapter->PermanentAddress + i);
			if (result != PCIBIOS_SUCCESSFUL) {
				dev_err(&pdev->dev, ";Could not read PCI config space for MAC address\n");
				return -EIO;
			}
		}
	}
	return 0;
}