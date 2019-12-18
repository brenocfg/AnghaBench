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
typedef  int u8 ;
struct usbnet {int rx_urb_size; TYPE_3__* udev; TYPE_2__* net; } ;
struct usb_interface {int /*<<< orphan*/  dev; TYPE_1__* cur_altsetting; } ;
struct usb_cdc_mdlm_detail_desc {int bLength; int* bDetailData; int /*<<< orphan*/  bGuidDescriptorType; } ;
struct usb_cdc_mdlm_desc {int bLength; int /*<<< orphan*/  bGUID; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int hard_header_len; int mtu; } ;
struct TYPE_4__ {int* extra; int extralen; } ;

/* Variables and functions */
 int ENODEV ; 
#define  USB_CDC_MDLM_DETAIL_TYPE 129 
#define  USB_CDC_MDLM_TYPE 128 
 int USB_DT_CS_INTERFACE ; 
 int /*<<< orphan*/  blan_guid ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  safe_guid ; 
 int usbnet_get_endpoints (struct usbnet*,struct usb_interface*) ; 

__attribute__((used)) static int blan_mdlm_bind(struct usbnet *dev, struct usb_interface *intf)
{
	u8				*buf = intf->cur_altsetting->extra;
	int				len = intf->cur_altsetting->extralen;
	struct usb_cdc_mdlm_desc	*desc = NULL;
	struct usb_cdc_mdlm_detail_desc	*detail = NULL;

	while (len > 3) {
		if (buf [1] != USB_DT_CS_INTERFACE)
			goto next_desc;

		/* use bDescriptorSubType, and just verify that we get a
		 * "BLAN" (or "SAFE") descriptor.
		 */
		switch (buf [2]) {
		case USB_CDC_MDLM_TYPE:
			if (desc) {
				dev_dbg(&intf->dev, "extra MDLM\n");
				goto bad_desc;
			}
			desc = (void *) buf;
			if (desc->bLength != sizeof *desc) {
				dev_dbg(&intf->dev, "MDLM len %u\n",
					desc->bLength);
				goto bad_desc;
			}
			/* expect bcdVersion 1.0, ignore */
			if (memcmp(&desc->bGUID, blan_guid, 16)
				    && memcmp(&desc->bGUID, safe_guid, 16) ) {
				/* hey, this one might _really_ be MDLM! */
				dev_dbg(&intf->dev, "MDLM guid\n");
				goto bad_desc;
			}
			break;
		case USB_CDC_MDLM_DETAIL_TYPE:
			if (detail) {
				dev_dbg(&intf->dev, "extra MDLM detail\n");
				goto bad_desc;
			}
			detail = (void *) buf;
			switch (detail->bGuidDescriptorType) {
			case 0:			/* "SAFE" */
				if (detail->bLength != (sizeof *detail + 2))
					goto bad_detail;
				break;
			case 1:			/* "BLAN" */
				if (detail->bLength != (sizeof *detail + 3))
					goto bad_detail;
				break;
			default:
				goto bad_detail;
			}

			/* assuming we either noticed BLAN already, or will
			 * find it soon, there are some data bytes here:
			 *  - bmNetworkCapabilities (unused)
			 *  - bmDataCapabilities (bits, see below)
			 *  - bPad (ignored, for PADAFTER -- BLAN-only)
			 * bits are:
			 *  - 0x01 -- Zaurus framing (add CRC)
			 *  - 0x02 -- PADBEFORE (CRC includes some padding)
			 *  - 0x04 -- PADAFTER (some padding after CRC)
			 *  - 0x08 -- "fermat" packet mangling (for hw bugs)
			 * the PADBEFORE appears not to matter; we interop
			 * with devices that use it and those that don't.
			 */
			if ((detail->bDetailData[1] & ~0x02) != 0x01) {
				/* bmDataCapabilities == 0 would be fine too,
				 * but framing is minidriver-coupled for now.
				 */
bad_detail:
				dev_dbg(&intf->dev,
						"bad MDLM detail, %d %d %d\n",
						detail->bLength,
						detail->bDetailData[0],
						detail->bDetailData[2]);
				goto bad_desc;
			}

			/* same extra framing as for non-BLAN mode */
			dev->net->hard_header_len += 6;
			dev->rx_urb_size = dev->net->hard_header_len
					+ dev->net->mtu;
			break;
		}
next_desc:
		len -= buf [0];	/* bLength */
		buf += buf [0];
	}

	if (!desc || !detail) {
		dev_dbg(&intf->dev, "missing cdc mdlm %s%sdescriptor\n",
			desc ? "" : "func ",
			detail ? "" : "detail ");
		goto bad_desc;
	}

	/* There's probably a CDC Ethernet descriptor there, but we can't
	 * rely on the Ethernet address it provides since not all vendors
	 * bother to make it unique.  Likewise there's no point in tracking
	 * of the CDC event notifications.
	 */
	return usbnet_get_endpoints(dev, intf);

bad_desc:
	dev_info(&dev->udev->dev, "unsupported MDLM descriptors\n");
	return -ENODEV;
}