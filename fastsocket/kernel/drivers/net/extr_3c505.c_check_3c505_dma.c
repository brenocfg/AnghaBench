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
struct net_device {int /*<<< orphan*/  dma; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {scalar_t__ direction; scalar_t__ start_time; } ;
struct TYPE_5__ {int hcr_val; int /*<<< orphan*/  lock; scalar_t__ rx_active; scalar_t__ busy; scalar_t__ dmaing; TYPE_1__ current_dma; } ;
typedef  TYPE_2__ elp_device ;

/* Variables and functions */
 int DIR ; 
 int DMAE ; 
 int TCEN ; 
 unsigned long claim_dma_lock () ; 
 int /*<<< orphan*/  disable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_dma_residue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 TYPE_2__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outb_control (int,struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void check_3c505_dma(struct net_device *dev)
{
	elp_device *adapter = netdev_priv(dev);
	if (adapter->dmaing && time_after(jiffies, adapter->current_dma.start_time + 10)) {
		unsigned long flags, f;
		pr_err("%s: DMA %s timed out, %d bytes left\n", dev->name,
			adapter->current_dma.direction ? "download" : "upload",
			get_dma_residue(dev->dma));
		spin_lock_irqsave(&adapter->lock, flags);
		adapter->dmaing = 0;
		adapter->busy = 0;

		f=claim_dma_lock();
		disable_dma(dev->dma);
		release_dma_lock(f);

		if (adapter->rx_active)
			adapter->rx_active--;
		outb_control(adapter->hcr_val & ~(DMAE | TCEN | DIR), dev);
		spin_unlock_irqrestore(&adapter->lock, flags);
	}
}