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
typedef  int u16 ;
struct uwb_rc_control_intf_class_desc {int /*<<< orphan*/  bcdRCIVersion; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct device dev; } ;
struct uwb_rc {int version; TYPE_1__ uwb_dev; struct hwarc* priv; } ;
struct usb_device {char** rawdescriptors; TYPE_3__* actconfig; TYPE_3__* config; } ;
struct usb_descriptor_header {scalar_t__ bDescriptorType; size_t bLength; } ;
struct hwarc {struct usb_device* usb_dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  wTotalLength; } ;
struct TYPE_6__ {TYPE_2__ desc; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ USB_DT_CS_RADIO_CONTROL ; 
 int __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hwarc_get_version(struct uwb_rc *rc)
{
	int result;

	struct hwarc *hwarc = rc->priv;
	struct uwb_rc_control_intf_class_desc *descr;
	struct device *dev = &rc->uwb_dev.dev;
	struct usb_device *usb_dev = hwarc->usb_dev;
	char *itr;
	struct usb_descriptor_header *hdr;
	size_t itr_size, actconfig_idx;
	u16 version;

	actconfig_idx = (usb_dev->actconfig - usb_dev->config) /
		sizeof(usb_dev->config[0]);
	itr = usb_dev->rawdescriptors[actconfig_idx];
	itr_size = le16_to_cpu(usb_dev->actconfig->desc.wTotalLength);
	while (itr_size >= sizeof(*hdr)) {
		hdr = (struct usb_descriptor_header *) itr;
		dev_dbg(dev, "Extra device descriptor: "
			"type %02x/%u bytes @ %zu (%zu left)\n",
			hdr->bDescriptorType, hdr->bLength,
			(itr - usb_dev->rawdescriptors[actconfig_idx]),
			itr_size);
		if (hdr->bDescriptorType == USB_DT_CS_RADIO_CONTROL)
			goto found;
		itr += hdr->bLength;
		itr_size -= hdr->bLength;
	}
	dev_err(dev, "cannot find Radio Control Interface Class descriptor\n");
	return -ENODEV;

found:
	result = -EINVAL;
	if (hdr->bLength > itr_size) {	/* is it available? */
		dev_err(dev, "incomplete Radio Control Interface Class "
			"descriptor (%zu bytes left, %u needed)\n",
			itr_size, hdr->bLength);
		goto error;
	}
	if (hdr->bLength < sizeof(*descr)) {
		dev_err(dev, "short Radio Control Interface Class "
			"descriptor\n");
		goto error;
	}
	descr = (struct uwb_rc_control_intf_class_desc *) hdr;
	/* Make LE fields CPU order */
	version = __le16_to_cpu(descr->bcdRCIVersion);
	if (version != 0x0100) {
		dev_err(dev, "Device reports protocol version 0x%04x. We "
			"do not support that. \n", version);
		result = -EINVAL;
		goto error;
	}
	rc->version = version;
	dev_dbg(dev, "Device supports WUSB protocol version 0x%04x \n",	rc->version);
	result = 0;
error:
	return result;
}