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
struct usb_stv {int VideoMode; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PDEBUG (int,char*) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int stv_set_config (struct usb_stv*,int,int /*<<< orphan*/ ,int) ; 
 int stv_sndctrl (int,struct usb_stv*,int,int,unsigned char*,int) ; 
 int /*<<< orphan*/  stv_stop_video (struct usb_stv*) ; 

__attribute__((used)) static int stv_set_video_mode (struct usb_stv *dev)
{
	int i, stop_video = 1;
	unsigned char *buf;

	buf = kmalloc (40, GFP_KERNEL);
	if (buf == NULL) {
		PDEBUG (0, "STV(e): Out of (small buf) memory");
		return -1;
	}

	if ((i = stv_set_config (dev, 1, 0, 0)) < 0) {
		kfree(buf);
		return i;
	}

	i = stv_sndctrl (2, dev, 0x06, 0x0100, buf, 0x12);
	if (!(i > 0) && (buf[8] == 0x53) && (buf[9] == 0x05)) {
		PDEBUG (1, "STV(e): Could not get descriptor 0100.");
		goto error;
	}

	/*  set alternate interface 1 */
	if ((i = stv_set_config (dev, 1, 0, 1)) < 0)
		goto error;

	if ((i = stv_sndctrl (0, dev, 0x85, 0, buf, 0x10)) != 0x10)
		goto error;
	PDEBUG (1, "STV(i): Setting video mode.");
	/*  Switch to Video mode: 0x0100 = VGA (640x480), 0x0000 = CIF (352x288) 0x0300 = QVGA (320x240)  */
	if ((i = stv_sndctrl (1, dev, 0x09, dev->VideoMode, buf, 0x0)) < 0) {
		stop_video = 0;
		goto error;
	}
	goto exit;

error:
	kfree(buf);
	if (stop_video == 1)
		stv_stop_video (dev);
	return -1;

exit:
	kfree(buf);
	return 0;
}