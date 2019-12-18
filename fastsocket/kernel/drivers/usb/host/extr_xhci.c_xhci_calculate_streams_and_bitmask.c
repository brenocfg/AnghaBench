#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct xhci_hcd {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  bmAttributes; } ;
struct usb_host_ss_ep_comp {TYPE_1__ desc; } ;
struct TYPE_4__ {int /*<<< orphan*/  bEndpointAddress; } ;
struct usb_host_endpoint {TYPE_2__ desc; struct usb_host_ss_ep_comp* ss_ep_comp; } ;
struct usb_device {int /*<<< orphan*/  slot_id; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int USB_SS_MAX_STREAMS (int /*<<< orphan*/ ) ; 
 int xhci_check_streams_endpoint (struct xhci_hcd*,struct usb_device*,struct usb_host_endpoint*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int xhci_get_endpoint_flag (TYPE_2__*) ; 

__attribute__((used)) static int xhci_calculate_streams_and_bitmask(struct xhci_hcd *xhci,
		struct usb_device *udev,
		struct usb_host_endpoint **eps, unsigned int num_eps,
		unsigned int *num_streams, u32 *changed_ep_bitmask)
{
	struct usb_host_ss_ep_comp *ss_ep_comp;
	unsigned int max_streams;
	unsigned int endpoint_flag;
	int i;
	int ret;

	for (i = 0; i < num_eps; i++) {
		ret = xhci_check_streams_endpoint(xhci, udev,
				eps[i], udev->slot_id);
		if (ret < 0)
			return ret;

		ss_ep_comp = eps[i]->ss_ep_comp;
		max_streams = USB_SS_MAX_STREAMS(ss_ep_comp->desc.bmAttributes);
		if (max_streams < (*num_streams - 1)) {
			xhci_dbg(xhci, "Ep 0x%x only supports %u stream IDs.\n",
					eps[i]->desc.bEndpointAddress,
					max_streams);
			*num_streams = max_streams+1;
		}

		endpoint_flag = xhci_get_endpoint_flag(&eps[i]->desc);
		if (*changed_ep_bitmask & endpoint_flag)
			return -EINVAL;
		*changed_ep_bitmask |= endpoint_flag;
	}
	return 0;
}