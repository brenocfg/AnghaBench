#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int maxpacket; int /*<<< orphan*/  ep_list; int /*<<< orphan*/  name; } ;
struct net2280_ep {int num; int fifo_size; scalar_t__ stopped; TYPE_1__ ep; int /*<<< orphan*/ * regs; int /*<<< orphan*/ * dma; struct net2280* dev; } ;
struct TYPE_5__ {TYPE_1__* ep0; } ;
struct net2280 {TYPE_3__* dep; TYPE_2__ gadget; struct net2280_ep* ep; int /*<<< orphan*/  regs; int /*<<< orphan*/ * epregs; int /*<<< orphan*/ * dma; } ;
struct TYPE_6__ {int /*<<< orphan*/  dep_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP_DONTUSE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ep_name ; 
 int /*<<< orphan*/  ep_reset (int /*<<< orphan*/ ,struct net2280_ep*) ; 
 int use_dma ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usb_reinit (struct net2280 *dev)
{
	u32	tmp;
	int	init_dma;

	/* use_dma changes are ignored till next device re-init */
	init_dma = use_dma;

	/* basic endpoint init */
	for (tmp = 0; tmp < 7; tmp++) {
		struct net2280_ep	*ep = &dev->ep [tmp];

		ep->ep.name = ep_name [tmp];
		ep->dev = dev;
		ep->num = tmp;

		if (tmp > 0 && tmp <= 4) {
			ep->fifo_size = 1024;
			if (init_dma)
				ep->dma = &dev->dma [tmp - 1];
		} else
			ep->fifo_size = 64;
		ep->regs = &dev->epregs [tmp];
		ep_reset (dev->regs, ep);
	}
	dev->ep [0].ep.maxpacket = 64;
	dev->ep [5].ep.maxpacket = 64;
	dev->ep [6].ep.maxpacket = 64;

	dev->gadget.ep0 = &dev->ep [0].ep;
	dev->ep [0].stopped = 0;
	INIT_LIST_HEAD (&dev->gadget.ep0->ep_list);

	/* we want to prevent lowlevel/insecure access from the USB host,
	 * but erratum 0119 means this enable bit is ignored
	 */
	for (tmp = 0; tmp < 5; tmp++)
		writel (EP_DONTUSE, &dev->dep [tmp].dep_cfg);
}