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
typedef  int u8 ;
struct gspca_dev {int /*<<< orphan*/  usb_buf; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DATA_IN ; 
 int DATA_OUT ; 
 int /*<<< orphan*/  D_ERR ; 
 int EINVAL ; 
 int EPIPE ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int) ; 
 int USB_DIR_IN ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  err (char*,int,int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,unsigned int,int,int,int,int,int /*<<< orphan*/ ,int,int) ; 
 unsigned int usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpia_usb_transferCmd(struct gspca_dev *gspca_dev, u8 *command)
{
	u8 requesttype;
	unsigned int pipe;
	int ret, databytes = command[6] | (command[7] << 8);
	/* Sometimes we see spurious EPIPE errors */
	int retries = 3;

	if (command[0] == DATA_IN) {
		pipe = usb_rcvctrlpipe(gspca_dev->dev, 0);
		requesttype = USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE;
	} else if (command[0] == DATA_OUT) {
		pipe = usb_sndctrlpipe(gspca_dev->dev, 0);
		requesttype = USB_TYPE_VENDOR | USB_RECIP_DEVICE;
	} else {
		PDEBUG(D_ERR, "Unexpected first byte of command: %x",
		       command[0]);
		return -EINVAL;
	}

retry:
	ret = usb_control_msg(gspca_dev->dev, pipe,
			      command[1],
			      requesttype,
			      command[2] | (command[3] << 8),
			      command[4] | (command[5] << 8),
			      gspca_dev->usb_buf, databytes, 1000);

	if (ret < 0)
		err("usb_control_msg %02x, error %d", command[1],
		       ret);

	if (ret == -EPIPE && retries > 0) {
		retries--;
		goto retry;
	}

	return (ret < 0) ? ret : 0;
}