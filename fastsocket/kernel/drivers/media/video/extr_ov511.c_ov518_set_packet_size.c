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
struct usb_ov511 {scalar_t__ bclass; int packet_size; int /*<<< orphan*/  iface; int /*<<< orphan*/  dev; scalar_t__ packet_numbering; } ;

/* Variables and functions */
 scalar_t__ BCL_OV518 ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  OV511_RESET_NOREGS ; 
 int OV518_ALT_SIZE_0 ; 
 int OV518_ALT_SIZE_128 ; 
 int OV518_ALT_SIZE_256 ; 
 int OV518_ALT_SIZE_384 ; 
 int OV518_ALT_SIZE_512 ; 
 int OV518_ALT_SIZE_640 ; 
 int OV518_ALT_SIZE_768 ; 
 int OV518_ALT_SIZE_896 ; 
 int /*<<< orphan*/  PDEBUG (int,char*,int,int) ; 
 int /*<<< orphan*/  err (char*,...) ; 
 int /*<<< orphan*/  ov518_reg_w32 (struct usb_ov511*,int,int,int) ; 
 scalar_t__ ov51x_reset (struct usb_ov511*,int /*<<< orphan*/ ) ; 
 scalar_t__ ov51x_restart (struct usb_ov511*) ; 
 scalar_t__ ov51x_stop (struct usb_ov511*) ; 
 scalar_t__ reg_w (struct usb_ov511*,int,int) ; 
 scalar_t__ usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ov518_set_packet_size(struct usb_ov511 *ov, int size)
{
	int alt;

	if (ov51x_stop(ov) < 0)
		return -EIO;

	if (ov->bclass == BCL_OV518) {
		if (size == 0)
			alt = OV518_ALT_SIZE_0;
		else if (size == 128)
			alt = OV518_ALT_SIZE_128;
		else if (size == 256)
			alt = OV518_ALT_SIZE_256;
		else if (size == 384)
			alt = OV518_ALT_SIZE_384;
		else if (size == 512)
			alt = OV518_ALT_SIZE_512;
		else if (size == 640)
			alt = OV518_ALT_SIZE_640;
		else if (size == 768)
			alt = OV518_ALT_SIZE_768;
		else if (size == 896)
			alt = OV518_ALT_SIZE_896;
		else {
			err("Set packet size: invalid size (%d)", size);
			return -EINVAL;
		}
	} else {
		err("Set packet size: Invalid bridge type");
		return -EINVAL;
	}

	PDEBUG(3, "%d, alt=%d", size, alt);

	ov->packet_size = size;
	if (size > 0) {
		/* Program ISO FIFO size reg (packet number isn't included) */
		ov518_reg_w32(ov, 0x30, size, 2);

		if (ov->packet_numbering)
			++ov->packet_size;
	}

	if (usb_set_interface(ov->dev, ov->iface, alt) < 0) {
		err("Set packet size: set interface error");
		return -EBUSY;
	}

	/* Initialize the stream */
	if (reg_w(ov, 0x2f, 0x80) < 0)
		return -EIO;

	if (ov51x_restart(ov) < 0)
		return -EIO;

	if (ov51x_reset(ov, OV511_RESET_NOREGS) < 0)
		return -EIO;

	return 0;
}