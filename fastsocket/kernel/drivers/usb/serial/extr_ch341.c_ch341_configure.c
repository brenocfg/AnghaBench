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
struct ch341_private {int /*<<< orphan*/  line_control; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ch341_control_in (struct usb_device*,int,int,int /*<<< orphan*/ ,char*,unsigned int const) ; 
 int ch341_control_out (struct usb_device*,int,int,int) ; 
 int ch341_get_status (struct usb_device*,struct ch341_private*) ; 
 int ch341_set_baudrate (struct usb_device*,struct ch341_private*) ; 
 int ch341_set_handshake (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (unsigned int const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ch341_configure(struct usb_device *dev, struct ch341_private *priv)
{
	char *buffer;
	int r;
	const unsigned size = 8;

	dbg("ch341_configure()");

	buffer = kmalloc(size, GFP_KERNEL);
	if (!buffer)
		return -ENOMEM;

	/* expect two bytes 0x27 0x00 */
	r = ch341_control_in(dev, 0x5f, 0, 0, buffer, size);
	if (r < 0)
		goto out;

	r = ch341_control_out(dev, 0xa1, 0, 0);
	if (r < 0)
		goto out;

	r = ch341_set_baudrate(dev, priv);
	if (r < 0)
		goto out;

	/* expect two bytes 0x56 0x00 */
	r = ch341_control_in(dev, 0x95, 0x2518, 0, buffer, size);
	if (r < 0)
		goto out;

	r = ch341_control_out(dev, 0x9a, 0x2518, 0x0050);
	if (r < 0)
		goto out;

	/* expect 0xff 0xee */
	r = ch341_get_status(dev, priv);
	if (r < 0)
		goto out;

	r = ch341_control_out(dev, 0xa1, 0x501f, 0xd90a);
	if (r < 0)
		goto out;

	r = ch341_set_baudrate(dev, priv);
	if (r < 0)
		goto out;

	r = ch341_set_handshake(dev, priv->line_control);
	if (r < 0)
		goto out;

	/* expect 0x9f 0xee */
	r = ch341_get_status(dev, priv);

out:	kfree(buffer);
	return r;
}