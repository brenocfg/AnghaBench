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
struct usb_endpoint_descriptor {int /*<<< orphan*/  bInterval; int /*<<< orphan*/  bEndpointAddress; } ;
struct i2400mu {int /*<<< orphan*/  notif_urb; int /*<<< orphan*/  usb_dev; TYPE_1__* usb_iface; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  I2400MU_EP_NOTIFICATION ; 
 int /*<<< orphan*/  I2400MU_MAX_NOTIFICATION_LEN ; 
 int /*<<< orphan*/  d_fnend (int,struct device*,char*,struct i2400mu*,int) ; 
 int /*<<< orphan*/  d_fnstart (int,struct device*,char*,struct i2400mu*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  i2400mu_notification_cb ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_fill_int_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct i2400mu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 struct usb_endpoint_descriptor* usb_get_epd (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int usb_rcvintpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int) ; 

int i2400mu_notification_setup(struct i2400mu *i2400mu)
{
	struct device *dev = &i2400mu->usb_iface->dev;
	int usb_pipe, ret = 0;
	struct usb_endpoint_descriptor *epd;
	char *buf;

	d_fnstart(4, dev, "(i2400m %p)\n", i2400mu);
	buf = kmalloc(I2400MU_MAX_NOTIFICATION_LEN, GFP_KERNEL | GFP_DMA);
	if (buf == NULL) {
		dev_err(dev, "notification: buffer allocation failed\n");
		ret = -ENOMEM;
		goto error_buf_alloc;
	}

	i2400mu->notif_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!i2400mu->notif_urb) {
		ret = -ENOMEM;
		dev_err(dev, "notification: cannot allocate URB\n");
		goto error_alloc_urb;
	}
	epd = usb_get_epd(i2400mu->usb_iface, I2400MU_EP_NOTIFICATION);
	usb_pipe = usb_rcvintpipe(i2400mu->usb_dev, epd->bEndpointAddress);
	usb_fill_int_urb(i2400mu->notif_urb, i2400mu->usb_dev, usb_pipe,
			 buf, I2400MU_MAX_NOTIFICATION_LEN,
			 i2400mu_notification_cb, i2400mu, epd->bInterval);
	ret = usb_submit_urb(i2400mu->notif_urb, GFP_KERNEL);
	if (ret != 0) {
		dev_err(dev, "notification: cannot submit URB: %d\n", ret);
		goto error_submit;
	}
	d_fnend(4, dev, "(i2400m %p) = %d\n", i2400mu, ret);
	return ret;

error_submit:
	usb_free_urb(i2400mu->notif_urb);
error_alloc_urb:
	kfree(buf);
error_buf_alloc:
	d_fnend(4, dev, "(i2400m %p) = %d\n", i2400mu, ret);
	return ret;
}