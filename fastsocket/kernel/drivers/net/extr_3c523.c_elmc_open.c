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
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int IRQF_SAMPLE_RANDOM ; 
 int IRQF_SHARED ; 
 int /*<<< orphan*/  alloc586 (struct net_device*) ; 
 int /*<<< orphan*/  elmc_id_attn586 () ; 
 int /*<<< orphan*/  elmc_id_reset586 () ; 
 int /*<<< orphan*/  elmc_interrupt ; 
 int /*<<< orphan*/  init586 (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  startrecv586 (struct net_device*) ; 

__attribute__((used)) static int elmc_open(struct net_device *dev)
{
	int ret;

	elmc_id_attn586();	/* disable interrupts */

	ret = request_irq(dev->irq, &elmc_interrupt, IRQF_SHARED | IRQF_SAMPLE_RANDOM,
			  dev->name, dev);
	if (ret) {
		pr_err("%s: couldn't get irq %d\n", dev->name, dev->irq);
		elmc_id_reset586();
		return ret;
	}
	alloc586(dev);
	init586(dev);
	startrecv586(dev);
	netif_start_queue(dev);
	return 0;		/* most done by init */
}