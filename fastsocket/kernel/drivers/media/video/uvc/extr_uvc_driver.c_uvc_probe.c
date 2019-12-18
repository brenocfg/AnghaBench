#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct uvc_device {int quirks; int uvc_version; int /*<<< orphan*/  name; int /*<<< orphan*/  intfnum; int /*<<< orphan*/  intf; int /*<<< orphan*/  udev; int /*<<< orphan*/  nmappings; int /*<<< orphan*/  users; int /*<<< orphan*/  nstreams; int /*<<< orphan*/  streams; int /*<<< orphan*/  chains; int /*<<< orphan*/  entities; } ;
struct usb_interface {TYPE_2__* cur_altsetting; } ;
struct usb_device_id {int driver_info; int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct TYPE_6__ {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct usb_device {char* product; scalar_t__ autosuspend_disabled; TYPE_3__ descriptor; int /*<<< orphan*/  devpath; } ;
struct TYPE_4__ {int /*<<< orphan*/  bInterfaceNumber; } ;
struct TYPE_5__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  UVC_TRACE_PROBE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 struct uvc_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  usb_get_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_get_intf (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct uvc_device*) ; 
 scalar_t__ uvc_ctrl_init_device (struct uvc_device*) ; 
 scalar_t__ uvc_parse_control (struct uvc_device*) ; 
 int /*<<< orphan*/  uvc_printk (int /*<<< orphan*/ ,char*,...) ; 
 int uvc_quirks_param ; 
 scalar_t__ uvc_register_chains (struct uvc_device*) ; 
 scalar_t__ uvc_scan_device (struct uvc_device*) ; 
 int uvc_status_init (struct uvc_device*) ; 
 int /*<<< orphan*/  uvc_trace (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  uvc_unregister_video (struct uvc_device*) ; 

__attribute__((used)) static int uvc_probe(struct usb_interface *intf,
		     const struct usb_device_id *id)
{
	struct usb_device *udev = interface_to_usbdev(intf);
	struct uvc_device *dev;
	int ret;

	if (id->idVendor && id->idProduct)
		uvc_trace(UVC_TRACE_PROBE, "Probing known UVC device %s "
				"(%04x:%04x)\n", udev->devpath, id->idVendor,
				id->idProduct);
	else
		uvc_trace(UVC_TRACE_PROBE, "Probing generic UVC device %s\n",
				udev->devpath);

	/* Allocate memory for the device and initialize it. */
	if ((dev = kzalloc(sizeof *dev, GFP_KERNEL)) == NULL)
		return -ENOMEM;

	INIT_LIST_HEAD(&dev->entities);
	INIT_LIST_HEAD(&dev->chains);
	INIT_LIST_HEAD(&dev->streams);
	atomic_set(&dev->nstreams, 0);
	atomic_set(&dev->users, 0);
	atomic_set(&dev->nmappings, 0);

	dev->udev = usb_get_dev(udev);
	dev->intf = usb_get_intf(intf);
	dev->intfnum = intf->cur_altsetting->desc.bInterfaceNumber;
	dev->quirks = (uvc_quirks_param == -1)
		    ? id->driver_info : uvc_quirks_param;

	if (udev->product != NULL)
		strlcpy(dev->name, udev->product, sizeof dev->name);
	else
		snprintf(dev->name, sizeof dev->name,
			"UVC Camera (%04x:%04x)",
			le16_to_cpu(udev->descriptor.idVendor),
			le16_to_cpu(udev->descriptor.idProduct));

	/* Parse the Video Class control descriptor. */
	if (uvc_parse_control(dev) < 0) {
		uvc_trace(UVC_TRACE_PROBE, "Unable to parse UVC "
			"descriptors.\n");
		goto error;
	}

	uvc_printk(KERN_INFO, "Found UVC %u.%02x device %s (%04x:%04x)\n",
		dev->uvc_version >> 8, dev->uvc_version & 0xff,
		udev->product ? udev->product : "<unnamed>",
		le16_to_cpu(udev->descriptor.idVendor),
		le16_to_cpu(udev->descriptor.idProduct));

	if (dev->quirks != id->driver_info) {
		uvc_printk(KERN_INFO, "Forcing device quirks to 0x%x by module "
			"parameter for testing purpose.\n", dev->quirks);
		uvc_printk(KERN_INFO, "Please report required quirks to the "
			"linux-uvc-devel mailing list.\n");
	}

	/* Initialize controls. */
	if (uvc_ctrl_init_device(dev) < 0)
		goto error;

	/* Scan the device for video chains. */
	if (uvc_scan_device(dev) < 0)
		goto error;

	/* Register video devices. */
	if (uvc_register_chains(dev) < 0)
		goto error;

	/* Save our data pointer in the interface data. */
	usb_set_intfdata(intf, dev);

	/* Initialize the interrupt URB. */
	if ((ret = uvc_status_init(dev)) < 0) {
		uvc_printk(KERN_INFO, "Unable to initialize the status "
			"endpoint (%d), status interrupt will not be "
			"supported.\n", ret);
	}

	uvc_trace(UVC_TRACE_PROBE, "UVC device initialized.\n");
	udev->autosuspend_disabled = 0;
	return 0;

error:
	uvc_unregister_video(dev);
	return -ENODEV;
}