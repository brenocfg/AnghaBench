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
struct net_device_stats {int /*<<< orphan*/  rx_missed_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_frame_errors; } ;
struct net_device {long base_addr; struct net_device_stats stats; } ;
struct ei_device {int /*<<< orphan*/  page_lock; } ;

/* Variables and functions */
 scalar_t__ EN0_COUNTER0 ; 
 scalar_t__ EN0_COUNTER1 ; 
 scalar_t__ EN0_COUNTER2 ; 
 scalar_t__ inb_p (scalar_t__) ; 
 scalar_t__ netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct net_device_stats *get_stats(struct net_device *dev)
{
	long ioaddr = dev->base_addr;
	struct ei_device *ei_local = (struct ei_device *) netdev_priv(dev);
	unsigned long flags;
    
	/* If the card is stopped, just return the present stats. */
	if (!netif_running(dev))
		return &dev->stats;

	spin_lock_irqsave(&ei_local->page_lock,flags);
	/* Read the counter registers, assuming we are in page 0. */
	dev->stats.rx_frame_errors += inb_p(ioaddr + EN0_COUNTER0);
	dev->stats.rx_crc_errors   += inb_p(ioaddr + EN0_COUNTER1);
	dev->stats.rx_missed_errors+= inb_p(ioaddr + EN0_COUNTER2);
	spin_unlock_irqrestore(&ei_local->page_lock, flags);
    
	return &dev->stats;
}