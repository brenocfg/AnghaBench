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
struct usb_gadget_driver {int /*<<< orphan*/  (* unbind ) (TYPE_4__*) ;int /*<<< orphan*/ * resume; int /*<<< orphan*/ * suspend; int /*<<< orphan*/ * disconnect; int /*<<< orphan*/ * setup; int /*<<< orphan*/ * bind; } ;
struct TYPE_7__ {int /*<<< orphan*/  ep_list; } ;
struct ci13xxx_ep {TYPE_3__* qh; TYPE_2__ ep; } ;
struct TYPE_6__ {int /*<<< orphan*/ * driver; } ;
struct TYPE_9__ {int /*<<< orphan*/ * ep0; TYPE_1__ dev; int /*<<< orphan*/ * ops; } ;
struct ci13xxx {int /*<<< orphan*/ * qh_pool; int /*<<< orphan*/ * td_pool; int /*<<< orphan*/  lock; struct usb_gadget_driver* driver; TYPE_4__ gadget; struct ci13xxx_ep* ci13xxx_ep; } ;
struct TYPE_8__ {int /*<<< orphan*/  dma; int /*<<< orphan*/ * ptr; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long RX ; 
 unsigned long TX ; 
 int /*<<< orphan*/  _gadget_stop_activity (TYPE_4__*) ; 
 struct ci13xxx* _udc ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_device_state (int /*<<< orphan*/ ) ; 
 unsigned long hw_ep_max ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  trace (char*,struct usb_gadget_driver*) ; 

int usb_gadget_unregister_driver(struct usb_gadget_driver *driver)
{
	struct ci13xxx *udc = _udc;
	unsigned long i, k, flags;

	trace("%p", driver);

	if (driver             == NULL ||
	    driver->bind       == NULL ||
	    driver->unbind     == NULL ||
	    driver->setup      == NULL ||
	    driver->disconnect == NULL ||
	    driver->suspend    == NULL ||
	    driver->resume     == NULL ||
	    driver             != udc->driver)
		return -EINVAL;

	spin_lock_irqsave(udc->lock, flags);

	hw_device_state(0);

	/* unbind gadget */
	if (udc->gadget.ops != NULL) {
		_gadget_stop_activity(&udc->gadget);

		spin_unlock_irqrestore(udc->lock, flags);
		driver->unbind(&udc->gadget);               /* MAY SLEEP */
		spin_lock_irqsave(udc->lock, flags);

		udc->gadget.ops        = NULL;
		udc->gadget.dev.driver = NULL;
	}

	/* free resources */
	for (i = 0; i < hw_ep_max; i++) {
		struct ci13xxx_ep *mEp = &udc->ci13xxx_ep[i];

		if (i == 0)
			udc->gadget.ep0 = NULL;
		else if (!list_empty(&mEp->ep.ep_list))
			list_del_init(&mEp->ep.ep_list);

		for (k = RX; k <= TX; k++)
			if (mEp->qh[k].ptr != NULL)
				dma_pool_free(udc->qh_pool,
					      mEp->qh[k].ptr, mEp->qh[k].dma);
	}

	udc->driver = NULL;

	spin_unlock_irqrestore(udc->lock, flags);

	if (udc->td_pool != NULL) {
		dma_pool_destroy(udc->td_pool);
		udc->td_pool = NULL;
	}
	if (udc->qh_pool != NULL) {
		dma_pool_destroy(udc->qh_pool);
		udc->qh_pool = NULL;
	}

	return 0;
}