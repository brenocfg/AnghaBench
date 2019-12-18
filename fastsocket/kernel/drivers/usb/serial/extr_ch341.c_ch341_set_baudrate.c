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
struct usb_device {int dummy; } ;
struct ch341_private {unsigned long baud_rate; } ;

/* Variables and functions */
 short CH341_BAUDBASE_DIVMAX ; 
 unsigned long CH341_BAUDBASE_FACTOR ; 
 int EINVAL ; 
 int ch341_control_out (struct usb_device*,int,int,short) ; 
 int /*<<< orphan*/  dbg (char*,unsigned long) ; 

__attribute__((used)) static int ch341_set_baudrate(struct usb_device *dev,
			      struct ch341_private *priv)
{
	short a, b;
	int r;
	unsigned long factor;
	short divisor;

	dbg("ch341_set_baudrate(%d)", priv->baud_rate);

	if (!priv->baud_rate)
		return -EINVAL;
	factor = (CH341_BAUDBASE_FACTOR / priv->baud_rate);
	divisor = CH341_BAUDBASE_DIVMAX;

	while ((factor > 0xfff0) && divisor) {
		factor >>= 3;
		divisor--;
	}

	if (factor > 0xfff0)
		return -EINVAL;

	factor = 0x10000 - factor;
	a = (factor & 0xff00) | divisor;
	b = factor & 0xff;

	r = ch341_control_out(dev, 0x9a, 0x1312, a);
	if (!r)
		r = ch341_control_out(dev, 0x9a, 0x0f2c, b);

	return r;
}