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
typedef  scalar_t__ u32 ;
struct xhci_virt_device {TYPE_1__* eps; int /*<<< orphan*/  out_ctx; } ;
struct xhci_hcd {int /*<<< orphan*/  lock; struct xhci_virt_device** devs; } ;
struct xhci_ep_ctx {int dummy; } ;
struct xhci_command {int /*<<< orphan*/  in_ctx; } ;
struct usb_host_endpoint {int /*<<< orphan*/  desc; } ;
struct usb_hcd {int dummy; } ;
struct usb_device {size_t slot_id; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_4__ {struct xhci_command* free_streams_command; } ;
struct TYPE_3__ {int /*<<< orphan*/  ep_state; TYPE_2__* stream_info; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  EP_GETTING_NO_STREAMS ; 
 int /*<<< orphan*/  EP_HAS_STREAMS ; 
 struct xhci_hcd* hcd_to_xhci (struct usb_hcd*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ xhci_calculate_no_streams_bitmask (struct xhci_hcd*,struct usb_device*,struct usb_host_endpoint**,unsigned int) ; 
 int xhci_configure_endpoint (struct xhci_hcd*,struct usb_device*,struct xhci_command*,int,int) ; 
 int /*<<< orphan*/  xhci_endpoint_copy (struct xhci_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  xhci_free_stream_info (struct xhci_hcd*,TYPE_2__*) ; 
 unsigned int xhci_get_endpoint_index (int /*<<< orphan*/ *) ; 
 struct xhci_ep_ctx* xhci_get_ep_ctx (struct xhci_hcd*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  xhci_setup_input_ctx_for_config_ep (struct xhci_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  xhci_setup_no_streams_ep_input_ctx (struct xhci_hcd*,struct xhci_ep_ctx*,TYPE_1__*) ; 

int xhci_free_streams(struct usb_hcd *hcd, struct usb_device *udev,
		struct usb_host_endpoint **eps, unsigned int num_eps,
		gfp_t mem_flags)
{
	int i, ret;
	struct xhci_hcd *xhci;
	struct xhci_virt_device *vdev;
	struct xhci_command *command;
	unsigned int ep_index;
	unsigned long flags;
	u32 changed_ep_bitmask;

	xhci = hcd_to_xhci(hcd);
	vdev = xhci->devs[udev->slot_id];

	/* Set up a configure endpoint command to remove the streams rings */
	spin_lock_irqsave(&xhci->lock, flags);
	changed_ep_bitmask = xhci_calculate_no_streams_bitmask(xhci,
			udev, eps, num_eps);
	if (changed_ep_bitmask == 0) {
		spin_unlock_irqrestore(&xhci->lock, flags);
		return -EINVAL;
	}

	/* Use the xhci_command structure from the first endpoint.  We may have
	 * allocated too many, but the driver may call xhci_free_streams() for
	 * each endpoint it grouped into one call to xhci_alloc_streams().
	 */
	ep_index = xhci_get_endpoint_index(&eps[0]->desc);
	command = vdev->eps[ep_index].stream_info->free_streams_command;
	for (i = 0; i < num_eps; i++) {
		struct xhci_ep_ctx *ep_ctx;

		ep_index = xhci_get_endpoint_index(&eps[i]->desc);
		ep_ctx = xhci_get_ep_ctx(xhci, command->in_ctx, ep_index);
		xhci->devs[udev->slot_id]->eps[ep_index].ep_state |=
			EP_GETTING_NO_STREAMS;

		xhci_endpoint_copy(xhci, command->in_ctx,
				vdev->out_ctx, ep_index);
		xhci_setup_no_streams_ep_input_ctx(xhci, ep_ctx,
				&vdev->eps[ep_index]);
	}
	xhci_setup_input_ctx_for_config_ep(xhci, command->in_ctx,
			vdev->out_ctx, changed_ep_bitmask, changed_ep_bitmask);
	spin_unlock_irqrestore(&xhci->lock, flags);

	/* Issue and wait for the configure endpoint command,
	 * which must succeed.
	 */
	ret = xhci_configure_endpoint(xhci, udev, command,
			false, true);

	/* xHC rejected the configure endpoint command for some reason, so we
	 * leave the streams rings intact.
	 */
	if (ret < 0)
		return ret;

	spin_lock_irqsave(&xhci->lock, flags);
	for (i = 0; i < num_eps; i++) {
		ep_index = xhci_get_endpoint_index(&eps[i]->desc);
		xhci_free_stream_info(xhci, vdev->eps[ep_index].stream_info);
		vdev->eps[ep_index].stream_info = NULL;
		/* FIXME Unset maxPstreams in endpoint context and
		 * update deq ptr to point to normal string ring.
		 */
		vdev->eps[ep_index].ep_state &= ~EP_GETTING_NO_STREAMS;
		vdev->eps[ep_index].ep_state &= ~EP_HAS_STREAMS;
	}
	spin_unlock_irqrestore(&xhci->lock, flags);

	return 0;
}