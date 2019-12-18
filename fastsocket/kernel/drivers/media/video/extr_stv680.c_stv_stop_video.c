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
struct usb_stv {unsigned char origMode; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PDEBUG (int,char*,...) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int stv_set_config (struct usb_stv*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stv_sndctrl (int,struct usb_stv*,int,int,unsigned char*,int) ; 

__attribute__((used)) static int stv_stop_video (struct usb_stv *dev)
{
	int i;
	unsigned char *buf;

	buf = kmalloc (40, GFP_KERNEL);
	if (buf == NULL) {
		PDEBUG (0, "STV(e): Out of (small buf) memory");
		return -1;
	}

	/* this is a high priority command; it stops all lower order commands */
	if ((i = stv_sndctrl (1, dev, 0x04, 0x0000, buf, 0x0)) < 0) {
		i = stv_sndctrl (0, dev, 0x80, 0, buf, 0x02);	/* Get Last Error; 2 = busy */
		PDEBUG (1, "STV(i): last error: %i,  command = 0x%x", buf[0], buf[1]);
	} else {
		PDEBUG (1, "STV(i): Camera reset to idle mode.");
	}

	if ((i = stv_set_config (dev, 1, 0, 0)) < 0)
		PDEBUG (1, "STV(e): Reset config during exit failed");

	/*  get current mode  */
	buf[0] = 0xf0;
	if ((i = stv_sndctrl (0, dev, 0x87, 0, buf, 0x08)) != 0x08)	/* get mode */
		PDEBUG (0, "STV(e): Stop_video: problem setting original mode");
	if (dev->origMode != buf[0]) {
		memset (buf, 0, 8);
		buf[0] = (unsigned char) dev->origMode;
		if ((i = stv_sndctrl (3, dev, 0x07, 0x0100, buf, 0x08)) != 0x08) {
			PDEBUG (0, "STV(e): Stop_video: Set_Camera_Mode failed");
			i = -1;
		}
		buf[0] = 0xf0;
		i = stv_sndctrl (0, dev, 0x87, 0, buf, 0x08);
		if ((i != 0x08) || (buf[0] != dev->origMode)) {
			PDEBUG (0, "STV(e): camera NOT set to original resolution.");
			i = -1;
		} else
			PDEBUG (0, "STV(i): Camera set to original resolution");
	}
	/* origMode */
	kfree(buf);
	return i;
}