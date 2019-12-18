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
struct usb_interface {int dummy; } ;
struct TYPE_2__ {struct bas_cardstate* bas; } ;
struct cardstate {int /*<<< orphan*/  bcs; int /*<<< orphan*/  dev; TYPE_1__ hw; } ;
struct bas_cardstate {int basstate; int /*<<< orphan*/  timer_ctrl; int /*<<< orphan*/  urb_int_in; int /*<<< orphan*/  urb_ctrl; int /*<<< orphan*/  pending; int /*<<< orphan*/  waitqueue; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int BAS_TIMEOUT ; 
 int BS_ATOPEN ; 
 int BS_ATRDPEND ; 
 int BS_ATWRPEND ; 
 int BS_B1OPEN ; 
 int BS_B2OPEN ; 
 int BS_SUSPEND ; 
 int /*<<< orphan*/  DEBUG_SUSPEND ; 
 int EBUSY ; 
 int /*<<< orphan*/  HD_CLOSE_ATCHANNEL ; 
 int HZ ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int req_submit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int update_basstate (struct bas_cardstate*,int,int) ; 
 struct cardstate* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int gigaset_suspend(struct usb_interface *intf, pm_message_t message)
{
	struct cardstate *cs = usb_get_intfdata(intf);
	struct bas_cardstate *ucs = cs->hw.bas;
	int rc;

	/* set suspend flag; this stops AT command/response traffic */
	if (update_basstate(ucs, BS_SUSPEND, 0) & BS_SUSPEND) {
		gig_dbg(DEBUG_SUSPEND, "already suspended");
		return 0;
	}

	/* wait a bit for blocking conditions to go away */
	rc = wait_event_timeout(ucs->waitqueue,
			!(ucs->basstate &
			  (BS_B1OPEN|BS_B2OPEN|BS_ATRDPEND|BS_ATWRPEND)),
			BAS_TIMEOUT*HZ/10);
	gig_dbg(DEBUG_SUSPEND, "wait_event_timeout() -> %d", rc);

	/* check for conditions preventing suspend */
	if (ucs->basstate & (BS_B1OPEN|BS_B2OPEN|BS_ATRDPEND|BS_ATWRPEND)) {
		dev_warn(cs->dev, "cannot suspend:\n");
		if (ucs->basstate & BS_B1OPEN)
			dev_warn(cs->dev, " B channel 1 open\n");
		if (ucs->basstate & BS_B2OPEN)
			dev_warn(cs->dev, " B channel 2 open\n");
		if (ucs->basstate & BS_ATRDPEND)
			dev_warn(cs->dev, " receiving AT reply\n");
		if (ucs->basstate & BS_ATWRPEND)
			dev_warn(cs->dev, " sending AT command\n");
		update_basstate(ucs, 0, BS_SUSPEND);
		return -EBUSY;
	}

	/* close AT channel if open */
	if (ucs->basstate & BS_ATOPEN) {
		gig_dbg(DEBUG_SUSPEND, "closing AT channel");
		rc = req_submit(cs->bcs, HD_CLOSE_ATCHANNEL, 0, 0);
		if (rc) {
			update_basstate(ucs, 0, BS_SUSPEND);
			return rc;
		}
		wait_event_timeout(ucs->waitqueue, !ucs->pending,
				   BAS_TIMEOUT*HZ/10);
		/* in case of timeout, proceed anyway */
	}

	/* kill all URBs and timers that might still be pending */
	usb_kill_urb(ucs->urb_ctrl);
	usb_kill_urb(ucs->urb_int_in);
	del_timer_sync(&ucs->timer_ctrl);

	gig_dbg(DEBUG_SUSPEND, "suspend complete");
	return 0;
}