#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int /*<<< orphan*/  trans_start; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  io_addr; } ;
typedef  TYPE_1__ board_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  dm9000_init_dm9000 (struct net_device*) ; 
 int /*<<< orphan*/  dm9000_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  jiffies ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dm9000_timeout(struct net_device *dev)
{
	board_info_t *db = netdev_priv(dev);
	u8 reg_save;
	unsigned long flags;

	/* Save previous register address */
	reg_save = readb(db->io_addr);
	spin_lock_irqsave(&db->lock, flags);

	netif_stop_queue(dev);
	dm9000_reset(db);
	dm9000_init_dm9000(dev);
	/* We can accept TX packets again */
	dev->trans_start = jiffies;
	netif_wake_queue(dev);

	/* Restore previous register address */
	writeb(reg_save, db->io_addr);
	spin_unlock_irqrestore(&db->lock, flags);
}