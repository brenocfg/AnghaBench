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

/* Variables and functions */
 scalar_t__ AMCC_OP_REG_MCSR ; 
 unsigned int EEPROM_BUSY ; 
 unsigned char NVCMD_BEGIN_READ ; 
 unsigned char NVCMD_LOAD_HIGH ; 
 unsigned char NVCMD_LOAD_LOW ; 
 unsigned char inb (scalar_t__) ; 
 unsigned int inl (scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 

int i_AddiHeaderRW_ReadEeprom(int i_NbOfWordsToRead,
	unsigned int dw_PCIBoardEepromAddress,
	unsigned short w_EepromStartAddress, unsigned short *pw_DataRead)
{
	unsigned int dw_eeprom_busy = 0;
	int i_Counter = 0;
	int i_WordCounter;
	int i;
	unsigned char pb_ReadByte[1];
	unsigned char b_ReadLowByte = 0;
	unsigned char b_ReadHighByte = 0;
	unsigned char b_SelectedAddressLow = 0;
	unsigned char b_SelectedAddressHigh = 0;
	unsigned short w_ReadWord = 0;

	for (i_WordCounter = 0; i_WordCounter < i_NbOfWordsToRead;
		i_WordCounter++) {
		do {
			dw_eeprom_busy =
				inl(dw_PCIBoardEepromAddress +
				AMCC_OP_REG_MCSR);
			dw_eeprom_busy = dw_eeprom_busy & EEPROM_BUSY;
		} while (dw_eeprom_busy == EEPROM_BUSY);

		for (i_Counter = 0; i_Counter < 2; i_Counter++) {
			b_SelectedAddressLow = (w_EepromStartAddress + i_Counter) % 256;	/* Read the low 8 bit part */
			b_SelectedAddressHigh = (w_EepromStartAddress + i_Counter) / 256;	/* Read the high 8 bit part */

			/* Select the load low address mode */
			outb(NVCMD_LOAD_LOW,
				dw_PCIBoardEepromAddress + AMCC_OP_REG_MCSR +
				3);

			/* Wait on busy */
			do {
				dw_eeprom_busy =
					inl(dw_PCIBoardEepromAddress +
					AMCC_OP_REG_MCSR);
				dw_eeprom_busy = dw_eeprom_busy & EEPROM_BUSY;
			} while (dw_eeprom_busy == EEPROM_BUSY);

			/* Load the low address */
			outb(b_SelectedAddressLow,
				dw_PCIBoardEepromAddress + AMCC_OP_REG_MCSR +
				2);

			/* Wait on busy */
			do {
				dw_eeprom_busy =
					inl(dw_PCIBoardEepromAddress +
					AMCC_OP_REG_MCSR);
				dw_eeprom_busy = dw_eeprom_busy & EEPROM_BUSY;
			} while (dw_eeprom_busy == EEPROM_BUSY);

			/* Select the load high address mode */
			outb(NVCMD_LOAD_HIGH,
				dw_PCIBoardEepromAddress + AMCC_OP_REG_MCSR +
				3);

			/* Wait on busy */
			do {
				dw_eeprom_busy =
					inl(dw_PCIBoardEepromAddress +
					AMCC_OP_REG_MCSR);
				dw_eeprom_busy = dw_eeprom_busy & EEPROM_BUSY;
			} while (dw_eeprom_busy == EEPROM_BUSY);

			/* Load the high address */
			outb(b_SelectedAddressHigh,
				dw_PCIBoardEepromAddress + AMCC_OP_REG_MCSR +
				2);

			/* Wait on busy */
			do {
				dw_eeprom_busy =
					inl(dw_PCIBoardEepromAddress +
					AMCC_OP_REG_MCSR);
				dw_eeprom_busy = dw_eeprom_busy & EEPROM_BUSY;
			} while (dw_eeprom_busy == EEPROM_BUSY);

			/* Select the READ mode */
			outb(NVCMD_BEGIN_READ,
				dw_PCIBoardEepromAddress + AMCC_OP_REG_MCSR +
				3);

			/* Wait on busy */
			do {
				dw_eeprom_busy =
					inl(dw_PCIBoardEepromAddress +
					AMCC_OP_REG_MCSR);
				dw_eeprom_busy = dw_eeprom_busy & EEPROM_BUSY;
			} while (dw_eeprom_busy == EEPROM_BUSY);

			/* Read data into the EEPROM */
			*pb_ReadByte =
				inb(dw_PCIBoardEepromAddress +
				AMCC_OP_REG_MCSR + 2);

			/* Wait on busy */
			do {
				dw_eeprom_busy =
					inl(dw_PCIBoardEepromAddress +
					AMCC_OP_REG_MCSR);
				dw_eeprom_busy = dw_eeprom_busy & EEPROM_BUSY;
			} while (dw_eeprom_busy == EEPROM_BUSY);

			/* Select the upper address part */
			if (i_Counter == 0) {
				b_ReadLowByte = pb_ReadByte[0];
			} else {
				b_ReadHighByte = pb_ReadByte[0];
			}

			/* Sleep */
			msleep(1);

		}
		w_ReadWord =
			(b_ReadLowByte | (((unsigned short)b_ReadHighByte) *
				256));

		pw_DataRead[i_WordCounter] = w_ReadWord;

		w_EepromStartAddress += 2;	/*  to read the next word */

	}			/*  for (...) i_NbOfWordsToRead */
	return 0;
}