#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * bus; } ;
struct usb_gadget_driver {int (* bind ) (TYPE_4__*) ;TYPE_2__ driver; int /*<<< orphan*/ * resume; int /*<<< orphan*/ * suspend; int /*<<< orphan*/ * disconnect; int /*<<< orphan*/ * setup; int /*<<< orphan*/ * unbind; } ;
struct ci13xxx_td {int dummy; } ;
struct ci13xxx_qh {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  ep_list; int /*<<< orphan*/  maxpacket; int /*<<< orphan*/ * ops; int /*<<< orphan*/  name; } ;
struct ci13xxx_ep {TYPE_3__* qh; TYPE_1__ ep; int /*<<< orphan*/  name; int /*<<< orphan*/ * td_pool; TYPE_5__* device; int /*<<< orphan*/  lock; } ;
struct TYPE_10__ {TYPE_2__* driver; } ;
struct TYPE_9__ {TYPE_5__ dev; int /*<<< orphan*/ * ops; int /*<<< orphan*/  ep_list; TYPE_1__* ep0; } ;
struct ci13xxx {int /*<<< orphan*/  lock; struct ci13xxx_ep* ci13xxx_ep; TYPE_4__ gadget; int /*<<< orphan*/ * qh_pool; int /*<<< orphan*/ * td_pool; struct usb_gadget_driver* driver; } ;
struct TYPE_8__ {int /*<<< orphan*/  dma; int /*<<< orphan*/ * ptr; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_PAYLOAD_MAX ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 size_t RX ; 
 unsigned long TX ; 
 struct ci13xxx* _udc ; 
 int /*<<< orphan*/ * dma_pool_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* dma_pool_create (char*,TYPE_5__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ *) ; 
 int hw_device_state (int /*<<< orphan*/ ) ; 
 unsigned long hw_ep_max ; 
 int /*<<< orphan*/  info (char*,unsigned long) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scnprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  trace (char*,struct usb_gadget_driver*) ; 
 int /*<<< orphan*/  usb_ep_ops ; 
 int /*<<< orphan*/  usb_gadget_ops ; 
 int /*<<< orphan*/  usb_gadget_unregister_driver (struct usb_gadget_driver*) ; 

int usb_gadget_register_driver(struct usb_gadget_driver *driver)
{
	struct ci13xxx *udc = _udc;
	unsigned long i, k, flags;
	int retval = -ENOMEM;

	trace("%p", driver);

	if (driver             == NULL ||
	    driver->bind       == NULL ||
	    driver->unbind     == NULL ||
	    driver->setup      == NULL ||
	    driver->disconnect == NULL ||
	    driver->suspend    == NULL ||
	    driver->resume     == NULL)
		return -EINVAL;
	else if (udc         == NULL)
		return -ENODEV;
	else if (udc->driver != NULL)
		return -EBUSY;

	/* alloc resources */
	udc->qh_pool = dma_pool_create("ci13xxx_qh", &udc->gadget.dev,
				       sizeof(struct ci13xxx_qh),
				       64, PAGE_SIZE);
	if (udc->qh_pool == NULL)
		return -ENOMEM;

	udc->td_pool = dma_pool_create("ci13xxx_td", &udc->gadget.dev,
				       sizeof(struct ci13xxx_td),
				       64, PAGE_SIZE);
	if (udc->td_pool == NULL) {
		dma_pool_destroy(udc->qh_pool);
		udc->qh_pool = NULL;
		return -ENOMEM;
	}

	spin_lock_irqsave(udc->lock, flags);

	info("hw_ep_max = %d", hw_ep_max);

	udc->driver = driver;
	udc->gadget.ops        = NULL;
	udc->gadget.dev.driver = NULL;

	retval = 0;
	for (i = 0; i < hw_ep_max; i++) {
		struct ci13xxx_ep *mEp = &udc->ci13xxx_ep[i];

		scnprintf(mEp->name, sizeof(mEp->name), "ep%i", (int)i);

		mEp->lock         = udc->lock;
		mEp->device       = &udc->gadget.dev;
		mEp->td_pool      = udc->td_pool;

		mEp->ep.name      = mEp->name;
		mEp->ep.ops       = &usb_ep_ops;
		mEp->ep.maxpacket = CTRL_PAYLOAD_MAX;

		/* this allocation cannot be random */
		for (k = RX; k <= TX; k++) {
			INIT_LIST_HEAD(&mEp->qh[k].queue);
			mEp->qh[k].ptr = dma_pool_alloc(udc->qh_pool,
							GFP_KERNEL,
							&mEp->qh[k].dma);
			if (mEp->qh[k].ptr == NULL)
				retval = -ENOMEM;
			else
				memset(mEp->qh[k].ptr, 0,
				       sizeof(*mEp->qh[k].ptr));
		}
		if (i == 0)
			udc->gadget.ep0 = &mEp->ep;
		else
			list_add_tail(&mEp->ep.ep_list, &udc->gadget.ep_list);
	}
	if (retval)
		goto done;

	/* bind gadget */
	driver->driver.bus     = NULL;
	udc->gadget.ops        = &usb_gadget_ops;
	udc->gadget.dev.driver = &driver->driver;

	spin_unlock_irqrestore(udc->lock, flags);
	retval = driver->bind(&udc->gadget);                /* MAY SLEEP */
	spin_lock_irqsave(udc->lock, flags);

	if (retval) {
		udc->gadget.ops        = NULL;
		udc->gadget.dev.driver = NULL;
		goto done;
	}

	retval = hw_device_state(udc->ci13xxx_ep[0].qh[RX].dma);

 done:
	spin_unlock_irqrestore(udc->lock, flags);
	if (retval)
		usb_gadget_unregister_driver(driver);
	return retval;
}