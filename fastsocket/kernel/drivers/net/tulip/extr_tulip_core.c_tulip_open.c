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
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  tulip_free_ring (struct net_device*) ; 
 int /*<<< orphan*/  tulip_init_ring (struct net_device*) ; 
 int /*<<< orphan*/  tulip_interrupt ; 
 int /*<<< orphan*/  tulip_up (struct net_device*) ; 

__attribute__((used)) static int
tulip_open(struct net_device *dev)
{
	int retval;

	tulip_init_ring (dev);

	retval = request_irq(dev->irq, &tulip_interrupt, IRQF_SHARED, dev->name, dev);
	if (retval)
		goto free_ring;

	tulip_up (dev);

	netif_start_queue (dev);

	return 0;

free_ring:
	tulip_free_ring (dev);
	return retval;
}