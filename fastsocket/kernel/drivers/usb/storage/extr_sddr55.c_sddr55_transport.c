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
struct us_data {unsigned char* iobuf; scalar_t__ extra; int /*<<< orphan*/  extra_destructor; } ;
struct sddr55_card_info {unsigned char* sense_data; unsigned int* lba_to_pba; unsigned long capacity; int max_log_blks; int pageshift; int blockshift; unsigned int smallpageshift; unsigned int blockmask; scalar_t__ force_read_only; scalar_t__ read_only; scalar_t__ fatal_error; scalar_t__ last_access; } ;
struct scsi_cmnd {int* cmnd; } ;
typedef  int /*<<< orphan*/  mode_page_01 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ALLOW_MEDIUM_REMOVAL ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int HZ ; 
 int INQUIRY ; 
 int MODE_SENSE_10 ; 
 unsigned long PAGESIZE ; 
 int READ_10 ; 
 int READ_CAPACITY ; 
 int REQUEST_SENSE ; 
 int START_STOP ; 
 int TEST_UNIT_READY ; 
 int USB_STOR_TRANSPORT_ERROR ; 
 int USB_STOR_TRANSPORT_FAILED ; 
 int USB_STOR_TRANSPORT_GOOD ; 
 int /*<<< orphan*/  US_DEBUGP (char*,...) ; 
 int WRITE_10 ; 
 int /*<<< orphan*/  cpu_to_be32 (unsigned long) ; 
 int /*<<< orphan*/  fill_inquiry_response (struct us_data*,unsigned char*,int) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sddr55_card_info_destructor ; 
 unsigned long sddr55_get_capacity (struct us_data*) ; 
 int sddr55_read_data (struct us_data*,unsigned int,unsigned int,unsigned short) ; 
 int /*<<< orphan*/  sddr55_read_map (struct us_data*) ; 
 int sddr55_status (struct us_data*) ; 
 int sddr55_write_data (struct us_data*,unsigned int,unsigned int,unsigned short) ; 
 int /*<<< orphan*/  set_sense_info (int,int,int /*<<< orphan*/ ) ; 
 unsigned int short_pack (int,int) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  usb_stor_set_xfer_buf (unsigned char*,int,struct scsi_cmnd*) ; 

