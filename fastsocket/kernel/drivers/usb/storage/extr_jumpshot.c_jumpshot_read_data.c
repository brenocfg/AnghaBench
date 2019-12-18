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
struct us_data {unsigned char* iobuf; int /*<<< orphan*/  srb; int /*<<< orphan*/  send_ctrl_pipe; } ;
struct scatterlist {int dummy; } ;
struct jumpshot_info {int ssize; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  TO_XFER_BUF ; 
 int USB_STOR_TRANSPORT_ERROR ; 
 int USB_STOR_TRANSPORT_GOOD ; 
 int USB_STOR_XFER_GOOD ; 
 int /*<<< orphan*/  US_DEBUGP (char*,int) ; 
 int jumpshot_bulk_read (struct us_data*,unsigned char*,int) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 void* min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  usb_stor_access_xfer_buf (unsigned char*,int,int /*<<< orphan*/ ,struct scatterlist**,unsigned int*,int /*<<< orphan*/ ) ; 
 int usb_stor_ctrl_transfer (struct us_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,unsigned char*,int) ; 

__attribute__((used)) static int jumpshot_read_data(struct us_data *us,
			      struct jumpshot_info *info,
			      u32 sector,
			      u32 sectors)
{
	unsigned char *command = us->iobuf;
	unsigned char *buffer;
	unsigned char  thistime;
	unsigned int totallen, alloclen;
	int len, result;
	unsigned int sg_offset = 0;
	struct scatterlist *sg = NULL;

	// we're working in LBA mode.  according to the ATA spec, 
	// we can support up to 28-bit addressing.  I don't know if Jumpshot
	// supports beyond 24-bit addressing.  It's kind of hard to test 
	// since it requires > 8GB CF card.

	if (sector > 0x0FFFFFFF)
		return USB_STOR_TRANSPORT_ERROR;

	totallen = sectors * info->ssize;

	// Since we don't read more than 64 KB at a time, we have to create
	// a bounce buffer and move the data a piece at a time between the
	// bounce buffer and the actual transfer buffer.

	alloclen = min(totallen, 65536u);
	buffer = kmalloc(alloclen, GFP_NOIO);
	if (buffer == NULL)
		return USB_STOR_TRANSPORT_ERROR;

	do {
		// loop, never allocate or transfer more than 64k at once
		// (min(128k, 255*info->ssize) is the real limit)
		len = min(totallen, alloclen);
		thistime = (len / info->ssize) & 0xff;

		command[0] = 0;
		command[1] = thistime;
		command[2] = sector & 0xFF;
		command[3] = (sector >>  8) & 0xFF;
		command[4] = (sector >> 16) & 0xFF;

		command[5] = 0xE0 | ((sector >> 24) & 0x0F);
		command[6] = 0x20;

		// send the setup + command
		result = usb_stor_ctrl_transfer(us, us->send_ctrl_pipe,
					       0, 0x20, 0, 1, command, 7);
		if (result != USB_STOR_XFER_GOOD)
			goto leave;

		// read the result
		result = jumpshot_bulk_read(us, buffer, len);
		if (result != USB_STOR_XFER_GOOD)
			goto leave;

		US_DEBUGP("jumpshot_read_data:  %d bytes\n", len);

		// Store the data in the transfer buffer
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