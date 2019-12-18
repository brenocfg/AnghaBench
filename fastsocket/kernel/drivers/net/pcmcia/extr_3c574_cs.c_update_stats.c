#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {int tx_carrier_errors; int tx_heartbeat_errors; int collisions; int tx_window_errors; int rx_fifo_errors; int tx_packets; int /*<<< orphan*/  tx_bytes; } ;
struct net_device {unsigned int base_addr; TYPE_1__ stats; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EL3WINDOW (int) ; 
 unsigned int EL3_STATUS ; 
 int inb (unsigned int) ; 
 int inw (unsigned int) ; 

__attribute__((used)) static void update_stats(struct net_device *dev)
{
	unsigned int ioaddr = dev->base_addr;
	u8 rx, tx, up;

	DEBUG(2, "%s: updating the statistics.\n", dev->name);

	if (inw(ioaddr+EL3_STATUS) == 0xffff) /* No card. */
		return;
		
	/* Unlike the 3c509 we need not turn off stats updates while reading. */
	/* Switch to the stats window, and read everything. */
	EL3WINDOW(6);
	dev->stats.tx_carrier_errors 		+= inb(ioaddr + 0);
	dev->stats.tx_heartbeat_errors		+= inb(ioaddr + 1);
	/* Multiple collisions. */	   	inb(ioaddr + 2);
	dev->stats.collisions			+= inb(ioaddr + 3);
	dev->stats.tx_window_errors		+= inb(ioaddr + 4);
	dev->stats.rx_fifo_errors		+= inb(ioaddr + 5);
	dev->stats.tx_packets			+= inb(ioaddr + 6);
	up		 			 = inb(ioaddr + 9);
	dev->stats.tx_packets			+= (up&0x30) << 4;
	/* Rx packets   */			   inb(ioaddr + 7);
	/* Tx deferrals */			   inb(ioaddr + 8);
	rx		 			 = inw(ioaddr + 10);
	tx					 = inw(ioaddr + 12);

	EL3WINDOW(4);
	/* BadSSD */				   inb(ioaddr + 12);
	up					 = inb(ioaddr + 13);

	dev->stats.tx_bytes 			+= tx + ((up & 0xf0) << 12);

	EL3WINDOW(1);
}