__attribute__((used)) static int sddr55_transport(struct scsi_cmnd *srb, struct us_data *us)
{
	int result;
	static unsigned char inquiry_response[8] = {
		0x00, 0x80, 0x00, 0x02, 0x1F, 0x00, 0x00, 0x00
	};
 	// write-protected for now, no block descriptor support
	static unsigned char mode_page_01[20] = {
		0x0, 0x12, 0x00, 0x80, 0x0, 0x0, 0x0, 0x0,
		0x01, 0x0A,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};
	unsigned char *ptr = us->iobuf;
	unsigned long capacity;
	unsigned int lba;
	unsigned int pba;
	unsigned int page;
	unsigned short pages;
	struct sddr55_card_info *info;

	if (!us->extra) {
		us->extra = kzalloc(
			sizeof(struct sddr55_card_info), GFP_NOIO);
		if (!us->extra)
			return USB_STOR_TRANSPORT_ERROR;
		us->extra_destructor = sddr55_card_info_destructor;
	}

	info = (struct sddr55_card_info *)(us->extra);

	if (srb->cmnd[0] == REQUEST_SENSE) {
		US_DEBUGP("SDDR55: request sense %02x/%02x/%02x\n", info->sense_data[2], info->sense_data[12], info->sense_data[13]);

		memcpy (ptr, info->sense_data, sizeof info->sense_data);
		ptr[0] = 0x70;
		ptr[7] = 11;
		usb_stor_set_xfer_buf (ptr, sizeof info->sense_data, srb);
		memset (info->sense_data, 0, sizeof info->sense_data);

		return USB_STOR_TRANSPORT_GOOD;
	}

	memset (info->sense_data, 0, sizeof info->sense_data);

	/* Dummy up a response for INQUIRY since SDDR55 doesn't
	   respond to INQUIRY commands */

	if (srb->cmnd[0] == INQUIRY) {
		memcpy(ptr, inquiry_response, 8);
		fill_inquiry_response(us, ptr, 36);
		return USB_STOR_TRANSPORT_GOOD;
	}

	/* only check card status if the map isn't allocated, ie no card seen yet
	 * or if it's been over half a second since we last accessed it
	 */
	if (info->lba_to_pba == NULL || time_after(jiffies, info->last_access + HZ/2)) {

		/* check to see if a card is fitted */
		result = sddr55_status (us);
		if (result) {
			result = sddr55_status (us);
			if (!result) {
			set_sense_info (6, 0x28, 0);	/* new media, set unit attention, not ready to ready */
			}
			return USB_STOR_TRANSPORT_FAILED;
		}
	}

	/* if we detected a problem with the map when writing,
	   don't allow any more access */
	if (info->fatal_error) {

		set_sense_info (3, 0x31, 0);
		return USB_STOR_TRANSPORT_FAILED;
	}

	if (srb->cmnd[0] == READ_CAPACITY) {

		capacity = sddr55_get_capacity(us);

		if (!capacity) {
			set_sense_info (3, 0x30, 0); /* incompatible medium */
			return USB_STOR_TRANSPORT_FAILED;
		}

		info->capacity = capacity;

		/* figure out the maximum logical block number, allowing for
		 * the fact that only 250 out of every 256 are used */
		info->max_log_blks = ((info->capacity >> (info->pageshift + info->blockshift)) / 256) * 250;

		/* Last page in the card, adjust as we only use 250 out of
		 * every 256 pages */
		capacity = (capacity / 256) * 250;

		capacity /= PAGESIZE;
		capacity--;

		((__be32 *) ptr)[0] = cpu_to_be32(capacity);
		((__be32 *) ptr)[1] = cpu_to_be32(PAGESIZE);
		usb_stor_set_xfer_buf(ptr, 8, srb);

		sddr55_read_map(us);

		return USB_STOR_TRANSPORT_GOOD;
	}

	if (srb->cmnd[0] == MODE_SENSE_10) {

		memcpy(ptr, mode_page_01, sizeof mode_page_01);
		ptr[3] = (info->read_only || info->force_read_only) ? 0x80 : 0;
		usb_stor_set_xfer_buf(ptr, sizeof(mode_page_01), srb);

		if ( (srb->cmnd[2] & 0x3F) == 0x01 ) {
			US_DEBUGP(
			  "SDDR55: Dummy up request for mode page 1\n");
			return USB_STOR_TRANSPORT_GOOD;

		} else if ( (srb->cmnd[2] & 0x3F) == 0x3F ) {
			US_DEBUGP(
			  "SDDR55: Dummy up request for all mode pages\n");
			return USB_STOR_TRANSPORT_GOOD;
		}

		set_sense_info (5, 0x24, 0);	/* invalid field in command */
		return USB_STOR_TRANSPORT_FAILED;
	}

	if (srb->cmnd[0] == ALLOW_MEDIUM_REMOVAL) {

		US_DEBUGP(
		  "SDDR55: %s medium removal. Not that I can do"
		  " anything about it...\n",
		  (srb->cmnd[4]&0x03) ? "Prevent" : "Allow");

		return USB_STOR_TRANSPORT_GOOD;

	}

	if (srb->cmnd[0] == READ_10 || srb->cmnd[0] == WRITE_10) {

		page = short_pack(srb->cmnd[3], srb->cmnd[2]);
		page <<= 16;
		page |= short_pack(srb->cmnd[5], srb->cmnd[4]);
		pages = short_pack(srb->cmnd[8], srb->cmnd[7]);

		page <<= info->smallpageshift;

		// convert page to block and page-within-block

		lba = page >> info->blockshift;
		page = page & info->blockmask;

		// locate physical block corresponding to logical block

		if (lba >= info->max_log_blks) {

			US_DEBUGP("Error: Requested LBA %04X exceeds maximum "
			  "block %04X\n", lba, info->max_log_blks-1);

			set_sense_info (5, 0x24, 0);	/* invalid field in command */

			return USB_STOR_TRANSPORT_FAILED;
		}

		pba = info->lba_to_pba[lba];

		if (srb->cmnd[0] == WRITE_10) {
			US_DEBUGP("WRITE_10: write block %04X (LBA %04X) page %01X"
				" pages %d\n",
				pba, lba, page, pages);

			return sddr55_write_data(us, lba, page, pages);
		} else {
			US_DEBUGP("READ_10: read block %04X (LBA %04X) page %01X"
				" pages %d\n",
				pba, lba, page, pages);

			return sddr55_read_data(us, lba, page, pages);
		}
	}


	if (srb->cmnd[0] == TEST_UNIT_READY) {
		return USB_STOR_TRANSPORT_GOOD;
	}

	if (srb->cmnd[0] == START_STOP) {
		return USB_STOR_TRANSPORT_GOOD;
	}

	set_sense_info (5, 0x20, 0);	/* illegal command */

	return USB_STOR_TRANSPORT_FAILED; // FIXME: sense buffer?
}