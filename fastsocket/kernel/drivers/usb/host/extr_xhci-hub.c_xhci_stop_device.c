#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct xhci_virt_device {int /*<<< orphan*/  cmd_list; TYPE_2__* eps; } ;
struct xhci_hcd {int /*<<< orphan*/  lock; TYPE_3__* cmd_ring; struct xhci_virt_device** devs; } ;
struct TYPE_9__ {scalar_t__ next; } ;
struct xhci_command {TYPE_4__ cmd_list; int /*<<< orphan*/  completion; int /*<<< orphan*/  command_trb; } ;
struct TYPE_8__ {int /*<<< orphan*/  enqueue; } ;
struct TYPE_7__ {TYPE_1__* ring; } ;
struct TYPE_6__ {scalar_t__ dequeue; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ETIME ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int LAST_EP_INDEX ; 
 scalar_t__ LIST_POISON1 ; 
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 int /*<<< orphan*/  list_add_tail (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (TYPE_4__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int wait_for_completion_interruptible_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xhci_command* xhci_alloc_command (struct xhci_hcd*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*) ; 
 int /*<<< orphan*/  xhci_free_command (struct xhci_hcd*,struct xhci_command*) ; 
 int /*<<< orphan*/  xhci_queue_stop_endpoint (struct xhci_hcd*,int,int,int) ; 
 int /*<<< orphan*/  xhci_ring_cmd_db (struct xhci_hcd*) ; 
 int /*<<< orphan*/  xhci_warn (struct xhci_hcd*,char*,char*) ; 

__attribute__((used)) static int xhci_stop_device(struct xhci_hcd *xhci, int slot_id, int suspend)
{
	struct xhci_virt_device *virt_dev;
	struct xhci_command *cmd;
	unsigned long flags;
	int timeleft;
	int ret;
	int i;

	ret = 0;
	virt_dev = xhci->devs[slot_id];
	cmd = xhci_alloc_command(xhci, false, true, GFP_NOIO);
	if (!cmd) {
		xhci_dbg(xhci, "Couldn't allocate command structure.\n");
		return -ENOMEM;
	}

	spin_lock_irqsave(&xhci->lock, flags);
	for (i = LAST_EP_INDEX; i > 0; i--) {
		if (virt_dev->eps[i].ring && virt_dev->eps[i].ring->dequeue)
			xhci_queue_stop_endpoint(xhci, slot_id, i, suspend);
	}
	cmd->command_trb = xhci->cmd_ring->enqueue;
	list_add_tail(&cmd->cmd_list, &virt_dev->cmd_list);
	xhci_queue_stop_endpoint(xhci, slot_id, 0, suspend);
	xhci_ring_cmd_db(xhci);
	spin_unlock_irqrestore(&xhci->lock, flags);

	/* Wait for last stop endpoint command to finish */
	timeleft = wait_for_completion_interruptible_timeout(
			cmd->completion,
			USB_CTRL_SET_TIMEOUT);
	if (timeleft <= 0) {
		xhci_warn(xhci, "%s while waiting for stop endpoint command\n",
				timeleft == 0 ? "Timeout" : "Signal");
		spin_lock_irqsave(&xhci->lock, flags);
		/* The timeout might have raced with the event ring handler, so
		 * only delete from the list if the item isn't poisoned.
		 */
		if (cmd->cmd_list.next != LIST_POISON1)
			list_del(&cmd->cmd_list);
		spin_unlock_irqrestore(&xhci->lock, flags);
		ret = -ETIME;
		goto command_cleanup;
	}

command_cleanup:
	xhci_free_command(xhci, cmd);
	return ret;
}