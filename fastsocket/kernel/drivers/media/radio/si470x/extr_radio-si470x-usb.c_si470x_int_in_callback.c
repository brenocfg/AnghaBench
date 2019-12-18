#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct urb {int status; scalar_t__ actual_length; struct si470x_device* context; } ;
struct si470x_device {int* registers; size_t wr_index; int buf_size; int rd_index; scalar_t__ int_in_running; TYPE_1__* intf; int /*<<< orphan*/  int_in_urb; scalar_t__ usbdev; int /*<<< orphan*/  read_queue; int /*<<< orphan*/ * buffer; int /*<<< orphan*/ * int_in_buffer; scalar_t__ disconnected; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ECONNRESET ; 
 int ENOENT ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 unsigned char RADIO_REGISTER_SIZE ; 
 size_t RDSA ; 
 size_t RDSB ; 
 size_t RDSC ; 
 size_t RDSD ; 
 unsigned char RDS_REGISTER_NUM ; 
 unsigned char RDS_REPORT ; 
 int RDS_REPORT_SIZE ; 
 size_t READCHAN ; 
 int READCHAN_BLERB ; 
 int READCHAN_BLERC ; 
 int READCHAN_BLERD ; 
 unsigned char STATUSRSSI ; 
 int STATUSRSSI_BLERA ; 
 int STATUSRSSI_RDSR ; 
 int STATUSRSSI_RDSS ; 
 size_t SYSCONFIG1 ; 
 int SYSCONFIG1_RDS ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int get_unaligned_be16 (int /*<<< orphan*/ *) ; 
 unsigned short max_rds_errors ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char**,int) ; 
 int /*<<< orphan*/  put_unaligned_le16 (unsigned short,unsigned char**) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void si470x_int_in_callback(struct urb *urb)
{
	struct si470x_device *radio = urb->context;
	unsigned char buf[RDS_REPORT_SIZE];
	int retval;
	unsigned char regnr;
	unsigned char blocknum;
	unsigned short bler; /* rds block errors */
	unsigned short rds;
	unsigned char tmpbuf[3];

	if (urb->status) {
		if (urb->status == -ENOENT ||
				urb->status == -ECONNRESET ||
				urb->status == -ESHUTDOWN) {
			return;
		} else {
			dev_warn(&radio->intf->dev,
			 "non-zero urb status (%d)\n", urb->status);
			goto resubmit; /* Maybe we can recover. */
		}
	}

	/* safety checks */
	if (radio->disconnected)
		return;
	if ((radio->registers[SYSCONFIG1] & SYSCONFIG1_RDS) == 0)
		goto resubmit;

	if (urb->actual_length > 0) {
		/* Update RDS registers with URB data */
		buf[0] = RDS_REPORT;
		for (regnr = 0; regnr < RDS_REGISTER_NUM; regnr++)
			radio->registers[STATUSRSSI + regnr] =
			    get_unaligned_be16(&radio->int_in_buffer[
				regnr * RADIO_REGISTER_SIZE + 1]);
		/* get rds blocks */
		if ((radio->registers[STATUSRSSI] & STATUSRSSI_RDSR) == 0) {
			/* No RDS group ready, better luck next time */
			goto resubmit;
		}
		if ((radio->registers[STATUSRSSI] & STATUSRSSI_RDSS) == 0) {
			/* RDS decoder not synchronized */
			goto resubmit;
		}
		for (blocknum = 0; blocknum < 4; blocknum++) {
			switch (blocknum) {
			default:
				bler = (radio->registers[STATUSRSSI] &
						STATUSRSSI_BLERA) >> 9;
				rds = radio->registers[RDSA];
				break;
			case 1:
				bler = (radio->registers[READCHAN] &
						READCHAN_BLERB) >> 14;
				rds = radio->registers[RDSB];
				break;
			case 2:
				bler = (radio->registers[READCHAN] &
						READCHAN_BLERC) >> 12;
				rds = radio->registers[RDSC];
				break;
			case 3:
				bler = (radio->registers[READCHAN] &
						READCHAN_BLERD) >> 10;
				rds = radio->registers[RDSD];
				break;
			};

			/* Fill the V4L2 RDS buffer */
			put_unaligned_le16(rds, &tmpbuf);
			tmpbuf[2] = blocknum;		/* offset name */
			tmpbuf[2] |= blocknum << 3;	/* received offset */
			if (bler > max_rds_errors)
				tmpbuf[2] |= 0x80; /* uncorrectable errors */
			else if (bler > 0)
				tmpbuf[2] |= 0x40; /* corrected error(s) */

			/* copy RDS block to internal buffer */
			memcpy(&radio->buffer[radio->wr_index], &tmpbuf, 3);
			radio->wr_index += 3;

			/* wrap write pointer */
			if (radio->wr_index >= radio->buf_size)
				radio->wr_index = 0;

			/* check for overflow */
			if (radio->wr_index == radio->rd_index) {
				/* increment and wrap read pointer */
				radio->rd_index += 3;
				if (radio->rd_index >= radio->buf_size)
					radio->rd_index = 0;
			}
		}
		if (radio->wr_index != radio->rd_index)
			wake_up_interruptible(&radio->read_queue);
	}

resubmit:
	/* Resubmit if we're still running. */
	if (radio->int_in_running && radio->usbdev) {
		retval = usb_submit_urb(radio->int_in_urb, GFP_ATOMIC);
		if (retval) {
			dev_warn(&radio->intf->dev,
			       "resubmitting urb failed (%d)", retval);
			radio->int_in_running = 0;
		}
	}
}