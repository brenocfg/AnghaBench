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
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct usb_device {int dummy; } ;
struct TYPE_8__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct TYPE_6__ {int /*<<< orphan*/  reapable; int /*<<< orphan*/  completing; int /*<<< orphan*/  active; int /*<<< orphan*/  pending; int /*<<< orphan*/  lock; } ;
struct TYPE_7__ {TYPE_4__ commsqual_timer; int /*<<< orphan*/  commsqual_bh; int /*<<< orphan*/  state; int /*<<< orphan*/  link_status; int /*<<< orphan*/  ctlx_urb; int /*<<< orphan*/  tx_urb; int /*<<< orphan*/  rx_urb; TYPE_4__ reqtimer; TYPE_4__ resptimer; TYPE_4__ throttle; int /*<<< orphan*/  usb_work; int /*<<< orphan*/  link_bh; int /*<<< orphan*/  completion_bh; int /*<<< orphan*/  reaper_bh; int /*<<< orphan*/  authq; TYPE_1__ ctlxq; int /*<<< orphan*/  cmdq; int /*<<< orphan*/  endp_out; int /*<<< orphan*/  endp_in; struct usb_device* usb; } ;
typedef  TYPE_2__ hfa384x_t ;

/* Variables and functions */
 int /*<<< orphan*/  HFA384x_LINK_NOTCONNECTED ; 
 int /*<<< orphan*/  HFA384x_STATE_INIT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfa384x_usb_defer ; 
 int /*<<< orphan*/  hfa384x_usb_throttlefn ; 
 int /*<<< orphan*/  hfa384x_usbctlx_completion_task ; 
 int /*<<< orphan*/  hfa384x_usbctlx_reaper_task ; 
 int /*<<< orphan*/  hfa384x_usbctlx_reqtimerfn ; 
 int /*<<< orphan*/  hfa384x_usbctlx_resptimerfn ; 
 int /*<<< orphan*/  init_timer (TYPE_4__*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  prism2sta_commsqual_defer ; 
 int /*<<< orphan*/  prism2sta_commsqual_timer ; 
 int /*<<< orphan*/  prism2sta_processing_defer ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  usb_init_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (struct usb_device*,int) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (struct usb_device*,int) ; 

void hfa384x_create(hfa384x_t *hw, struct usb_device *usb)
{
	memset(hw, 0, sizeof(hfa384x_t));
	hw->usb = usb;

	/* set up the endpoints */
	hw->endp_in = usb_rcvbulkpipe(usb, 1);
	hw->endp_out = usb_sndbulkpipe(usb, 2);

	/* Set up the waitq */
	init_waitqueue_head(&hw->cmdq);

	/* Initialize the command queue */
	spin_lock_init(&hw->ctlxq.lock);
	INIT_LIST_HEAD(&hw->ctlxq.pending);
	INIT_LIST_HEAD(&hw->ctlxq.active);
	INIT_LIST_HEAD(&hw->ctlxq.completing);
	INIT_LIST_HEAD(&hw->ctlxq.reapable);

	/* Initialize the authentication queue */
	skb_queue_head_init(&hw->authq);

	tasklet_init(&hw->reaper_bh,
		     hfa384x_usbctlx_reaper_task, (unsigned long)hw);
	tasklet_init(&hw->completion_bh,
		     hfa384x_usbctlx_completion_task, (unsigned long)hw);
	INIT_WORK(&hw->link_bh, prism2sta_processing_defer);
	INIT_WORK(&hw->usb_work, hfa384x_usb_defer);

	init_timer(&hw->throttle);
	hw->throttle.function = hfa384x_usb_throttlefn;
	hw->throttle.data = (unsigned long)hw;

	init_timer(&hw->resptimer);
	hw->resptimer.function = hfa384x_usbctlx_resptimerfn;
	hw->resptimer.data = (unsigned long)hw;

	init_timer(&hw->reqtimer);
	hw->reqtimer.function = hfa384x_usbctlx_reqtimerfn;
	hw->reqtimer.data = (unsigned long)hw;

	usb_init_urb(&hw->rx_urb);
	usb_init_urb(&hw->tx_urb);
	usb_init_urb(&hw->ctlx_urb);

	hw->link_status = HFA384x_LINK_NOTCONNECTED;
	hw->state = HFA384x_STATE_INIT;

	INIT_WORK(&hw->commsqual_bh, prism2sta_commsqual_defer);
	init_timer(&hw->commsqual_timer);
	hw->commsqual_timer.data = (unsigned long)hw;
	hw->commsqual_timer.function = prism2sta_commsqual_timer;
}