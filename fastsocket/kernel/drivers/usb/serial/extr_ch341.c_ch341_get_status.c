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
struct ch341_private {char line_status; int /*<<< orphan*/  lock; scalar_t__ multi_status_change; } ;

/* Variables and functions */
 char CH341_BITS_MODEM_STAT ; 
 int ENOMEM ; 
 int EPROTO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ch341_control_in (struct usb_device*,int,int,int /*<<< orphan*/ ,char*,unsigned int const) ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (unsigned int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ch341_get_status(struct usb_device *dev, struct ch341_private *priv)
{
	char *buffer;
	int r;
	const unsigned size = 8;
	unsigned long flags;

	dbg("ch341_get_status()");

	buffer = kmalloc(size, GFP_KERNEL);
	if (!buffer)
		return -ENOMEM;

	r = ch341_control_in(dev, 0x95, 0x0706, 0, buffer, size);
	if (r < 0)
		goto out;

	/* setup the private status if available */
	if (r == 2) {
		r = 0;
		spin_lock_irqsave(&priv->lock, flags);
		priv->line_status = (~(*buffer)) & CH341_BITS_MODEM_STAT;
		priv->multi_status_change = 0;
		spin_unlock_irqrestore(&priv->lock, flags);
	} else
		r = -EPROTO;

out:	kfree(buffer);
	return r;
}