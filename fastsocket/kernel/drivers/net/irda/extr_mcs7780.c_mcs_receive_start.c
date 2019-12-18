#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  state; int /*<<< orphan*/  in_frame; } ;
struct mcs_cb {TYPE_2__* rx_urb; int /*<<< orphan*/  in_buf; int /*<<< orphan*/  ep_in; int /*<<< orphan*/  usbdev; TYPE_1__ rx_buff; } ;
struct TYPE_5__ {scalar_t__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OUTSIDE_FRAME ; 
 int /*<<< orphan*/  mcs_receive_irq ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct mcs_cb*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int mcs_receive_start(struct mcs_cb *mcs)
{
	mcs->rx_buff.in_frame = FALSE;
	mcs->rx_buff.state = OUTSIDE_FRAME;

	usb_fill_bulk_urb(mcs->rx_urb, mcs->usbdev,
			  usb_rcvbulkpipe(mcs->usbdev, mcs->ep_in),
			  mcs->in_buf, 4096, mcs_receive_irq, mcs);

	mcs->rx_urb->status = 0;
	return usb_submit_urb(mcs->rx_urb, GFP_KERNEL);
}