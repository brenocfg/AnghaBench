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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct ucbus_write_cmd {int bw_addr; int bw_data; } ;
struct gspca_dev {int usb_err; int /*<<< orphan*/ * usb_buf; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_USBO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int SQ930_CTRL_UCBUS_IO ; 
 int USB_BUF_SZ ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  err (char*,...) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ucbus_write(struct gspca_dev *gspca_dev,
			const struct ucbus_write_cmd *cmd,
			int ncmds,
			int batchsize)
{
	u8 *buf;
	u16 val, idx;
	int len, ret;

	if (gspca_dev->usb_err < 0)
		return;

#ifdef GSPCA_DEBUG
	if ((batchsize - 1) * 3 > USB_BUF_SZ) {
		err("Bug: usb_buf overflow");
		gspca_dev->usb_err = -ENOMEM;
		return;
	}
#endif

	for (;;) {
		len = ncmds;
		if (len > batchsize)
			len = batchsize;
		ncmds -= len;

		val = (cmd->bw_addr << 8) | SQ930_CTRL_UCBUS_IO;
		idx = (cmd->bw_data << 8) | (cmd->bw_addr >> 8);

		buf = gspca_dev->usb_buf;
		while (--len > 0) {
			cmd++;
			*buf++ = cmd->bw_addr;
			*buf++ = cmd->bw_addr >> 8;
			*buf++ = cmd->bw_data;
		}
		if (buf != gspca_dev->usb_buf)
			PDEBUG(D_USBO, "ucbus v: %04x i: %04x %02x...%02x",
					val, idx,
					gspca_dev->usb_buf[0], buf[-1]);
		else
			PDEBUG(D_USBO, "ucbus v: %04x i: %04x",
					val, idx);
		ret = usb_control_msg(gspca_dev->dev,
				usb_sndctrlpipe(gspca_dev->dev, 0),
				0x0c,			/* request */
			   USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				val, idx,
				gspca_dev->usb_buf, buf - gspca_dev->usb_buf,
				500);
		if (ret < 0) {
			err("ucbus_write failed %d", ret);
			gspca_dev->usb_err = ret;
			return;
		}
		msleep(30);
		if (ncmds <= 0)
			break;
		cmd++;
	}
}