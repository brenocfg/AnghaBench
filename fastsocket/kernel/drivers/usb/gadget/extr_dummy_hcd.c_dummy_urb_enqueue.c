#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct usb_hcd {int dummy; } ;
struct urbp {int /*<<< orphan*/  urbp_list; struct urb* urb; } ;
struct urb {scalar_t__ dev; int error_count; int /*<<< orphan*/  pipe; struct urbp* hcpriv; scalar_t__ transfer_buffer_length; int /*<<< orphan*/  transfer_buffer; } ;
struct dummy {scalar_t__ udev; int /*<<< orphan*/  lock; int /*<<< orphan*/  timer; int /*<<< orphan*/  urbp_list; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ PIPE_CONTROL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dummy_dev (struct dummy*) ; 
 struct dummy* hcd_to_dummy (struct usb_hcd*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree (struct urbp*) ; 
 struct urbp* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usb_get_dev (scalar_t__) ; 
 int usb_hcd_link_urb_to_ep (struct usb_hcd*,struct urb*) ; 
 scalar_t__ usb_pipetype (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dummy_urb_enqueue (
	struct usb_hcd			*hcd,
	struct urb			*urb,
	gfp_t				mem_flags
) {
	struct dummy	*dum;
	struct urbp	*urbp;
	unsigned long	flags;
	int		rc;

	if (!urb->transfer_buffer && urb->transfer_buffer_length)
		return -EINVAL;

	urbp = kmalloc (sizeof *urbp, mem_flags);
	if (!urbp)
		return -ENOMEM;
	urbp->urb = urb;

	dum = hcd_to_dummy (hcd);
	spin_lock_irqsave (&dum->lock, flags);
	rc = usb_hcd_link_urb_to_ep(hcd, urb);
	if (rc) {
		kfree(urbp);
		goto done;
	}

	if (!dum->udev) {
		dum->udev = urb->dev;
		usb_get_dev (dum->udev);
	} else if (unlikely (dum->udev != urb->dev))
		dev_err (dummy_dev(dum), "usb_device address has changed!\n");

	list_add_tail (&urbp->urbp_list, &dum->urbp_list);
	urb->hcpriv = urbp;
	if (usb_pipetype (urb->pipe) == PIPE_CONTROL)
		urb->error_count = 1;		/* mark as a new urb */

	/* kick the scheduler, it'll do the rest */
	if (!timer_pending (&dum->timer))
		mod_timer (&dum->timer, jiffies + 1);

 done:
	spin_unlock_irqrestore(&dum->lock, flags);
	return rc;
}