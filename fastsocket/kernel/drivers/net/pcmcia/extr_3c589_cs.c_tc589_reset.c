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
struct net_device {unsigned int base_addr; int /*<<< orphan*/  if_port; int /*<<< orphan*/ * dev_addr; } ;

/* Variables and functions */
 int AckIntr ; 
 int AdapterFailure ; 
 int /*<<< orphan*/  EL3WINDOW (int) ; 
 unsigned int EL3_CMD ; 
 int IntLatch ; 
 int IntReq ; 
 int RxComplete ; 
 int RxEarly ; 
 int RxEnable ; 
 int SetIntrEnb ; 
 int SetStatusEnb ; 
 int StatsDisable ; 
 int StatsEnable ; 
 int StatsFull ; 
 int TxAvailable ; 
 int TxEnable ; 
 int /*<<< orphan*/  inb (unsigned int) ; 
 int /*<<< orphan*/  inw (unsigned int) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  outw (int,unsigned int) ; 
 int /*<<< orphan*/  set_rx_mode (struct net_device*) ; 
 int /*<<< orphan*/  tc589_set_xcvr (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tc589_reset(struct net_device *dev)
{
    unsigned int ioaddr = dev->base_addr;
    int i;
    
    EL3WINDOW(0);
    outw(0x0001, ioaddr + 4);			/* Activate board. */ 
    outw(0x3f00, ioaddr + 8);			/* Set the IRQ line. */
    
    /* Set the station address in window 2. */
    EL3WINDOW(2);
    for (i = 0; i < 6; i++)
	outb(dev->dev_addr[i], ioaddr + i);

    tc589_set_xcvr(dev, dev->if_port);
    
    /* Switch to the stats window, and clear all stats by reading. */
    outw(StatsDisable, ioaddr + EL3_CMD);
    EL3WINDOW(6);
    for (i = 0; i < 9; i++)
	inb(ioaddr+i);
    inw(ioaddr + 10);
    inw(ioaddr + 12);
    
    /* Switch to register set 1 for normal use. */
    EL3WINDOW(1);

    set_rx_mode(dev);
    outw(StatsEnable, ioaddr + EL3_CMD); /* Turn on statistics. */
    outw(RxEnable, ioaddr + EL3_CMD); /* Enable the receiver. */
    outw(TxEnable, ioaddr + EL3_CMD); /* Enable transmitter. */
    /* Allow status bits to be seen. */
    outw(SetStatusEnb | 0xff, ioaddr + EL3_CMD);
    /* Ack all pending events, and set active indicator mask. */
    outw(AckIntr | IntLatch | TxAvailable | RxEarly | IntReq,
	 ioaddr + EL3_CMD);
    outw(SetIntrEnb | IntLatch | TxAvailable | RxComplete | StatsFull
	 | AdapterFailure, ioaddr + EL3_CMD);
}