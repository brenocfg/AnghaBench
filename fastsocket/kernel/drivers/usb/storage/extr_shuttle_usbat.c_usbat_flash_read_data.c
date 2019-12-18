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
typedef  int u32 ;
struct usbat_info {int ssize; } ;
struct us_data {int /*<<< orphan*/  srb; } ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  TO_XFER_BUF ; 
 unsigned char USBAT_ATA_DEVICE ; 
 unsigned char USBAT_ATA_FEATURES ; 
 unsigned char USBAT_ATA_LBA_HI ; 
 unsigned char USBAT_ATA_LBA_ME ; 
 unsigned char USBAT_ATA_SECCNT ; 
 unsigned char USBAT_ATA_SECNUM ; 
 unsigned char USBAT_ATA_STATUS ; 
 int USB_STOR_TRANSPORT_ERROR ; 
 int USB_STOR_TRANSPORT_GOOD ; 
 int /*<<< orphan*/  US_DEBUGP (char*,int) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 void* min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  usb_stor_access_xfer_buf (unsigned char*,int,int /*<<< orphan*/ ,struct scatterlist**,unsigned int*,int /*<<< orphan*/ ) ; 
 int usbat_flash_check_media (struct us_data*,struct usbat_info*) ; 
 int usbat_multiple_write (struct us_data*,unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  usbat_pack_ata_sector_cmd (unsigned char*,unsigned char,int,int) ; 
 int usbat_read_blocks (struct us_data*,unsigned char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbat_flash_read_data(struct us_data *us,
								 struct usbat_info *info,
								 u32 sector,
								 u32 sectors)
{
	unsigned char registers[7] = {
		USBAT_ATA_FEATURES,
		USBAT_ATA_SECCNT,
		USBAT_ATA_SECNUM,
		USBAT_ATA_LBA_ME,
		USBAT_ATA_LBA_HI,
		USBAT_ATA_DEVICE,
		USBAT_ATA_STATUS,
	};
	unsigned char command[7];
	unsigned char *buffer;
	unsigned char  thistime;
	unsigned int totallen, alloclen;
	int len, result;
	unsigned int sg_offset = 0;
	struct scatterlist *sg = NULL;

	result = usbat_flash_check_media(us, info);
	if (result != USB_STOR_TRANSPORT_GOOD)
		return result;

	/*
	 * we're working in LBA mode.  according to the ATA spec,
	 * we can support up to 28-bit addressing.  I don't know if Jumpshot
	 * supports beyond 24-bit addressing.  It's kind of hard to test
	 * since it requires > 8GB CF card.
	 */

	if (sector > 0x0FFFFFFF)
		return USB_STOR_TRANSPORT_ERROR;

	totallen = sectors * info->ssize;

	/*
	 * Since we don't read more than 64 KB at a time, we have to create
	 * a bounce buffer and move the data a piece at a time between the
	 * bounce buffer and the actual transfer buffer.
	 */

	alloclen = min(totallen, 65536u);
	buffer = kmalloc(alloclen, GFP_NOIO);
	if (buffer == NULL)
		return USB_STOR_TRANSPORT_ERROR;

	do {
		/*
		 * loop, never allocate or transfer more than 64k at once
		 * (min(128k, 255*info->ssize) is the real limit)
		 */
		len = min(totallen, alloclen);
		thistime = (len / info->ssize) & 0xff;
 
		/* ATA command 0x20 (READ SECTORS) */
		usbat_pack_ata_sector_cmd(command, thistime, sector, 0x20);

		/* Write/execute ATA read command */
		result = usbat_multiple_write(us, registers, command, 7);
		if (result != USB_STOR_TRANSPORT_GOOD)
			goto leave;

		/* Read the data we just requested */
		result = usbat_read_blocks(us, buffer, len, 0);
		if (result != USB_STOR_TRANSPORT_GOOD)
			goto leave;
  	 
		US_DEBUGP("usbat_flash_read_data:  %d bytes\n", len);
	
		/* Store the data in the transfer buffer */
		usb_stor_access_xfer_buf(buffer, len, us->srb,
					 &sg, &sg_offset, TO_XFER_BUF);

		sector += thistime;
		totallen -= len;
	} while (totallen > 0);

	kfree(buffer);
	return USB_STOR_TRANSPORT_GOOD;

leave:
	kfree(buffer);
	return USB_STOR_TRANSPORT_ERROR;
}