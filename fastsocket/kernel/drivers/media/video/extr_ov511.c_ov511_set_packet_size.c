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
struct usb_ov511 {scalar_t__ bridge; int packet_size; int /*<<< orphan*/  iface; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BRG_OV511 ; 
 scalar_t__ BRG_OV511PLUS ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int OV511PLUS_ALT_SIZE_0 ; 
 int OV511PLUS_ALT_SIZE_129 ; 
 int OV511PLUS_ALT_SIZE_257 ; 
 int OV511PLUS_ALT_SIZE_33 ; 
 int OV511PLUS_ALT_SIZE_385 ; 
 int OV511PLUS_ALT_SIZE_513 ; 
 int OV511PLUS_ALT_SIZE_769 ; 
 int OV511PLUS_ALT_SIZE_961 ; 
 int OV511_ALT_SIZE_0 ; 
 int OV511_ALT_SIZE_257 ; 
 int OV511_ALT_SIZE_513 ; 
 int OV511_ALT_SIZE_769 ; 
 int OV511_ALT_SIZE_993 ; 
 int /*<<< orphan*/  OV511_RESET_NOREGS ; 
 int /*<<< orphan*/  PDEBUG (int,char*,int,int,int) ; 
 int /*<<< orphan*/  R51x_FIFO_PSIZE ; 
 int /*<<< orphan*/  err (char*,...) ; 
 scalar_t__ ov51x_reset (struct usb_ov511*,int /*<<< orphan*/ ) ; 
 scalar_t__ ov51x_restart (struct usb_ov511*) ; 
 scalar_t__ ov51x_stop (struct usb_ov511*) ; 
 scalar_t__ reg_w (struct usb_ov511*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ov511_set_packet_size(struct usb_ov511 *ov, int size)
{
	int alt, mult;

	if (ov51x_stop(ov) < 0)
		return -EIO;

	mult = size >> 5;

	if (ov->bridge == BRG_OV511) {
		if (size == 0)
			alt = OV511_ALT_SIZE_0;
		else if (size == 257)
			alt = OV511_ALT_SIZE_257;
		else if (size == 513)
			alt = OV511_ALT_SIZE_513;
		else if (size == 769)
			alt = OV511_ALT_SIZE_769;
		else if (size == 993)
			alt = OV511_ALT_SIZE_993;
		else {
			err("Set packet size: invalid size (%d)", size);
			return -EINVAL;
		}
	} else if (ov->bridge == BRG_OV511PLUS) {
		if (size == 0)
			alt = OV511PLUS_ALT_SIZE_0;
		else if (size == 33)
			alt = OV511PLUS_ALT_SIZE_33;
		else if (size == 129)
			alt = OV511PLUS_ALT_SIZE_129;
		else if (size == 257)
			alt = OV511PLUS_ALT_SIZE_257;
		else if (size == 385)
			alt = OV511PLUS_ALT_SIZE_385;
		else if (size == 513)
			alt = OV511PLUS_ALT_SIZE_513;
		else if (size == 769)
			alt = OV511PLUS_ALT_SIZE_769;
		else if (size == 961)
			alt = OV511PLUS_ALT_SIZE_961;
		else {
			err("Set packet size: invalid size (%d)", size);
			return -EINVAL;
		}
	} else {
		err("Set packet size: Invalid bridge type");
		return -EINVAL;
	}

	PDEBUG(3, "%d, mult=%d, alt=%d", size, mult, alt);

	if (reg_w(ov, R51x_FIFO_PSIZE, mult) < 0)
		return -EIO;

	if (usb_set_interface(ov->dev, ov->iface, alt) < 0) {
		err("Set packet size: set interface error");
		return -EBUSY;
	}

	if (ov51x_reset(ov, OV511_RESET_NOREGS) < 0)
		return -EIO;

	ov->packet_size = size;

	if (ov51x_restart(ov) < 0)
		return -EIO;

	return 0;
}