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
typedef  int /*<<< orphan*/  u16 ;
struct us_data {int /*<<< orphan*/  recv_bulk_pipe; int /*<<< orphan*/  send_bulk_pipe; } ;

/* Variables and functions */
 int ALAUDA_BULK_CMD ; 
 int ALAUDA_BULK_ERASE_BLOCK ; 
 int MEDIA_PORT (struct us_data*) ; 
 int PBA_HI (int /*<<< orphan*/ ) ; 
 int PBA_LO (int /*<<< orphan*/ ) ; 
 int PBA_ZONE (int /*<<< orphan*/ ) ; 
 int USB_STOR_XFER_GOOD ; 
 int /*<<< orphan*/  US_DEBUGP (char*,unsigned char,...) ; 
 int usb_stor_bulk_transfer_buf (struct us_data*,int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int alauda_erase_block(struct us_data *us, u16 pba)
{
	int rc;
	unsigned char command[] = {
		ALAUDA_BULK_CMD, ALAUDA_BULK_ERASE_BLOCK, PBA_HI(pba),
		PBA_ZONE(pba), 0, PBA_LO(pba), 0x02, 0, MEDIA_PORT(us)
	};
	unsigned char buf[2];

	US_DEBUGP("alauda_erase_block: Erasing PBA %d\n", pba);

	rc = usb_stor_bulk_transfer_buf(us, us->send_bulk_pipe,
		command, 9, NULL);
	if (rc != USB_STOR_XFER_GOOD)
		return rc;

	rc = usb_stor_bulk_transfer_buf(us, us->recv_bulk_pipe,
		buf, 2, NULL);
	if (rc != USB_STOR_XFER_GOOD)
		return rc;

	US_DEBUGP("alauda_erase_block: Erase result: %02X %02X\n",
		buf[0], buf[1]);
	return rc;
}