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
typedef  scalar_t__ u32 ;
typedef  size_t u16 ;
struct wusb_cbaf_assoc_request {int /*<<< orphan*/  AssociationDataIndex; int /*<<< orphan*/  AssociationTypeInfoSize; int /*<<< orphan*/  AssociationSubTypeId; int /*<<< orphan*/  AssociationTypeId; } ;
struct wusb_cbaf_assoc_info {int /*<<< orphan*/  NumAssociationRequests; int /*<<< orphan*/  Length; } ;
struct device {int dummy; } ;
struct cbaf {struct wusb_cbaf_assoc_info* buffer; int /*<<< orphan*/  buffer_size; TYPE_3__* usb_iface; int /*<<< orphan*/  usb_dev; } ;
struct TYPE_6__ {TYPE_2__* cur_altsetting; struct device dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  bInterfaceNumber; } ;
struct TYPE_5__ {TYPE_1__ desc; } ;

/* Variables and functions */
#define  AR_TYPE_WUSB 130 
#define  AR_TYPE_WUSB_ASSOCIATE 129 
#define  AR_TYPE_WUSB_RETRIEVE_HOST_INFO 128 
 int /*<<< orphan*/  CBAF_REQ_GET_ASSOCIATION_INFORMATION ; 
 int EINVAL ; 
 int USB_DIR_IN ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_CLASS ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,size_t,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wusb_cbaf_assoc_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cbaf_check(struct cbaf *cbaf)
{
	int result;
	struct device *dev = &cbaf->usb_iface->dev;
	struct wusb_cbaf_assoc_info *assoc_info;
	struct wusb_cbaf_assoc_request *assoc_request;
	size_t assoc_size;
	void *itr, *top;
	int ar_rhi = 0, ar_assoc = 0;

	result = usb_control_msg(
		cbaf->usb_dev, usb_rcvctrlpipe(cbaf->usb_dev, 0),
		CBAF_REQ_GET_ASSOCIATION_INFORMATION,
		USB_DIR_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
		0, cbaf->usb_iface->cur_altsetting->desc.bInterfaceNumber,
		cbaf->buffer, cbaf->buffer_size, 1000 /* FIXME: arbitrary */);
	if (result < 0) {
		dev_err(dev, "Cannot get available association types: %d\n",
			result);
		return result;
	}

	assoc_info = cbaf->buffer;
	if (result < sizeof(*assoc_info)) {
		dev_err(dev, "Not enough data to decode association info "
			"header (%zu vs %zu bytes required)\n",
			(size_t)result, sizeof(*assoc_info));
		return result;
	}

	assoc_size = le16_to_cpu(assoc_info->Length);
	if (result < assoc_size) {
		dev_err(dev, "Not enough data to decode association info "
			"(%zu vs %zu bytes required)\n",
			(size_t)assoc_size, sizeof(*assoc_info));
		return result;
	}
	/*
	 * From now on, we just verify, but won't error out unless we
	 * don't find the AR_TYPE_WUSB_{RETRIEVE_HOST_INFO,ASSOCIATE}
	 * types.
	 */
	itr = cbaf->buffer + sizeof(*assoc_info);
	top = cbaf->buffer + assoc_size;
	dev_dbg(dev, "Found %u association requests (%zu bytes)\n",
		 assoc_info->NumAssociationRequests, assoc_size);

	while (itr < top) {
		u16 ar_type, ar_subtype;
		u32 ar_size;
		const char *ar_name;

		assoc_request = itr;

		if (top - itr < sizeof(*assoc_request)) {
			dev_err(dev, "Not enough data to decode associaton "
				"request (%zu vs %zu bytes needed)\n",
				top - itr, sizeof(*assoc_request));
			break;
		}

		ar_type = le16_to_cpu(assoc_request->AssociationTypeId);
		ar_subtype = le16_to_cpu(assoc_request->AssociationSubTypeId);
		ar_size = le32_to_cpu(assoc_request->AssociationTypeInfoSize);
		ar_name = "unknown";

		switch (ar_type) {
		case AR_TYPE_WUSB:
			/* Verify we have what is mandated by [WUSB-AM]. */
			switch (ar_subtype) {
			case AR_TYPE_WUSB_RETRIEVE_HOST_INFO:
				ar_name = "RETRIEVE_HOST_INFO";
				ar_rhi = 1;
				break;
			case AR_TYPE_WUSB_ASSOCIATE:
				/* send assoc data */
				ar_name = "ASSOCIATE";
				ar_assoc = 1;
				break;
			};
			break;
		};

		dev_dbg(dev, "Association request #%02u: 0x%04x/%04x "
			 "(%zu bytes): %s\n",
			 assoc_request->AssociationDataIndex, ar_type,
			 ar_subtype, (size_t)ar_size, ar_name);

		itr += sizeof(*assoc_request);
	}

	if (!ar_rhi) {
		dev_err(dev, "Missing RETRIEVE_HOST_INFO association "
			"request\n");
		return -EINVAL;
	}
	if (!ar_assoc) {
		dev_err(dev, "Missing ASSOCIATE association request\n");
		return -EINVAL;
	}

	return 0;
}