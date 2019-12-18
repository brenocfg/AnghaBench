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
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  alloc586 (struct net_device*) ; 
 int /*<<< orphan*/  init586 (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  startrecv586 (struct net_device*) ; 
 int /*<<< orphan*/  sun3_82586_interrupt ; 
 int /*<<< orphan*/  sun3_disint () ; 
 int /*<<< orphan*/  sun3_enaint () ; 
 int /*<<< orphan*/  sun3_reset586 () ; 

__attribute__((used)) static int sun3_82586_open(struct net_device *dev)
{
	int ret;

	sun3_disint();
	alloc586(dev);
	init586(dev);
	startrecv586(dev);
	sun3_enaint();

	ret = request_irq(dev->irq, &sun3_82586_interrupt,0,dev->name,dev);
	if (ret)
	{
		sun3_reset586();
		return ret;
	}

	netif_start_queue(dev);

	return 0; /* most done by init */
}