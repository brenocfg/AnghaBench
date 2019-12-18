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
struct cardstate {int /*<<< orphan*/  dev; TYPE_1__ hw; } ;
struct bas_cardstate {int /*<<< orphan*/  urb_int_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  BS_SUSPEND ; 
 int /*<<< orphan*/  DEBUG_SUSPEND ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_usb_rcmsg (int) ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  update_basstate (struct bas_cardstate*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cardstate* usb_get_intfdata (struct usb_interface*) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gigaset_resume(struct usb_interface *intf)
{
	struct cardstate *cs = usb_get_intfdata(intf);
	struct bas_cardstate *ucs = cs->hw.bas;
	int rc;

	/* resubmit interrupt URB for spontaneous messages from base */
	rc = usb_submit_urb(ucs->urb_int_in, GFP_KERNEL);
	if (rc) {
		dev_err(cs->dev, "could not resubmit interrupt URB: %s\n",
			get_usb_rcmsg(rc));
		return rc;
	}

	/* clear suspend flag to reallow activity */
	update_basstate(ucs, 0, BS_SUSPEND);

	gig_dbg(DEBUG_SUSPEND, "resume complete");
	return 0;
}