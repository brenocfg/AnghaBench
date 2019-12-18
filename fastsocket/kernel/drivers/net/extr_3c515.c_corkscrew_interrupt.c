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
struct net_device {int base_addr; int name; int irq; } ;
struct corkscrew_private {unsigned int dirty_tx; unsigned int cur_tx; int /*<<< orphan*/  lock; int /*<<< orphan*/ * tx_skb; scalar_t__ tx_full; int /*<<< orphan*/ ** tx_skbuff; int /*<<< orphan*/ * tx_ring; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int AckIntr ; 
 int AdapterFailure ; 
 int DMADone ; 
 int DownComplete ; 
 scalar_t__ DownListPtr ; 
 int /*<<< orphan*/  EL3WINDOW (int) ; 
 scalar_t__ EL3_CMD ; 
 scalar_t__ EL3_STATUS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int IntLatch ; 
 int IntReq ; 
 int RxComplete ; 
 int RxEarly ; 
 int RxEnable ; 
 int RxReset ; 
 int SetIntrEnb ; 
 int SetStatusEnb ; 
 int StatsFull ; 
 unsigned int TX_RING_SIZE ; 
 int Timer ; 
 int TxAvailable ; 
 int TxComplete ; 
 int UpComplete ; 
 scalar_t__ Wn7_MasterStatus ; 
 int /*<<< orphan*/  boomerang_rx (struct net_device*) ; 
 int corkscrew_debug ; 
 int /*<<< orphan*/  corkscrew_rx (struct net_device*) ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int,struct net_device*) ; 
 int inb (int) ; 
 scalar_t__ inl (scalar_t__) ; 
 int inw (scalar_t__) ; 
 scalar_t__ isa_virt_to_bus (int /*<<< orphan*/ *) ; 
 int max_interrupt_work ; 
 struct corkscrew_private* netdev_priv (struct net_device*) ; 
 int netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,int,int,int) ; 
 int /*<<< orphan*/  pr_notice (char*,int) ; 
 int /*<<< orphan*/  set_rx_mode (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_stats (int,struct net_device*) ; 

__attribute__((used)) static irqreturn_t corkscrew_interrupt(int irq, void *dev_id)
{
	/* Use the now-standard shared IRQ implementation. */
	struct net_device *dev = dev_id;
	struct corkscrew_private *lp = netdev_priv(dev);
	int ioaddr, status;
	int latency;
	int i = max_interrupt_work;

	ioaddr = dev->base_addr;
	latency = inb(ioaddr + Timer);

	spin_lock(&lp->lock);

	status = inw(ioaddr + EL3_STATUS);

	if (corkscrew_debug > 4)
		pr_debug("%s: interrupt, status %4.4x, timer %d.\n",
			dev->name, status, latency);
	if ((status & 0xE000) != 0xE000) {
		static int donedidthis;
		/* Some interrupt controllers store a bogus interrupt from boot-time.
		   Ignore a single early interrupt, but don't hang the machine for
		   other interrupt problems. */
		if (donedidthis++ > 100) {
			pr_err("%s: Bogus interrupt, bailing. Status %4.4x, start=%d.\n",
				   dev->name, status, netif_running(dev));
			free_irq(dev->irq, dev);
			dev->irq = -1;
		}
	}

	do {
		if (corkscrew_debug > 5)
			pr_debug("%s: In interrupt loop, status %4.4x.\n",
			       dev->name, status);
		if (status & RxComplete)
			corkscrew_rx(dev);

		if (status & TxAvailable) {
			if (corkscrew_debug > 5)
				pr_debug("	TX room bit was handled.\n");
			/* There's room in the FIFO for a full-sized packet. */
			outw(AckIntr | TxAvailable, ioaddr + EL3_CMD);
			netif_wake_queue(dev);
		}
		if (status & DownComplete) {
			unsigned int dirty_tx = lp->dirty_tx;

			while (lp->cur_tx - dirty_tx > 0) {
				int entry = dirty_tx % TX_RING_SIZE;
				if (inl(ioaddr + DownListPtr) == isa_virt_to_bus(&lp->tx_ring[entry]))
					break;	/* It still hasn't been processed. */
				if (lp->tx_skbuff[entry]) {
					dev_kfree_skb_irq(lp->tx_skbuff[entry]);
					lp->tx_skbuff[entry] = NULL;
				}
				dirty_tx++;
			}
			lp->dirty_tx = dirty_tx;
			outw(AckIntr | DownComplete, ioaddr + EL3_CMD);
			if (lp->tx_full && (lp->cur_tx - dirty_tx <= TX_RING_SIZE - 1)) {
				lp->tx_full = 0;
				netif_wake_queue(dev);
			}
		}
#ifdef VORTEX_BUS_MASTER
		if (status & DMADone) {
			outw(0x1000, ioaddr + Wn7_MasterStatus);	/* Ack the event. */
			dev_kfree_skb_irq(lp->tx_skb);	/* Release the transferred buffer */
			netif_wake_queue(dev);
		}
#endif
		if (status & UpComplete) {
			boomerang_rx(dev);
			outw(AckIntr | UpComplete, ioaddr + EL3_CMD);
		}
		if (status & (AdapterFailure | RxEarly | StatsFull)) {
			/* Handle all uncommon interrupts at once. */
			if (status & RxEarly) {	/* Rx early is unused. */
				corkscrew_rx(dev);
				outw(AckIntr | RxEarly, ioaddr + EL3_CMD);
			}
			if (status & StatsFull) {	/* Empty statistics. */
				static int DoneDidThat;
				if (corkscrew_debug > 4)
					pr_debug("%s: Updating stats.\n", dev->name);
				update_stats(ioaddr, dev);
				/* DEBUG HACK: Disable statistics as an interrupt source. */
				/* This occurs when we have the wrong media type! */
				if (DoneDidThat == 0 && inw(ioaddr + EL3_STATUS) & StatsFull) {
					int win, reg;
					pr_notice("%s: Updating stats failed, disabling stats as an interrupt source.\n",
						dev->name);
					for (win = 0; win < 8; win++) {
						EL3WINDOW(win);
						pr_notice("Vortex window %d:", win);
						for (reg = 0; reg < 16; reg++)
							pr_cont(" %2.2x", inb(ioaddr + reg));
						pr_cont("\n");
					}
					EL3WINDOW(7);
					outw(SetIntrEnb | TxAvailable |
					     RxComplete | AdapterFailure |
					     UpComplete | DownComplete |
					     TxComplete, ioaddr + EL3_CMD);
					DoneDidThat++;
				}
			}
			if (status & AdapterFailure) {
				/* Adapter failure requires Rx reset and reinit. */
				outw(RxReset, ioaddr + EL3_CMD);
				/* Set the Rx filter to the current state. */
				set_rx_mode(dev);
				outw(RxEnable, ioaddr + EL3_CMD);	/* Re-enable the receiver. */
				outw(AckIntr | AdapterFailure,
				     ioaddr + EL3_CMD);
			}
		}

		if (--i < 0) {
			pr_err("%s: Too much work in interrupt, status %4.4x. Disabling functions (%4.4x).\n",
				dev->name, status, SetStatusEnb | ((~status) & 0x7FE));
			/* Disable all pending interrupts. */
			outw(SetStatusEnb | ((~status) & 0x7FE), ioaddr + EL3_CMD);
			outw(AckIntr | 0x7FF, ioaddr + EL3_CMD);
			break;
		}
		/* Acknowledge the IRQ. */
		outw(AckIntr | IntReq | IntLatch, ioaddr + EL3_CMD);

	} while ((status = inw(ioaddr + EL3_STATUS)) & (IntLatch | RxComplete));

	spin_unlock(&lp->lock);

	if (corkscrew_debug > 4)
		pr_debug("%s: exiting interrupt, status %4.4x.\n", dev->name, status);
	return IRQ_HANDLED;
}