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
struct us_data {unsigned char* iobuf; } ;
struct scsi_cmnd {int cmd_len; unsigned char* cmnd; scalar_t__ sc_data_direction; } ;

/* Variables and functions */
 scalar_t__ DMA_FROM_DEVICE ; 
 scalar_t__ DMA_TO_DEVICE ; 
 scalar_t__ GPCMD_BLANK ; 
 scalar_t__ GPCMD_READ_CD ; 
 scalar_t__ READ_10 ; 
 scalar_t__ TEST_UNIT_READY ; 
 int /*<<< orphan*/  USBAT_ATA ; 
 unsigned char USBAT_ATA_CMD ; 
 int /*<<< orphan*/  USBAT_ATA_DATA ; 
 unsigned char USBAT_ATA_DEVICE ; 
 unsigned char USBAT_ATA_FEATURES ; 
 unsigned char USBAT_ATA_LBA_HI ; 
 unsigned char USBAT_ATA_LBA_ME ; 
 unsigned char USBAT_ATA_SECCNT ; 
 unsigned char USBAT_ATA_SECNUM ; 
 int /*<<< orphan*/  USBAT_ATA_STATUS ; 
 int USBAT_QUAL_ALQ ; 
 int USBAT_QUAL_FCQ ; 
 int USB_STOR_TRANSPORT_ERROR ; 
 int USB_STOR_TRANSPORT_GOOD ; 
 int USB_STOR_XFER_GOOD ; 
 int /*<<< orphan*/  US_DEBUGP (char*,unsigned int) ; 
 unsigned int scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sg_count (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sglist (struct scsi_cmnd*) ; 
 unsigned int transferred ; 
 int usbat_get_status (struct us_data*,unsigned char*) ; 
 int usbat_hp8200e_handle_read10 (struct us_data*,unsigned char*,unsigned char*,struct scsi_cmnd*) ; 
 int usbat_hp8200e_rw_block_test (struct us_data*,int /*<<< orphan*/ ,unsigned char*,unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,scalar_t__,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int) ; 
 int usbat_multiple_write (struct us_data*,unsigned char*,unsigned char*,int) ; 
 int usbat_read (struct us_data*,int /*<<< orphan*/ ,unsigned char,unsigned char*) ; 
 int usbat_read_block (struct us_data*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int usbat_write_block (struct us_data*,int /*<<< orphan*/ ,scalar_t__*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbat_hp8200e_transport(struct scsi_cmnd *srb, struct us_data *us)
{
	int result;
	unsigned char *status = us->iobuf;
	unsigned char registers[32];
	unsigned char data[32];
	unsigned int len;
	int i;

	len = scsi_bufflen(srb);

	/* Send A0 (ATA PACKET COMMAND).
	   Note: I guess we're never going to get any of the ATA
	   commands... just ATA Packet Commands.
 	 */

	registers[0] = USBAT_ATA_FEATURES;
	registers[1] = USBAT_ATA_SECCNT;
	registers[2] = USBAT_ATA_SECNUM;
	registers[3] = USBAT_ATA_LBA_ME;
	registers[4] = USBAT_ATA_LBA_HI;
	registers[5] = USBAT_ATA_DEVICE;
	registers[6] = USBAT_ATA_CMD;
	data[0] = 0x00;
	data[1] = 0x00;
	data[2] = 0x00;
	data[3] = len&0xFF; 		/* (cylL) = expected length (L) */
	data[4] = (len>>8)&0xFF; 	/* (cylH) = expected length (H) */
	data[5] = 0xB0; 		/* (device sel) = slave */
	data[6] = 0xA0; 		/* (command) = ATA PACKET COMMAND */

	for (i=7; i<19; i++) {
		registers[i] = 0x10;
		data[i] = (i-7 >= srb->cmd_len) ? 0 : srb->cmnd[i-7];
	}

	result = usbat_get_status(us, status);
	US_DEBUGP("Status = %02X\n", *status);
	if (result != USB_STOR_XFER_GOOD)
		return USB_STOR_TRANSPORT_ERROR;
	if (srb->cmnd[0] == TEST_UNIT_READY)
		transferred = 0;

	if (srb->sc_data_direction == DMA_TO_DEVICE) {

		result = usbat_hp8200e_rw_block_test(us, USBAT_ATA, 
			registers, data, 19,
			USBAT_ATA_DATA, USBAT_ATA_STATUS, 0xFD,
			(USBAT_QUAL_FCQ | USBAT_QUAL_ALQ),
			DMA_TO_DEVICE,
			scsi_sglist(srb),
			len, scsi_sg_count(srb), 10);

		if (result == USB_STOR_TRANSPORT_GOOD) {
			transferred += len;
			US_DEBUGP("Wrote %08X bytes\n", transferred);
		}

		return result;

	} else if (srb->cmnd[0] == READ_10 ||
		   srb->cmnd[0] == GPCMD_READ_CD) {

		return usbat_hp8200e_handle_read10(us, registers, data, srb);

	}

	if (len > 0xFFFF) {
		US_DEBUGP("Error: len = %08X... what do I do now?\n",
			len);
		return USB_STOR_TRANSPORT_ERROR;
	}

	if ( (result = usbat_multiple_write(us, 
			registers, data, 7)) != USB_STOR_TRANSPORT_GOOD) {
		return result;
	}

	/*
	 * Write the 12-byte command header.
	 *
	 * If the command is BLANK then set the timer for 75 minutes.
	 * Otherwise set it for 10 minutes.
	 *
	 * NOTE: THE 8200 DOCUMENTATION STATES THAT BLANKING A CDRW
	 * AT SPEED 4 IS UNRELIABLE!!!
	 */

	if ((result = usbat_write_block(us,
			USBAT_ATA, srb->cmnd, 12,
				(srb->cmnd[0]==GPCMD_BLANK ? 75 : 10), 0) !=
			     USB_STOR_TRANSPORT_GOOD)) {
		return result;
	}

	/* If there is response data to be read in then do it here. */

	if (len != 0 && (srb->sc_data_direction == DMA_FROM_DEVICE)) {

		/* How many bytes to read in? Check cylL register */

		if (usbat_read(us, USBAT_ATA, USBAT_ATA_LBA_ME, status) != 
		    	USB_STOR_XFER_GOOD) {
			return USB_STOR_TRANSPORT_ERROR;
		}

		if (len > 0xFF) { /* need to read cylH also */
			len = *status;
			if (usbat_read(us, USBAT_ATA, USBAT_ATA_LBA_HI, status) !=
				    USB_STOR_XFER_GOOD) {
				return USB_STOR_TRANSPORT_ERROR;
			}
			len += ((unsigned int) *status)<<8;
		}
		else
			len = *status;


		result = usbat_read_block(us, scsi_sglist(srb), len,
			                                   scsi_sg_count(srb));
	}

	return result;
}