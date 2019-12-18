#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xhci_virt_device {TYPE_1__* eps; } ;
struct xhci_input_control_ctx {int dummy; } ;
struct xhci_hcd {int dummy; } ;
struct xhci_ep_ctx {int /*<<< orphan*/  tx_info; int /*<<< orphan*/  ep_info2; int /*<<< orphan*/  ep_info; } ;
struct xhci_container_ctx {int dummy; } ;
struct xhci_bw_info {unsigned int type; int /*<<< orphan*/  max_esit_payload; int /*<<< orphan*/  max_packet_size; scalar_t__ num_packets; scalar_t__ mult; int /*<<< orphan*/  ep_interval; } ;
struct TYPE_2__ {struct xhci_bw_info bw_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTX_TO_EP_INTERVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ CTX_TO_EP_MULT (int /*<<< orphan*/ ) ; 
 unsigned int CTX_TO_EP_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ CTX_TO_MAX_BURST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTX_TO_MAX_ESIT_PAYLOAD (int /*<<< orphan*/ ) ; 
 scalar_t__ EP_IS_ADDED (struct xhci_input_control_ctx*,int) ; 
 scalar_t__ EP_IS_DROPPED (struct xhci_input_control_ctx*,int) ; 
 unsigned int INT_IN_EP ; 
 unsigned int INT_OUT_EP ; 
 unsigned int ISOC_IN_EP ; 
 unsigned int ISOC_OUT_EP ; 
 int /*<<< orphan*/  MAX_PACKET_DECODED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_clear_endpoint_bw_info (struct xhci_bw_info*) ; 
 struct xhci_ep_ctx* xhci_get_ep_ctx (struct xhci_hcd*,struct xhci_container_ctx*,int) ; 

void xhci_update_bw_info(struct xhci_hcd *xhci,
		struct xhci_container_ctx *in_ctx,
		struct xhci_input_control_ctx *ctrl_ctx,
		struct xhci_virt_device *virt_dev)
{
	struct xhci_bw_info *bw_info;
	struct xhci_ep_ctx *ep_ctx;
	unsigned int ep_type;
	int i;

	for (i = 1; i < 31; ++i) {
		bw_info = &virt_dev->eps[i].bw_info;

		/* We can't tell what endpoint type is being dropped, but
		 * unconditionally clearing the bandwidth info for non-periodic
		 * endpoints should be harmless because the info will never be
		 * set in the first place.
		 */
		if (!EP_IS_ADDED(ctrl_ctx, i) && EP_IS_DROPPED(ctrl_ctx, i)) {
			/* Dropped endpoint */
			xhci_clear_endpoint_bw_info(bw_info);
			continue;
		}

		if (EP_IS_ADDED(ctrl_ctx, i)) {
			ep_ctx = xhci_get_ep_ctx(xhci, in_ctx, i);
			ep_type = CTX_TO_EP_TYPE(le32_to_cpu(ep_ctx->ep_info2));

			/* Ignore non-periodic endpoints */
			if (ep_type != ISOC_OUT_EP && ep_type != INT_OUT_EP &&
					ep_type != ISOC_IN_EP &&
					ep_type != INT_IN_EP)
				continue;

			/* Added or changed endpoint */
			bw_info->ep_interval = CTX_TO_EP_INTERVAL(
					le32_to_cpu(ep_ctx->ep_info));
			/* Number of packets and mult are zero-based in the
			 * input context, but we want one-based for the
			 * interval table.
			 */
			bw_info->mult = CTX_TO_EP_MULT(
					le32_to_cpu(ep_ctx->ep_info)) + 1;
			bw_info->num_packets = CTX_TO_MAX_BURST(
					le32_to_cpu(ep_ctx->ep_info2)) + 1;
			bw_info->max_packet_size = MAX_PACKET_DECODED(
					le32_to_cpu(ep_ctx->ep_info2));
			bw_info->type = ep_type;
			bw_info->max_esit_payload = CTX_TO_MAX_ESIT_PAYLOAD(
					le32_to_cpu(ep_ctx->tx_info));
		}
	}
}