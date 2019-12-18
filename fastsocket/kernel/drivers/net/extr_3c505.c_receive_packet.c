#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  dma; } ;
struct TYPE_4__ {int length; int /*<<< orphan*/  start_time; struct sk_buff* skb; scalar_t__ direction; int /*<<< orphan*/ * target; } ;
struct TYPE_5__ {int hcr_val; int /*<<< orphan*/  busy; scalar_t__ rx_active; TYPE_1__ current_dma; int /*<<< orphan*/  dmaing; void* dma_buffer; } ;
typedef  TYPE_2__ elp_device ;

/* Variables and functions */
 int DIR ; 
 int DMAE ; 
 unsigned long MAX_DMA_ADDRESS ; 
 int TCEN ; 
 unsigned long claim_dma_lock () ; 
 int /*<<< orphan*/  clear_dma_ff (int /*<<< orphan*/ ) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  disable_dma (int /*<<< orphan*/ ) ; 
 int elp_debug ; 
 int /*<<< orphan*/  enable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isa_virt_to_bus (void*) ; 
 int /*<<< orphan*/  jiffies ; 
 TYPE_2__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outb_control (int,struct net_device*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 int /*<<< orphan*/  set_dma_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dma_count (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_dma_mode (int /*<<< orphan*/ ,int) ; 
 void* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void receive_packet(struct net_device *dev, int len)
{
	int rlen;
	elp_device *adapter = netdev_priv(dev);
	void *target;
	struct sk_buff *skb;
	unsigned long flags;

	rlen = (len + 1) & ~1;
	skb = dev_alloc_skb(rlen + 2);

	if (!skb) {
		pr_warning("%s: memory squeeze, dropping packet\n", dev->name);
		target = adapter->dma_buffer;
		adapter->current_dma.target = NULL;
		/* FIXME: stats */
		return;
	}

	skb_reserve(skb, 2);
	target = skb_put(skb, rlen);
	if ((unsigned long)(target + rlen) >= MAX_DMA_ADDRESS) {
		adapter->current_dma.target = target;
		target = adapter->dma_buffer;
	} else {
		adapter->current_dma.target = NULL;
	}

	/* if this happens, we die */
	if (test_and_set_bit(0, (void *) &adapter->dmaing))
		pr_err("%s: rx blocked, DMA in progress, dir %d\n",
			dev->name, adapter->current_dma.direction);

	adapter->current_dma.direction = 0;
	adapter->current_dma.length = rlen;
	adapter->current_dma.skb = skb;
	adapter->current_dma.start_time = jiffies;

	outb_control(adapter->hcr_val | DIR | TCEN | DMAE, dev);

	flags=claim_dma_lock();
	disable_dma(dev->dma);
	clear_dma_ff(dev->dma);
	set_dma_mode(dev->dma, 0x04);	/* dma read */
	set_dma_addr(dev->dma, isa_virt_to_bus(target));
	set_dma_count(dev->dma, rlen);
	enable_dma(dev->dma);
	release_dma_lock(flags);

	if (elp_debug >= 3) {
		pr_debug("%s: rx DMA transfer started\n", dev->name);
	}

	if (adapter->rx_active)
		adapter->rx_active--;

	if (!adapter->busy)
		pr_warning("%s: receive_packet called, busy not set.\n", dev->name);
}