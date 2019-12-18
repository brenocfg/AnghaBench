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
struct usba_udc {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct usba_ep {scalar_t__ is_in; int /*<<< orphan*/  queue; TYPE_1__ ep; scalar_t__ is_isoc; int /*<<< orphan*/  desc; struct usba_udc* udc; } ;
struct usb_ep {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUSY_BANKS ; 
 int /*<<< orphan*/  CLR_STA ; 
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  DBG_ERR ; 
 int /*<<< orphan*/  DBG_GADGET ; 
 int EAGAIN ; 
 int ENODEV ; 
 int ENOTTY ; 
 int /*<<< orphan*/  SET_STA ; 
 int /*<<< orphan*/  STA ; 
 int USBA_BF (int /*<<< orphan*/ ,long) ; 
 int USBA_FORCE_STALL ; 
 int USBA_TOGGLE_CLR ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct usba_ep* to_usba_ep (struct usb_ep*) ; 
 int usba_ep_readl (struct usba_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usba_ep_writel (struct usba_ep*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int usba_ep_set_halt(struct usb_ep *_ep, int value)
{
	struct usba_ep *ep = to_usba_ep(_ep);
	struct usba_udc *udc = ep->udc;
	unsigned long flags;
	int ret = 0;

	DBG(DBG_GADGET, "endpoint %s: %s HALT\n", ep->ep.name,
			value ? "set" : "clear");

	if (!ep->desc) {
		DBG(DBG_ERR, "Attempted to halt uninitialized ep %s\n",
				ep->ep.name);
		return -ENODEV;
	}
	if (ep->is_isoc) {
		DBG(DBG_ERR, "Attempted to halt isochronous ep %s\n",
				ep->ep.name);
		return -ENOTTY;
	}

	spin_lock_irqsave(&udc->lock, flags);

	/*
	 * We can't halt IN endpoints while there are still data to be
	 * transferred
	 */
	if (!list_empty(&ep->queue)
			|| ((value && ep->is_in && (usba_ep_readl(ep, STA)
					& USBA_BF(BUSY_BANKS, -1L))))) {
		ret = -EAGAIN;
	} else {
		if (value)
			usba_ep_writel(ep, SET_STA, USBA_FORCE_STALL);
		else
			usba_ep_writel(ep, CLR_STA,
					USBA_FORCE_STALL | USBA_TOGGLE_CLR);
		usba_ep_readl(ep, STA);
	}

	spin_unlock_irqrestore(&udc->lock, flags);

	return ret;
}