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
typedef  int u32 ;
struct pci_dev {scalar_t__ revision; } ;
struct et131x_adapter {struct pci_dev* pdev; } ;

/* Variables and functions */
 int EXTRACT_CONTROL_REG (int) ; 
 int EXTRACT_STATUS_REGISTER (int) ; 
 int FAILURE ; 
 int /*<<< orphan*/  LBCIF_ADDRESS_REGISTER_OFFSET ; 
 int LBCIF_CONTROL_I2C_WRITE ; 
 int LBCIF_CONTROL_LBCIF_ENABLE ; 
 int /*<<< orphan*/  LBCIF_CONTROL_REGISTER_OFFSET ; 
 int /*<<< orphan*/  LBCIF_DATA_REGISTER_OFFSET ; 
 int /*<<< orphan*/  LBCIF_DWORD1_GROUP_OFFSET ; 
 int LBCIF_STATUS_ACK_ERROR ; 
 int LBCIF_STATUS_GENERAL_ERROR ; 
 int LBCIF_STATUS_I2C_IDLE ; 
 int LBCIF_STATUS_PHY_QUEUE_AVAIL ; 
 int MAX_NUM_REGISTER_POLLS ; 
 int MAX_NUM_WRITE_RETRIES ; 
 int SUCCESS ; 
 scalar_t__ pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

int EepromWriteByte(struct et131x_adapter *etdev, u32 addr, u8 data)
{
	struct pci_dev *pdev = etdev->pdev;
	int index;
	int retries;
	int err = 0;
	int i2c_wack = 0;
	int writeok = 0;
	u8 control;
	u8 status = 0;
	u32 dword1 = 0;
	u32 val = 0;

	/*
	 * The following excerpt is from "Serial EEPROM HW Design
	 * Specification" Version 0.92 (9/20/2004):
	 *
	 * Single Byte Writes
	 *
	 * For an EEPROM, an I2C single byte write is defined as a START
	 * condition followed by the device address, EEPROM address, one byte
	 * of data and a STOP condition.  The STOP condition will trigger the
	 * EEPROM's internally timed write cycle to the nonvolatile memory.
	 * All inputs are disabled during this write cycle and the EEPROM will
	 * not respond to any access until the internal write is complete.
	 * The steps to execute a single byte write are as follows:
	 *
	 * 1. Check LBCIF Status Register for bits 6 & 3:2 all equal to 0 and
	 *    bits 7,1:0 both equal to 1, at least once after reset.
	 *    Subsequent operations need only to check that bits 1:0 are
	 *    equal to 1 prior to starting a single byte write.
	 *
	 * 2. Write to the LBCIF Control Register:  bit 7=1, bit 6=1, bit 3=0,
	 *    and bits 1:0 both =0.  Bit 5 should be set according to the
	 *    type of EEPROM being accessed (1=two byte addressing, 0=one
	 *    byte addressing).
	 *
	 * 3. Write the address to the LBCIF Address Register.
	 *
	 * 4. Write the data to the LBCIF Data Register (the I2C write will
	 *    begin).
	 *
	 * 5. Monitor bit 1:0 of the LBCIF Status Register.  When bits 1:0 are
	 *    both equal to 1, the I2C write has completed and the internal
	 *    write cycle of the EEPROM is about to start. (bits 1:0 = 01 is
	 *    a legal state while waiting from both equal to 1, but bits
	 *    1:0 = 10 is invalid and implies that something is broken).
	 *
	 * 6. Check bit 3 of the LBCIF Status Register.  If  equal to 1, an
	 *    error has occurred.
	 *
	 * 7. Check bit 2 of the LBCIF Status Register.  If equal to 1 an ACK
	 *    error has occurred on the address phase of the write.  This
	 *    could be due to an actual hardware failure or the EEPROM may
	 *    still be in its internal write cycle from a previous write.
	 *    This write operation was ignored and must be repeated later.
	 *
	 * 8. Set bit 6 of the LBCIF Control Register = 0. If another write is
	 *    required, go to step 1.
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
			status & LBCIF_STATUS_I2C_IDLE)
			/* bits 1:0 are equal to 1 */
			break;
	}

	if (err || (index >= MAX_NUM_REGISTER_POLLS))
		return FAILURE;

	/* Step 2: */
	control = 0;
	control |= LBCIF_CONTROL_LBCIF_ENABLE | LBCIF_CONTROL_I2C_WRITE;

	if (pci_write_config_byte(pdev, LBCIF_CONTROL_REGISTER_OFFSET,
				  control)) {
		return FAILURE;
	}

	i2c_wack = 1;

	/* Prepare EEPROM address for Step 3 */

	for (retries = 0; retries < MAX_NUM_WRITE_RETRIES; retries++) {
		/* Step 3:*/
		if (pci_write_config_dword(pdev, LBCIF_ADDRESS_REGISTER_OFFSET,
					   addr)) {
			break;
		}

		/* Step 4: */
		if (pci_write_config_byte(pdev, LBCIF_DATA_REGISTER_OFFSET,
					  data)) {
			break;
		}

		/* Step 5: */
		for (index = 0; index < MAX_NUM_REGISTER_POLLS; index++) {
			/* Read registers grouped in DWORD1 */
			if (pci_read_config_dword(pdev,
						  LBCIF_DWORD1_GROUP_OFFSET,
						  &dword1)) {
				err = 1;
				break;
			}

			status = EXTRACT_STATUS_REGISTER(dword1);

			if (status & LBCIF_STATUS_PHY_QUEUE_AVAIL &&
				status & LBCIF_STATUS_I2C_IDLE) {
				/* I2C write complete */
				break;
			}
		}

		if (err || (index >= MAX_NUM_REGISTER_POLLS))
			break;

		/*
		 * Step 6: Don't break here if we are revision 1, this is
		 *	   so we do a blind write for load bug.
		 */
		if (status & LBCIF_STATUS_GENERAL_ERROR
		    && etdev->pdev->revision == 0) {
			break;
		}

		/* Step 7 */
		if (status & LBCIF_STATUS_ACK_ERROR) {
			/*
			 * This could be due to an actual hardware failure
			 * or the EEPROM may still be in its internal write
			 * cycle from a previous write. This write operation
			 * was ignored and must be repeated later.
			 */
			udelay(10);
			continue;
		}

		writeok = 1;
		break;
	}

	/* Step 8: */
	udelay(10);
	index = 0;
	while (i2c_wack) {
		control &= ~LBCIF_CONTROL_I2C_WRITE;

		if (pci_write_config_byte(pdev, LBCIF_CONTROL_REGISTER_OFFSET,
					  control)) {
			writeok = 0;
		}

		/* Do read until internal ACK_ERROR goes away meaning write
		 * completed
		 */
		do {
			pci_write_config_dword(pdev,
					       LBCIF_ADDRESS_REGISTER_OFFSET,
					       addr);
			do {
				pci_read_config_dword(pdev,
					LBCIF_DATA_REGISTER_OFFSET, &val);
			} while ((val & 0x00010000) == 0);
		} while (val & 0x00040000);

		control = EXTRACT_CONTROL_REG(val);

		if (control != 0xC0 || index == 10000)
			break;

		index++;
	}

	return writeok ? SUCCESS : FAILURE;
}