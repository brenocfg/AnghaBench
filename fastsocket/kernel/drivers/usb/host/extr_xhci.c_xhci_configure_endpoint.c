#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  union xhci_trb {int dummy; } xhci_trb ;
typedef  int /*<<< orphan*/  u32 ;
struct completion {int dummy; } ;
struct xhci_virt_device {int /*<<< orphan*/  cmd_status; struct completion cmd_completion; int /*<<< orphan*/  cmd_list; struct xhci_container_ctx* in_ctx; } ;
struct xhci_hcd {int quirks; int /*<<< orphan*/  lock; TYPE_5__* cmd_ring; int /*<<< orphan*/  num_active_eps; struct xhci_virt_device** devs; } ;
struct xhci_container_ctx {int /*<<< orphan*/  dma; } ;
struct xhci_command {int /*<<< orphan*/  cmd_list; TYPE_2__* command_trb; int /*<<< orphan*/  status; struct completion* completion; struct xhci_container_ctx* in_ctx; } ;
struct usb_device {size_t slot_id; } ;
struct TYPE_10__ {union xhci_trb* dequeue; TYPE_4__* enq_seg; TYPE_2__* enqueue; } ;
struct TYPE_9__ {TYPE_3__* next; } ;
struct TYPE_8__ {TYPE_2__* trbs; } ;
struct TYPE_6__ {int /*<<< orphan*/  control; } ;
struct TYPE_7__ {TYPE_1__ link; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ETIME ; 
 scalar_t__ TRB_TYPE_LINK_LE32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XHCI_CMD_DEFAULT_TIMEOUT ; 
 int XHCI_EP_LIMIT_QUIRK ; 
 int XHCI_SW_BW_CHECKING ; 
 int /*<<< orphan*/  init_completion (struct completion*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int wait_for_completion_interruptible_timeout (struct completion*,int /*<<< orphan*/ ) ; 
 int xhci_cancel_cmd (struct xhci_hcd*,struct xhci_command*,union xhci_trb*) ; 
 int xhci_configure_endpoint_result (struct xhci_hcd*,struct usb_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*) ; 
 int xhci_evaluate_context_result (struct xhci_hcd*,struct usb_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xhci_finish_resource_reservation (struct xhci_hcd*,struct xhci_container_ctx*) ; 
 int /*<<< orphan*/  xhci_free_host_resources (struct xhci_hcd*,struct xhci_container_ctx*) ; 
 int xhci_queue_configure_endpoint (struct xhci_hcd*,int /*<<< orphan*/ ,size_t,int) ; 
 int xhci_queue_evaluate_context (struct xhci_hcd*,int /*<<< orphan*/ ,size_t,int) ; 
 scalar_t__ xhci_reserve_bandwidth (struct xhci_hcd*,struct xhci_virt_device*,struct xhci_container_ctx*) ; 
 scalar_t__ xhci_reserve_host_resources (struct xhci_hcd*,struct xhci_container_ctx*) ; 
 int /*<<< orphan*/  xhci_ring_cmd_db (struct xhci_hcd*) ; 
 int /*<<< orphan*/  xhci_warn (struct xhci_hcd*,char*,...) ; 

__attribute__((used)) static int xhci_configure_endpoint(struct xhci_hcd *xhci,
		struct usb_device *udev,
		struct xhci_command *command,
		bool ctx_change, bool must_succeed)
{
	int ret;
	int timeleft;
	unsigned long flags;
	struct xhci_container_ctx *in_ctx;
	struct completion *cmd_completion;
	u32 *cmd_status;
	struct xhci_virt_device *virt_dev;
	union xhci_trb *cmd_trb;

	spin_lock_irqsave(&xhci->lock, flags);
	virt_dev = xhci->devs[udev->slot_id];

	if (command)
		in_ctx = command->in_ctx;
	else
		in_ctx = virt_dev->in_ctx;

	if ((xhci->quirks & XHCI_EP_LIMIT_QUIRK) &&
			xhci_reserve_host_resources(xhci, in_ctx)) {
		spin_unlock_irqrestore(&xhci->lock, flags);
		xhci_warn(xhci, "Not enough host resources, "
				"active endpoint contexts = %u\n",
				xhci->num_active_eps);
		return -ENOMEM;
	}
	if ((xhci->quirks & XHCI_SW_BW_CHECKING) &&
			xhci_reserve_bandwidth(xhci, virt_dev, in_ctx)) {
		if ((xhci->quirks & XHCI_EP_LIMIT_QUIRK))
			xhci_free_host_resources(xhci, in_ctx);
		spin_unlock_irqrestore(&xhci->lock, flags);
		xhci_warn(xhci, "Not enough bandwidth\n");
		return -ENOMEM;
	}

	if (command) {
		cmd_completion = command->completion;
		cmd_status = &command->status;
		command->command_trb = xhci->cmd_ring->enqueue;

		/* Enqueue pointer can be left pointing to the link TRB,
		 * we must handle that
		 */
		if (TRB_TYPE_LINK_LE32(command->command_trb->link.control))
			command->command_trb =
				xhci->cmd_ring->enq_seg->next->trbs;

		list_add_tail(&command->cmd_list, &virt_dev->cmd_list);
	} else {
		cmd_completion = &virt_dev->cmd_completion;
		cmd_status = &virt_dev->cmd_status;
	}
	init_completion(cmd_completion);

	cmd_trb = xhci->cmd_ring->dequeue;
	if (!ctx_change)
		ret = xhci_queue_configure_endpoint(xhci, in_ctx->dma,
				udev->slot_id, must_succeed);
	else
		ret = xhci_queue_evaluate_context(xhci, in_ctx->dma,
				udev->slot_id, must_succeed);
	if (ret < 0) {
		if (command)
			list_del(&command->cmd_list);
		if ((xhci->quirks & XHCI_EP_LIMIT_QUIRK))
			xhci_free_host_resources(xhci, in_ctx);
		spin_unlock_irqrestore(&xhci->lock, flags);
		xhci_dbg(xhci, "FIXME allocate a new ring segment\n");
		return -ENOMEM;
	}
	xhci_ring_cmd_db(xhci);
	spin_unlock_irqrestore(&xhci->lock, flags);

	/* Wait for the configure endpoint command to complete */
	timeleft = wait_for_completion_interruptible_timeout(
			cmd_completion,
			XHCI_CMD_DEFAULT_TIMEOUT);
	if (timeleft <= 0) {
		xhci_warn(xhci, "%s while waiting for %s command\n",
				timeleft == 0 ? "Timeout" : "Signal",
				ctx_change == 0 ?
					"configure endpoint" :
					"evaluate context");
		/* cancel the configure endpoint command */
		ret = xhci_cancel_cmd(xhci, command, cmd_trb);
		if (ret < 0)
			return ret;
		return -ETIME;
	}

	if (!ctx_change)
		ret = xhci_configure_endpoint_result(xhci, udev, cmd_status);
	else
		ret = xhci_evaluate_context_result(xhci, udev, cmd_status);

	if ((xhci->quirks & XHCI_EP_LIMIT_QUIRK)) {
		spin_lock_irqsave(&xhci->lock, flags);
		/* If the command failed, remove the reserved resources.
		 * Otherwise, clean up the estimate to include dropped eps.
		 */
		if (ret)
			xhci_free_host_resources(xhci, in_ctx);
		else
			xhci_finish_resource_reservation(xhci, in_ctx);
		spin_unlock_irqrestore(&xhci->lock, flags);
	}
	return ret;
}