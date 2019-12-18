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
struct usb_ep {int /*<<< orphan*/  name; } ;
struct dummy_ep {int /*<<< orphan*/ * desc; } ;
struct dummy {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ep0name ; 
 struct dummy* ep_to_dummy (struct dummy_ep*) ; 
 int /*<<< orphan*/  nuke (struct dummy*,struct dummy_ep*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udc_dev (struct dummy*) ; 
 struct dummy_ep* usb_ep_to_dummy_ep (struct usb_ep*) ; 

__attribute__((used)) static int dummy_disable (struct usb_ep *_ep)
{
	struct dummy_ep		*ep;
	struct dummy		*dum;
	unsigned long		flags;
	int			retval;

	ep = usb_ep_to_dummy_ep (_ep);
	if (!_ep || !ep->desc || _ep->name == ep0name)
		return -EINVAL;
	dum = ep_to_dummy (ep);

	spin_lock_irqsave (&dum->lock, flags);
	ep->desc = NULL;
	retval = 0;
	nuke (dum, ep);
	spin_unlock_irqrestore (&dum->lock, flags);

	dev_dbg (udc_dev(dum), "disabled %s\n", _ep->name);
	return retval;
}