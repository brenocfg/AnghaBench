#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int /*<<< orphan*/  dev; struct usb_host_interface* cur_altsetting; } ;
struct TYPE_10__ {int bInterfaceClass; scalar_t__ bInterfaceSubClass; scalar_t__ bInterfaceProtocol; int bNumEndpoints; } ;
struct usb_host_interface {TYPE_3__* endpoint; TYPE_2__ desc; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_9__ {int bNumConfigurations; } ;
struct usb_device {TYPE_1__ descriptor; } ;
struct TYPE_13__ {int bEndpointAddress; int bInterval; } ;
struct TYPE_12__ {int* endpoint; int /*<<< orphan*/  io_lock; int /*<<< orphan*/  state; int /*<<< orphan*/  download_urb_buffer; struct usb_device* dev; int /*<<< orphan*/  download_urb; int /*<<< orphan*/  write_urb_buffer; int /*<<< orphan*/  write_urb; int /*<<< orphan*/  irq_urb_buffer; int /*<<< orphan*/  irq_urb; scalar_t__ open; } ;
struct TYPE_11__ {TYPE_7__ desc; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  READY ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 TYPE_4__* mdc800 ; 
 int /*<<< orphan*/  mdc800_class ; 
 int /*<<< orphan*/ * mdc800_ed ; 
 scalar_t__ mdc800_endpoint_equals (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdc800_usb_download_notify ; 
 int /*<<< orphan*/  mdc800_usb_irq ; 
 int /*<<< orphan*/  mdc800_usb_write_notify ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ ,struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  usb_fill_int_urb (int /*<<< orphan*/ ,struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (struct usb_device*,int) ; 
 int /*<<< orphan*/  usb_rcvintpipe (struct usb_device*,int) ; 
 int usb_register_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,TYPE_4__*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (struct usb_device*,int) ; 

__attribute__((used)) static int mdc800_usb_probe (struct usb_interface *intf,
			       const struct usb_device_id *id)
{
	int i,j;
	struct usb_host_interface *intf_desc;
	struct usb_device *dev = interface_to_usbdev (intf);
	int irq_interval=0;
	int retval;

	dbg ("(mdc800_usb_probe) called.");


	if (mdc800->dev != NULL)
	{
		dev_warn(&intf->dev, "only one Mustek MDC800 is supported.\n");
		return -ENODEV;
	}

	if (dev->descriptor.bNumConfigurations != 1)
	{
		dev_err(&intf->dev,
			"probe fails -> wrong Number of Configuration\n");
		return -ENODEV;
	}
	intf_desc = intf->cur_altsetting;

	if (
			( intf_desc->desc.bInterfaceClass != 0xff )
		||	( intf_desc->desc.bInterfaceSubClass != 0 )
		|| ( intf_desc->desc.bInterfaceProtocol != 0 )
		|| ( intf_desc->desc.bNumEndpoints != 4)
	)
	{
		dev_err(&intf->dev, "probe fails -> wrong Interface\n");
		return -ENODEV;
	}

	/* Check the Endpoints */
	for (i=0; i<4; i++)
	{
		mdc800->endpoint[i]=-1;
		for (j=0; j<4; j++)
		{
			if (mdc800_endpoint_equals (&intf_desc->endpoint [j].desc,&mdc800_ed [i]))
			{
				mdc800->endpoint[i]=intf_desc->endpoint [j].desc.bEndpointAddress ;
				if (i==1)
				{
					irq_interval=intf_desc->endpoint [j].desc.bInterval;
				}
			}
		}
		if (mdc800->endpoint[i] == -1)
		{
			dev_err(&intf->dev, "probe fails -> Wrong Endpoints.\n");
			return -ENODEV;
		}
	}


	dev_info(&intf->dev, "Found Mustek MDC800 on USB.\n");

	mutex_lock(&mdc800->io_lock);

	retval = usb_register_dev(intf, &mdc800_class);
	if (retval) {
		dev_err(&intf->dev, "Not able to get a minor for this device.\n");
		mutex_unlock(&mdc800->io_lock);
		return -ENODEV;
	}

	mdc800->dev=dev;
	mdc800->open=0;

	/* Setup URB Structs */
	usb_fill_int_urb (
		mdc800->irq_urb,
		mdc800->dev,
		usb_rcvintpipe (mdc800->dev,mdc800->endpoint [1]),
		mdc800->irq_urb_buffer,
		8,
		mdc800_usb_irq,
		mdc800,
		irq_interval
	);

	usb_fill_bulk_urb (
		mdc800->write_urb,
		mdc800->dev,
		usb_sndbulkpipe (mdc800->dev, mdc800->endpoint[0]),
		mdc800->write_urb_buffer,
		8,
		mdc800_usb_write_notify,
		mdc800
	);

	usb_fill_bulk_urb (
		mdc800->download_urb,
		mdc800->dev,
		usb_rcvbulkpipe (mdc800->dev, mdc800->endpoint [3]),
		mdc800->download_urb_buffer,
		64,
		mdc800_usb_download_notify,
		mdc800
	);

	mdc800->state=READY;

	mutex_unlock(&mdc800->io_lock);
	
	usb_set_intfdata(intf, mdc800);
	return 0;
}