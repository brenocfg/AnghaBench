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
struct us_data {unsigned int recv_bulk_pipe; unsigned int send_bulk_pipe; scalar_t__ extra; } ;
struct sddr55_card_info {int /*<<< orphan*/  last_access; } ;

/* Variables and functions */
 int DMA_FROM_DEVICE ; 
 int USB_STOR_XFER_GOOD ; 
 int /*<<< orphan*/  jiffies ; 
 int usb_stor_bulk_transfer_buf (struct us_data*,unsigned int,unsigned char*,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sddr55_bulk_transport(struct us_data *us, int direction,
		      unsigned char *data, unsigned int len) {
	struct sddr55_card_info *info = (struct sddr55_card_info *)us->extra;
	unsigned int pipe = (direction == DMA_FROM_DEVICE) ?
			us->recv_bulk_pipe : us->send_bulk_pipe;

	if (!len)
		return USB_STOR_XFER_GOOD;
	info->last_access = jiffies;
	return usb_stor_bulk_transfer_buf(us, pipe, data, len, NULL);
}