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
struct us_data {unsigned char* iobuf; unsigned int send_bulk_pipe; unsigned int recv_bulk_pipe; scalar_t__ extra; } ;
struct sddr09_card_info {int flags; int capacity; int pageshift; int pagesize; int blockshift; int blocksize; int blockmask; int lbact; } ;
struct scsi_cmnd {int* cmnd; int cmd_len; scalar_t__ sc_data_direction; } ;
struct nand_flash_dev {int chipshift; int pageshift; int blockshift; } ;
typedef  int /*<<< orphan*/  mode_page_01 ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int ALLOW_MEDIUM_REMOVAL ; 
 scalar_t__ DMA_FROM_DEVICE ; 
 scalar_t__ DMA_TO_DEVICE ; 
 int INQUIRY ; 
 int LUNBITS ; 
 int MODE_SENSE_10 ; 
 int READ_10 ; 
 int READ_CAPACITY ; 
 int REQUEST_SENSE ; 
 int SDDR09_WP ; 
 int TEST_UNIT_READY ; 
 int USB_STOR_TRANSPORT_ERROR ; 
 int USB_STOR_TRANSPORT_FAILED ; 
 int USB_STOR_TRANSPORT_GOOD ; 
 int USB_STOR_XFER_GOOD ; 
 int /*<<< orphan*/  US_DEBUGP (char*,...) ; 
 int WRITE_10 ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (unsigned long) ; 
 int /*<<< orphan*/  fill_inquiry_response (struct us_data*,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scsi_bufflen (struct scsi_cmnd*) ; 
 struct nand_flash_dev* sddr09_get_cardinfo (struct us_data*,int) ; 
 int /*<<< orphan*/  sddr09_get_wp (struct us_data*,struct sddr09_card_info*) ; 
 int sddr09_read_data (struct us_data*,unsigned int,unsigned int) ; 
 scalar_t__ sddr09_read_map (struct us_data*) ; 
 int sddr09_send_scsi_command (struct us_data*,int*,int) ; 
 int sddr09_write_data (struct us_data*,unsigned int,unsigned int) ; 
 unsigned int short_pack (int,int) ; 
 int /*<<< orphan*/  sprintf (unsigned char*,char*,int) ; 
 int strlen (unsigned char*) ; 
 int usb_stor_bulk_srb (struct us_data*,unsigned int,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  usb_stor_set_xfer_buf (unsigned char*,int,struct scsi_cmnd*) ; 

__attribute__((used)) static int sddr09_transport(struct scsi_cmnd *srb, struct us_data *us)
{
	static unsigned char sensekey = 0, sensecode = 0;
	static unsigned char havefakesense = 0;
	int result, i;
	unsigned char *ptr = us->iobuf;
	unsigned long capacity;
	unsigned int page, pages;

	struct sddr09_card_info *info;

	static unsigned char inquiry_response[8] = {
		0x00, 0x80, 0x00, 0x02, 0x1F, 0x00, 0x00, 0x00
	};

	/* note: no block descriptor support */
	static unsigned char mode_page_01[19] = {
		0x00, 0x0F, 0x00, 0x0, 0x0, 0x0, 0x00,
		0x01, 0x0A,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};

	info = (struct sddr09_card_info *)us->extra;

	if (srb->cmnd[0] == REQUEST_SENSE && havefakesense) {
		/* for a faked command, we have to follow with a faked sense */
		memset(ptr, 0, 18);
		ptr[0] = 0x70;
		ptr[2] = sensekey;
		ptr[7] = 11;
		ptr[12] = sensecode;
		usb_stor_set_xfer_buf(ptr, 18, srb);
		sensekey = sensecode = havefakesense = 0;
		return USB_STOR_TRANSPORT_GOOD;
	}

	havefakesense = 1;

	/* Dummy up a response for INQUIRY since SDDR09 doesn't
	   respond to INQUIRY commands */

	if (srb->cmnd[0] == INQUIRY) {
		memcpy(ptr, inquiry_response, 8);
		fill_inquiry_response(us, ptr, 36);
		return USB_STOR_TRANSPORT_GOOD;
	}

	if (srb->cmnd[0] == READ_CAPACITY) {
		struct nand_flash_dev *cardinfo;

		sddr09_get_wp(us, info);	/* read WP bit */

		cardinfo = sddr09_get_cardinfo(us, info->flags);
		if (!cardinfo) {
			/* probably no media */
		init_error:
			sensekey = 0x02;	/* not ready */
			sensecode = 0x3a;	/* medium not present */
			return USB_STOR_TRANSPORT_FAILED;
		}

		info->capacity = (1 << cardinfo->chipshift);
		info->pageshift = cardinfo->pageshift;
		info->pagesize = (1 << info->pageshift);
		info->blockshift = cardinfo->blockshift;
		info->blocksize = (1 << info->blockshift);
		info->blockmask = info->blocksize - 1;

		// map initialization, must follow get_cardinfo()
		if (sddr09_read_map(us)) {
			/* probably out of memory */
			goto init_error;
		}

		// Report capacity

		capacity = (info->lbact << info->blockshift) - 1;

		((__be32 *) ptr)[0] = cpu_to_be32(capacity);

		// Report page size

		((__be32 *) ptr)[1] = cpu_to_be32(info->pagesize);
		usb_stor_set_xfer_buf(ptr, 8, srb);

		return USB_STOR_TRANSPORT_GOOD;
	}

	if (srb->cmnd[0] == MODE_SENSE_10) {
		int modepage = (srb->cmnd[2] & 0x3F);

		/* They ask for the Read/Write error recovery page,
		   or for all pages. */
		/* %% We should check DBD %% */
		if (modepage == 0x01 || modepage == 0x3F) {
			US_DEBUGP("SDDR09: Dummy up request for "
				  "mode page 0x%x\n", modepage);

			memcpy(ptr, mode_page_01, sizeof(mode_page_01));
			((__be16*)ptr)[0] = cpu_to_be16(sizeof(mode_page_01) - 2);
			ptr[3] = (info->flags & SDDR09_WP) ? 0x80 : 0;
			usb_stor_set_xfer_buf(ptr, sizeof(mode_page_01), srb);
			return USB_STOR_TRANSPORT_GOOD;
		}

		sensekey = 0x05;	/* illegal request */
		sensecode = 0x24;	/* invalid field in CDB */
		return USB_STOR_TRANSPORT_FAILED;
	}

	if (srb->cmnd[0] == ALLOW_MEDIUM_REMOVAL)
		return USB_STOR_TRANSPORT_GOOD;

	havefakesense = 0;

	if (srb->cmnd[0] == READ_10) {

		page = short_pack(srb->cmnd[3], srb->cmnd[2]);
		page <<= 16;
		page |= short_pack(srb->cmnd[5], srb->cmnd[4]);
		pages = short_pack(srb->cmnd[8], srb->cmnd[7]);

		US_DEBUGP("READ_10: read page %d pagect %d\n",
			  page, pages);

		result = sddr09_read_data(us, page, pages);
		return (result == 0 ? USB_STOR_TRANSPORT_GOOD :
				USB_STOR_TRANSPORT_ERROR);
	}

	if (srb->cmnd[0] == WRITE_10) {

		page = short_pack(srb->cmnd[3], srb->cmnd[2]);
		page <<= 16;
		page |= short_pack(srb->cmnd[5], srb->cmnd[4]);
		pages = short_pack(srb->cmnd[8], srb->cmnd[7]);

		US_DEBUGP("WRITE_10: write page %d pagect %d\n",
			  page, pages);

		result = sddr09_write_data(us, page, pages);
		return (result == 0 ? USB_STOR_TRANSPORT_GOOD :
				USB_STOR_TRANSPORT_ERROR);
	}

	/* catch-all for all other commands, except
	 * pass TEST_UNIT_READY and REQUEST_SENSE through
	 */
	if (srb->cmnd[0] != TEST_UNIT_READY &&
	    srb->cmnd[0] != REQUEST_SENSE) {
		sensekey = 0x05;	/* illegal request */
		sensecode = 0x20;	/* invalid command */
		havefakesense = 1;
		return USB_STOR_TRANSPORT_FAILED;
	}

	for (; srb->cmd_len<12; srb->cmd_len++)
		srb->cmnd[srb->cmd_len] = 0;

	srb->cmnd[1] = LUNBITS;

	ptr[0] = 0;
	for (i=0; i<12; i++)
		sprintf(ptr+strlen(ptr), "%02X ", srb->cmnd[i]);

	US_DEBUGP("SDDR09: Send control for command %s\n", ptr);

	result = sddr09_send_scsi_command(us, srb->cmnd, 12);
	if (result) {
		US_DEBUGP("sddr09_transport: sddr09_send_scsi_command "
			  "returns %d\n", result);
		return USB_STOR_TRANSPORT_ERROR;
	}

	if (scsi_bufflen(srb) == 0)
		return USB_STOR_TRANSPORT_GOOD;

	if (srb->sc_data_direction == DMA_TO_DEVICE ||
	    srb->sc_data_direction == DMA_FROM_DEVICE) {
		unsigned int pipe = (srb->sc_data_direction == DMA_TO_DEVICE)
				? us->send_bulk_pipe : us->recv_bulk_pipe;

		US_DEBUGP("SDDR09: %s %d bytes\n",
			  (srb->sc_data_direction == DMA_TO_DEVICE) ?
			  "sending" : "receiving",
			  scsi_bufflen(srb));

		result = usb_stor_bulk_srb(us, pipe, srb);

		return (result == USB_STOR_XFER_GOOD ?
			USB_STOR_TRANSPORT_GOOD : USB_STOR_TRANSPORT_ERROR);
	} 

	return USB_STOR_TRANSPORT_GOOD;
}