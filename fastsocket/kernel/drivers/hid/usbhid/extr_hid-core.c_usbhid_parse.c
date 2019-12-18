#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct usb_interface {struct usb_host_interface* cur_altsetting; } ;
struct TYPE_8__ {scalar_t__ bInterfaceSubClass; scalar_t__ bInterfaceProtocol; int /*<<< orphan*/  bInterfaceNumber; int /*<<< orphan*/  bNumEndpoints; } ;
struct usb_host_interface {TYPE_4__ desc; struct usb_host_interface* endpoint; } ;
struct TYPE_6__ {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct usb_device {TYPE_2__ descriptor; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct hid_device {int quirks; int /*<<< orphan*/  country; void* version; TYPE_1__ dev; } ;
struct hid_descriptor {int bNumDescriptors; TYPE_3__* desc; int /*<<< orphan*/  bCountryCode; int /*<<< orphan*/  bcdHID; } ;
struct TYPE_7__ {scalar_t__ bDescriptorType; int /*<<< orphan*/  wDescriptorLength; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HID_DT_HID ; 
 scalar_t__ HID_DT_REPORT ; 
 unsigned int HID_MAX_DESCRIPTOR_SIZE ; 
 int HID_QUIRK_IGNORE ; 
 int HID_QUIRK_NOGET ; 
 scalar_t__ USB_INTERFACE_PROTOCOL_KEYBOARD ; 
 scalar_t__ USB_INTERFACE_PROTOCOL_MOUSE ; 
 scalar_t__ USB_INTERFACE_SUBCLASS_BOOT ; 
 int /*<<< orphan*/  dbg_hid (char*,...) ; 
 int hid_get_class_descriptor (struct usb_device*,int /*<<< orphan*/ ,scalar_t__,char*,unsigned int) ; 
 int hid_parse_report (struct hid_device*,char*,unsigned int) ; 
 int /*<<< orphan*/  hid_set_idle (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct usb_interface* to_usb_interface (int /*<<< orphan*/ ) ; 
 scalar_t__ usb_get_extra_descriptor (struct usb_host_interface*,int /*<<< orphan*/ ,struct hid_descriptor**) ; 
 int usbhid_lookup_quirk (void*,void*) ; 

__attribute__((used)) static int usbhid_parse(struct hid_device *hid)
{
	struct usb_interface *intf = to_usb_interface(hid->dev.parent);
	struct usb_host_interface *interface = intf->cur_altsetting;
	struct usb_device *dev = interface_to_usbdev (intf);
	struct hid_descriptor *hdesc;
	u32 quirks = 0;
	unsigned int rsize = 0;
	char *rdesc;
	int ret, n;

	quirks = usbhid_lookup_quirk(le16_to_cpu(dev->descriptor.idVendor),
			le16_to_cpu(dev->descriptor.idProduct));

	if (quirks & HID_QUIRK_IGNORE)
		return -ENODEV;

	/* Many keyboards and mice don't like to be polled for reports,
	 * so we will always set the HID_QUIRK_NOGET flag for them. */
	if (interface->desc.bInterfaceSubClass == USB_INTERFACE_SUBCLASS_BOOT) {
		if (interface->desc.bInterfaceProtocol == USB_INTERFACE_PROTOCOL_KEYBOARD ||
			interface->desc.bInterfaceProtocol == USB_INTERFACE_PROTOCOL_MOUSE)
				quirks |= HID_QUIRK_NOGET;
	}

	if (usb_get_extra_descriptor(interface, HID_DT_HID, &hdesc) &&
	    (!interface->desc.bNumEndpoints ||
	     usb_get_extra_descriptor(&interface->endpoint[0], HID_DT_HID, &hdesc))) {
		dbg_hid("class descriptor not present\n");
		return -ENODEV;
	}

	hid->version = le16_to_cpu(hdesc->bcdHID);
	hid->country = hdesc->bCountryCode;

	for (n = 0; n < hdesc->bNumDescriptors; n++)
		if (hdesc->desc[n].bDescriptorType == HID_DT_REPORT)
			rsize = le16_to_cpu(hdesc->desc[n].wDescriptorLength);

	if (!rsize || rsize > HID_MAX_DESCRIPTOR_SIZE) {
		dbg_hid("weird size of report descriptor (%u)\n", rsize);
		return -EINVAL;
	}

	if (!(rdesc = kmalloc(rsize, GFP_KERNEL))) {
		dbg_hid("couldn't allocate rdesc memory\n");
		return -ENOMEM;
	}

	hid_set_idle(dev, interface->desc.bInterfaceNumber, 0, 0);

	ret = hid_get_class_descriptor(dev, interface->desc.bInterfaceNumber,
			HID_DT_REPORT, rdesc, rsize);
	if (ret < 0) {
		dbg_hid("reading report descriptor failed\n");
		kfree(rdesc);
		goto err;
	}

	ret = hid_parse_report(hid, rdesc, rsize);
	kfree(rdesc);
	if (ret) {
		dbg_hid("parsing report descriptor failed\n");
		goto err;
	}

	hid->quirks |= quirks;

	return 0;
err:
	return ret;
}