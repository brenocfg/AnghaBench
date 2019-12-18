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
struct net_device {unsigned int base_addr; int* dev_addr; int mtu; } ;
struct el3_private {int advertising; int /*<<< orphan*/  window_lock; int /*<<< orphan*/  phys; scalar_t__ autoselect; } ;

/* Variables and functions */
 int AckIntr ; 
 int AdapterFailure ; 
 int /*<<< orphan*/  EL3WINDOW (int) ; 
 unsigned int EL3_CMD ; 
 int IntLatch ; 
 int IntReq ; 
 unsigned int RunnerRdCtrl ; 
 unsigned int RunnerWrCtrl ; 
 int RxComplete ; 
 int RxEarly ; 
 int RxEnable ; 
 int RxReset ; 
 int SetIntrEnb ; 
 int SetStatusEnb ; 
 int StatsDisable ; 
 int StatsEnable ; 
 int StatsFull ; 
 int TotalReset ; 
 int TxAvailable ; 
 int TxEnable ; 
 int TxReset ; 
 scalar_t__ Wn3_Config ; 
 unsigned int Wn3_MAC_Ctrl ; 
 unsigned int Wn3_Options ; 
 unsigned int Wn4_NetDiag ; 
 int /*<<< orphan*/  auto_polarity ; 
 int /*<<< orphan*/  inb (unsigned int) ; 
 int /*<<< orphan*/  inw (unsigned int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int mdio_read (unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdio_sync (unsigned int,int) ; 
 int /*<<< orphan*/  mdio_write (unsigned int,int /*<<< orphan*/ ,int,int) ; 
 struct el3_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outb (int,unsigned int) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 int /*<<< orphan*/  outw (int,unsigned int) ; 
 int /*<<< orphan*/  set_rx_mode (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tc574_wait_for_completion (struct net_device*,int) ; 

__attribute__((used)) static void tc574_reset(struct net_device *dev)
{
	struct el3_private *lp = netdev_priv(dev);
	int i;
	unsigned int ioaddr = dev->base_addr;
	unsigned long flags;

	tc574_wait_for_completion(dev, TotalReset|0x10);

	spin_lock_irqsave(&lp->window_lock, flags);
	/* Clear any transactions in progress. */
	outw(0, ioaddr + RunnerWrCtrl);
	outw(0, ioaddr + RunnerRdCtrl);

	/* Set the station address and mask. */
	EL3WINDOW(2);
	for (i = 0; i < 6; i++)
		outb(dev->dev_addr[i], ioaddr + i);
	for (; i < 12; i+=2)
		outw(0, ioaddr + i);

	/* Reset config options */
	EL3WINDOW(3);
	outb((dev->mtu > 1500 ? 0x40 : 0), ioaddr + Wn3_MAC_Ctrl);
	outl((lp->autoselect ? 0x01000000 : 0) | 0x0062001b,
		 ioaddr + Wn3_Config);
	/* Roadrunner only: Turn on the MII transceiver. */
	outw(0x8040, ioaddr + Wn3_Options);
	mdelay(1);
	outw(0xc040, ioaddr + Wn3_Options);
	EL3WINDOW(1);
	spin_unlock_irqrestore(&lp->window_lock, flags);
	
	tc574_wait_for_completion(dev, TxReset);
	tc574_wait_for_completion(dev, RxReset);
	mdelay(1);
	spin_lock_irqsave(&lp->window_lock, flags);
	EL3WINDOW(3);
	outw(0x8040, ioaddr + Wn3_Options);

	/* Switch to the stats window, and clear all stats by reading. */
	outw(StatsDisable, ioaddr + EL3_CMD);
	EL3WINDOW(6);
	for (i = 0; i < 10; i++)
		inb(ioaddr + i);
	inw(ioaddr + 10);
	inw(ioaddr + 12);
	EL3WINDOW(4);
	inb(ioaddr + 12);
	inb(ioaddr + 13);

	/* .. enable any extra statistics bits.. */
	outw(0x0040, ioaddr + Wn4_NetDiag);
	
	EL3WINDOW(1);
	spin_unlock_irqrestore(&lp->window_lock, flags);
	
	/* .. re-sync MII and re-fill what NWay is advertising. */
	mdio_sync(ioaddr, 32);
	mdio_write(ioaddr, lp->phys, 4, lp->advertising);
	if (!auto_polarity) {
		/* works for TDK 78Q2120 series MII's */
		i = mdio_read(ioaddr, lp->phys, 16) | 0x20;
		mdio_write(ioaddr, lp->phys, 16, i);
	}

	spin_lock_irqsave(&lp->window_lock, flags);
	/* Switch to register set 1 for normal use, just for TxFree. */
	set_rx_mode(dev);
	spin_unlock_irqrestore(&lp->window_lock, flags);
	outw(StatsEnable, ioaddr + EL3_CMD); /* Turn on statistics. */
	outw(RxEnable, ioaddr + EL3_CMD); /* Enable the receiver. */
	outw(TxEnable, ioaddr + EL3_CMD); /* Enable transmitter. */
	/* Allow status bits to be seen. */
	outw(SetStatusEnb | 0xff, ioaddr + EL3_CMD);
	/* Ack all pending events, and set active indicator mask. */
	outw(AckIntr | IntLatch | TxAvailable | RxEarly | IntReq,
		 ioaddr + EL3_CMD);
	outw(SetIntrEnb | IntLatch | TxAvailable | RxComplete | StatsFull
		 | AdapterFailure | RxEarly, ioaddr + EL3_CMD);
}