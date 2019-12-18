#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct st5481_intr {TYPE_1__* urb; } ;
struct st5481_ctrl {TYPE_1__* urb; } ;
struct st5481_adapter {struct st5481_ctrl ctrl; struct st5481_intr intr; } ;
struct TYPE_3__ {int /*<<< orphan*/  transfer_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_kill_urb (TYPE_1__*) ; 

void st5481_release_usb(struct st5481_adapter *adapter)
{
	struct st5481_intr *intr = &adapter->intr;
	struct st5481_ctrl *ctrl = &adapter->ctrl;

	DBG(1,"");

	// Stop and free Control and Interrupt URBs
	usb_kill_urb(ctrl->urb);
	kfree(ctrl->urb->transfer_buffer);
	usb_free_urb(ctrl->urb);
	ctrl->urb = NULL;

	usb_kill_urb(intr->urb);
	kfree(intr->urb->transfer_buffer);
	usb_free_urb(intr->urb);
	intr->urb = NULL;
}