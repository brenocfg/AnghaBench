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
struct us_data {int dummy; } ;
struct scsi_cmnd {unsigned int transfersize; } ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 unsigned char GPCMD_READ_CD ; 
 unsigned char LSB_of (unsigned int) ; 
 unsigned char MSB_of (unsigned int) ; 
 int /*<<< orphan*/  TO_XFER_BUF ; 
 int /*<<< orphan*/  USBAT_ATA ; 
 int /*<<< orphan*/  USBAT_ATA_DATA ; 
 int /*<<< orphan*/  USBAT_ATA_STATUS ; 
 int USBAT_QUAL_ALQ ; 
 int USBAT_QUAL_FCQ ; 
 int USB_STOR_TRANSPORT_FAILED ; 
 int USB_STOR_TRANSPORT_GOOD ; 
 int /*<<< orphan*/  US_DEBUGP (char*,unsigned int) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 unsigned int scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sg_count (struct scsi_cmnd*) ; 
 unsigned char* scsi_sglist (struct scsi_cmnd*) ; 
 unsigned int short_pack (unsigned char,unsigned char) ; 
 unsigned int transferred ; 
 int /*<<< orphan*/  usb_stor_access_xfer_buf (unsigned char*,unsigned int,struct scsi_cmnd*,struct scatterlist**,unsigned int*,int /*<<< orphan*/ ) ; 
 int usbat_hp8200e_rw_block_test (struct us_data*,int /*<<< orphan*/ ,unsigned char*,unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,unsigned char*,unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int usbat_hp8200e_handle_read10(struct us_data *us,
				       unsigned char *registers,
				       unsigned char *data,
				       struct scsi_cmnd *srb)
{
	int result = USB_STOR_TRANSPORT_GOOD;
	unsigned char *buffer;
	unsigned int len;
	unsigned int sector;
	unsigned int sg_offset = 0;
	struct scatterlist *sg = NULL;

	US_DEBUGP("handle_read10: transfersize %d\n",
		srb->transfersize);

	if (scsi_bufflen(srb) < 0x10000) {

		result = usbat_hp8200e_rw_block_test(us, USBAT_ATA, 
			registers, data, 19,
			USBAT_ATA_DATA, USBAT_ATA_STATUS, 0xFD,
			(USBAT_QUAL_FCQ | USBAT_QUAL_ALQ),
			DMA_FROM_DEVICE,
			scsi_sglist(srb),
			scsi_bufflen(srb), scsi_sg_count(srb), 1);

		return result;
	}

	/*
	 * Since we're requesting more data than we can handle in
	 * a single read command (max is 64k-1), we will perform
	 * multiple reads, but each read must be in multiples of
	 * a sector.  Luckily the sector size is in srb->transfersize
	 * (see linux/drivers/scsi/sr.c).
	 */

	if (data[7+0] == GPCMD_READ_CD) {
		len = short_pack(data[7+9], data[7+8]);
		len <<= 16;
		len |= data[7+7];
		US_DEBUGP("handle_read10: GPCMD_READ_CD: len %d\n", len);
		srb->transfersize = scsi_bufflen(srb)/len;
	}

	if (!srb->transfersize)  {
		srb->transfersize = 2048; /* A guess */
		US_DEBUGP("handle_read10: transfersize 0, forcing %d\n",
			srb->transfersize);
	}

	/*
	 * Since we only read in one block at a time, we have to create
	 * a bounce buffer and move the data a piece at a time between the
	 * bounce buffer and the actual transfer buffer.
	 */

	len = (65535/srb->transfersize) * srb->transfersize;
	US_DEBUGP("Max read is %d bytes\n", len);
	len = min(len, scsi_bufflen(srb));
	buffer = kmalloc(len, GFP_NOIO);
	if (buffer == NULL) /* bloody hell! */
		return USB_STOR_TRANSPORT_FAILED;
	sector = short_pack(data[7+3], data[7+2]);
	sector <<= 16;
	sector |= short_pack(data[7+5], data[7+4]);
	transferred = 0;

	while (transferred != scsi_bufflen(srb)) {

		if (len > scsi_bufflen(srb) - transferred)
			len = scsi_bufflen(srb) - transferred;

		data[3] = len&0xFF; 	  /* (cylL) = expected length (L) */
		data[4] = (len>>8)&0xFF;  /* (cylH) = expected length (H) */

		/* Fix up the SCSI command sector and num sectors */

		data[7+2] = MSB_of(sector>>16); /* SCSI command sector */
		data[7+3] = LSB_of(sector>>16);
		data[7+4] = MSB_of(sector&0xFFFF);
		data[7+5] = LSB_of(sector&0xFFFF);
		if (data[7+0] == GPCMD_READ_CD)
			data[7+6] = 0;
		data[7+7] = MSB_of(len / srb->transfersize); /* SCSI command */
		data[7+8] = LSB_of(len / srb->transfersize); /* num sectors */

		result = usbat_hp8200e_rw_block_test(us, USBAT_ATA, 
			registers, data, 19,
			USBAT_ATA_DATA, USBAT_ATA_STATUS, 0xFD, 
			(USBAT_QUAL_FCQ | USBAT_QUAL_ALQ),
			DMA_FROM_DEVICE,
			buffer,
			len, 0, 1);

		if (result != USB_STOR_TRANSPORT_GOOD)
			break;

		/* Store the data in the transfer buffer */
		usb_stor_access_xfer_buf(buffer, len, srb,
				 &sg, &sg_offset, TO_XFER_BUF);

		/* Update the amount transferred and the sector number */

		transferred += len;
		sector += len / srb->transfersize;

	} /* while transferred != scsi_bufflen(srb) */

	kfree(buffer);
	return result;
}