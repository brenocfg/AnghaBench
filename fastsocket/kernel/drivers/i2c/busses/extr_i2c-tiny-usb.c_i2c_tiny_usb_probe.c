#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_10__ {TYPE_6__ dev; int /*<<< orphan*/  name; struct i2c_tiny_usb* algo_data; int /*<<< orphan*/ * algo; int /*<<< orphan*/  class; int /*<<< orphan*/  owner; } ;
struct i2c_tiny_usb {TYPE_3__ adapter; struct usb_interface* interface; TYPE_4__* usb_dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  bcdDevice; } ;
struct TYPE_11__ {int devnum; TYPE_2__* bus; TYPE_1__ descriptor; } ;
struct TYPE_9__ {int busnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SET_DELAY ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_CLASS_HWMON ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  delay ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_6__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_6__*,char*,...) ; 
 int /*<<< orphan*/  i2c_add_adapter (TYPE_3__*) ; 
 int /*<<< orphan*/  i2c_tiny_usb_free (struct i2c_tiny_usb*) ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 struct i2c_tiny_usb* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int) ; 
 int /*<<< orphan*/  usb_algorithm ; 
 TYPE_4__* usb_get_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct i2c_tiny_usb*) ; 
 scalar_t__ usb_write (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i2c_tiny_usb_probe(struct usb_interface *interface,
			      const struct usb_device_id *id)
{
	struct i2c_tiny_usb *dev;
	int retval = -ENOMEM;
	u16 version;

	dev_dbg(&interface->dev, "probing usb device\n");

	/* allocate memory for our device state and initialize it */
	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (dev == NULL) {
		dev_err(&interface->dev, "Out of memory\n");
		goto error;
	}

	dev->usb_dev = usb_get_dev(interface_to_usbdev(interface));
	dev->interface = interface;

	/* save our data pointer in this interface device */
	usb_set_intfdata(interface, dev);

	version = le16_to_cpu(dev->usb_dev->descriptor.bcdDevice);
	dev_info(&interface->dev,
		 "version %x.%02x found at bus %03d address %03d\n",
		 version >> 8, version & 0xff,
		 dev->usb_dev->bus->busnum, dev->usb_dev->devnum);

	/* setup i2c adapter description */
	dev->adapter.owner = THIS_MODULE;
	dev->adapter.class = I2C_CLASS_HWMON;
	dev->adapter.algo = &usb_algorithm;
	dev->adapter.algo_data = dev;
	snprintf(dev->adapter.name, sizeof(dev->adapter.name),
		 "i2c-tiny-usb at bus %03d device %03d",
		 dev->usb_dev->bus->busnum, dev->usb_dev->devnum);

	if (usb_write(&dev->adapter, CMD_SET_DELAY, delay, 0, NULL, 0) != 0) {
		dev_err(&dev->adapter.dev,
			"failure setting delay to %dus\n", delay);
		retval = -EIO;
		goto error;
	}

	dev->adapter.dev.parent = &dev->interface->dev;

	/* and finally attach to i2c layer */
	i2c_add_adapter(&dev->adapter);

	/* inform user about successful attachment to i2c layer */
	dev_info(&dev->adapter.dev, "connected i2c-tiny-usb device\n");

	return 0;

 error:
	if (dev)
		i2c_tiny_usb_free(dev);

	return retval;
}