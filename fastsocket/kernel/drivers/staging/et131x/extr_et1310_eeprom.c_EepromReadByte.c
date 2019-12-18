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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int dummy; } ;
struct et131x_adapter {struct pci_dev* pdev; } ;

/* Variables and functions */
 int EXTRACT_DATA_REGISTER (int /*<<< orphan*/ ) ; 
 int EXTRACT_STATUS_REGISTER (int /*<<< orphan*/ ) ; 
 int FAILURE ; 
 int /*<<< orphan*/  LBCIF_ADDRESS_REGISTER_OFFSET ; 
 int LBCIF_CONTROL_LBCIF_ENABLE ; 
 int /*<<< orphan*/  LBCIF_CONTROL_REGISTER_OFFSET ; 
 int /*<<< orphan*/  LBCIF_DWORD1_GROUP_OFFSET ; 
 int LBCIF_STATUS_ACK_ERROR ; 
 int LBCIF_STATUS_I2C_IDLE ; 
 int LBCIF_STATUS_PHY_QUEUE_AVAIL ; 
 int MAX_NUM_REGISTER_POLLS ; 
 int SUCCESS ; 
 scalar_t__ pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int EepromReadByte(struct et131x_adapter *etdev, u32 addr, u8 *pdata)
{
	struct pci_dev *pdev = etdev->pdev;
	int index;
	int err = 0;
	u8 control;
	u8 status = 0;
	u32 dword1 = 0;

	/*
	 * The following excerpt is from "Serial EEPROM HW Design
	 * Specification" Version 0.92 (9/20/2004):
	 *
	 * Single Byte Reads
	 *
	 * A single byte read is similar to the single byte write, with the
	 * exception of the data flow:
	 *
	 * 1. Check LBCIF Status Register for bits 6 & 3:2 all equal to 0 and
	 *    bits 7,1:0 both equal to 1, at least once after reset.
	 *    Subsequent operations need only to check that bits 1:0 are equal
	 *    to 1 prior to starting a single byte read.
	 *
	 * 2. Write to the LBCIF Control Register:  bit 7=1, bit 6=0, bit 3=0,
	 *    and bits 1:0 both =0.  Bit 5 should be set according to the type
	 *    of EEPROM being accessed (1=two byte addressing, 0=one byte
	 *    addressing).
	 *
	 * 3. Write the address to the LBCIF Address Register (I2C read will
	 *    begin).
	 *
	 * 4. Monitor bit 0 of the LBCIF Status Register.  When =1, I2C read
	 *    is complete. (if bit 1 =1 and bit 0 stays =0, a hardware failure
	 *    has occurred).
	 *
	 * 5. Check bit 2 of the LBCIF Status Register.  If =1, then an error
	 *    has occurred.  The data that has been returned from the PHY may
	 *    be invalid.
	 *
	 * 6. Regardless of error status, read data byte from LBCIF Data
	 *    Register.  If another byte is required, go to step 1.
	 */

	/* Step 1: */
	for (index = 0; index < MAX_NUM_REGISTER_POLLS; index++) {
		/* Read registers grouped in DWORD1 */
		if (pci_read_config_dword(pdev, LBCIF_DWORD1_GROUP_OFFSET,
					  &dword1)) {
			err = 1;
			break;
		}

		status = EXTRACT_STATUS_REGISTER(dword1);

		if (status & LBCIF_STATUS_PHY_QUEUE_AVAIL &&
		    status & LBCIF_STATUS_I2C_IDLE) {
			/* bits 1:0 are equal to 1 */
			break;
		}
	}

	if (err || (index >= MAX_NUM_REGISTER_POLLS))
		return FAILURE;

	/* Step 2: */
	control = 0;
	control |= LBCIF_CONTROL_LBCIF_ENABLE;

	if (pci_write_config_byte(pdev, LBCIF_CONTROL_REGISTER_OFFSET,
				  control)) {
		return FAILURE;
	}

	/* Step 3: */

	if (pci_write_config_dword(pdev, LBCIF_ADDRESS_REGISTER_OFFSET,
				   addr)) {
		return FAILURE;
	}

	/* Step 4: */
	for (index = 0; index < MAX_NUM_REGISTER_POLLS; index++) {
		/* Read registers grouped in DWORD1 */
		if (pci_read_config_dword(pdev, LBCIF_DWORD1_GROUP_OFFSET,
					  &dword1)) {
			err = 1;
			break;
		}

		status = EXTRACT_STATUS_REGISTER(dword1);

		if (status & LBCIF_STATUS_PHY_QUEUE_AVAIL
		    && status & LBCIF_STATUS_I2C_IDLE) {
			/* I2C read complete */
			break;
		}
	}

	if (err || (index >= MAX_NUM_REGISTER_POLLS))
		return FAILURE;

	/* Step 6: */
	*pdata = EXTRACT_DATA_REGISTER(dword1);

	return (status & LBCIF_STATUS_ACK_ERROR) ? FAILURE : SUCCESS;
}