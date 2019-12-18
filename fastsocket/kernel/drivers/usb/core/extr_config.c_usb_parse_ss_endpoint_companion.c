#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct usb_ss_ep_comp_descriptor {scalar_t__ bDescriptorType; int bMaxBurst; int bmAttributes; int /*<<< orphan*/  wBytesPerInterval; scalar_t__ bLength; } ;
struct TYPE_7__ {int /*<<< orphan*/  bEndpointAddress; int /*<<< orphan*/  wMaxPacketSize; } ;
struct usb_host_endpoint {TYPE_2__ desc; TYPE_1__* ss_ep_comp; } ;
struct device {int dummy; } ;
struct TYPE_6__ {unsigned char* extra; int extralen; struct usb_ss_ep_comp_descriptor desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_DT_ENDPOINT ; 
 int /*<<< orphan*/  USB_DT_INTERFACE ; 
 scalar_t__ USB_DT_SS_ENDPOINT_COMP ; 
 int /*<<< orphan*/  USB_DT_SS_EP_COMP_SIZE ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 int find_next_descriptor (unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct usb_ss_ep_comp_descriptor*,struct usb_ss_ep_comp_descriptor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plural (int) ; 
 scalar_t__ usb_endpoint_xfer_bulk (TYPE_2__*) ; 
 scalar_t__ usb_endpoint_xfer_control (TYPE_2__*) ; 
 scalar_t__ usb_endpoint_xfer_int (TYPE_2__*) ; 
 scalar_t__ usb_endpoint_xfer_isoc (TYPE_2__*) ; 

__attribute__((used)) static int usb_parse_ss_endpoint_companion(struct device *ddev, int cfgno,
		int inum, int asnum, struct usb_host_endpoint *ep,
		int num_ep, unsigned char *buffer, int size)
{
	unsigned char *buffer_start = buffer;
	struct usb_ss_ep_comp_descriptor	*desc;
	int retval;
	int num_skipped;
	int max_tx;
	int i;

	desc = (struct usb_ss_ep_comp_descriptor *) buffer;
	if (desc->bDescriptorType != USB_DT_SS_ENDPOINT_COMP) {
		dev_warn(ddev, "No SuperSpeed endpoint companion for config %d "
				" interface %d altsetting %d ep %d: "
				"using minimum values\n",
				cfgno, inum, asnum, ep->desc.bEndpointAddress);
		/*
		 * The next descriptor is for an Endpoint or Interface,
		 * no extra descriptors to copy into the companion structure,
		 * and we didn't eat up any of the buffer.
		 */
		return 0;
	}
	memcpy(&ep->ss_ep_comp->desc, desc, USB_DT_SS_EP_COMP_SIZE);
	desc = &ep->ss_ep_comp->desc;
	buffer += desc->bLength;
	size -= desc->bLength;

	/* Eat up the other descriptors we don't care about */
	ep->ss_ep_comp->extra = buffer;
	i = find_next_descriptor(buffer, size, USB_DT_ENDPOINT,
			USB_DT_INTERFACE, &num_skipped);
	ep->ss_ep_comp->extralen = i;
	buffer += i;
	size -= i;
	retval = buffer - buffer_start;
	if (num_skipped > 0)
		dev_dbg(ddev, "skipped %d descriptor%s after %s\n",
				num_skipped, plural(num_skipped),
				"SuperSpeed endpoint companion");

	/* Check the various values */
	if (usb_endpoint_xfer_control(&ep->desc) && desc->bMaxBurst != 0) {
		dev_warn(ddev, "Control endpoint with bMaxBurst = %d in "
				"config %d interface %d altsetting %d ep %d: "
				"setting to zero\n", desc->bMaxBurst,
				cfgno, inum, asnum, ep->desc.bEndpointAddress);
		desc->bMaxBurst = 0;
	}
	if (desc->bMaxBurst > 15) {
		dev_warn(ddev, "Endpoint with bMaxBurst = %d in "
				"config %d interface %d altsetting %d ep %d: "
				"setting to 15\n", desc->bMaxBurst,
				cfgno, inum, asnum, ep->desc.bEndpointAddress);
		desc->bMaxBurst = 15;
	}
	if ((usb_endpoint_xfer_control(&ep->desc) || usb_endpoint_xfer_int(&ep->desc))
			&& desc->bmAttributes != 0) {
		dev_warn(ddev, "%s endpoint with bmAttributes = %d in "
				"config %d interface %d altsetting %d ep %d: "
				"setting to zero\n",
				usb_endpoint_xfer_control(&ep->desc) ? "Control" : "Bulk",
				desc->bmAttributes,
				cfgno, inum, asnum, ep->desc.bEndpointAddress);
		desc->bmAttributes = 0;
	}
	if (usb_endpoint_xfer_bulk(&ep->desc) && desc->bmAttributes > 16) {
		dev_warn(ddev, "Bulk endpoint with more than 65536 streams in "
				"config %d interface %d altsetting %d ep %d: "
				"setting to max\n",
				cfgno, inum, asnum, ep->desc.bEndpointAddress);
		desc->bmAttributes = 16;
	}
	if (usb_endpoint_xfer_isoc(&ep->desc) && desc->bmAttributes > 2) {
		dev_warn(ddev, "Isoc endpoint has Mult of %d in "
				"config %d interface %d altsetting %d ep %d: "
				"setting to 3\n", desc->bmAttributes + 1,
				cfgno, inum, asnum, ep->desc.bEndpointAddress);
		desc->bmAttributes = 2;
	}
	if (usb_endpoint_xfer_isoc(&ep->desc)) {
		max_tx = (desc->bMaxBurst + 1) * (desc->bmAttributes + 1) *
			le16_to_cpu(ep->desc.wMaxPacketSize);
	} else if (usb_endpoint_xfer_int(&ep->desc)) {
		max_tx = le16_to_cpu(ep->desc.wMaxPacketSize) *
			(desc->bMaxBurst + 1);
	} else {
		goto valid;
	}
	if (le16_to_cpu(desc->wBytesPerInterval) > max_tx) {
		dev_warn(ddev, "%s endpoint with wBytesPerInterval of %d in "
				"config %d interface %d altsetting %d ep %d: "
				"setting to %d\n",
				usb_endpoint_xfer_isoc(&ep->desc) ? "Isoc" : "Int",
				le16_to_cpu(desc->wBytesPerInterval),
				cfgno, inum, asnum, ep->desc.bEndpointAddress,
				max_tx);
		desc->wBytesPerInterval = cpu_to_le16(max_tx);
	}
valid:
	return retval;
}