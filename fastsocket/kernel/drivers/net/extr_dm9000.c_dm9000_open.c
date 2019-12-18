#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  irq; } ;
struct TYPE_9__ {int /*<<< orphan*/  mii; scalar_t__ dbug_cnt; int /*<<< orphan*/  dev; TYPE_1__* irq_res; } ;
typedef  TYPE_2__ board_info_t ;
struct TYPE_8__ {unsigned long flags; } ;

/* Variables and functions */
 int EAGAIN ; 
 unsigned long IRQF_SHARED ; 
 unsigned long IRQF_TRIGGER_MASK ; 
 unsigned long IRQF_TRIGGER_NONE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dm9000_init_dm9000 (struct net_device*) ; 
 int /*<<< orphan*/  dm9000_interrupt ; 
 int /*<<< orphan*/  dm9000_reset (TYPE_2__*) ; 
 int /*<<< orphan*/  dm9000_schedule_poll (TYPE_2__*) ; 
 int /*<<< orphan*/  mii_check_media (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_ifup (TYPE_2__*) ; 
 int /*<<< orphan*/  netif_msg_link (TYPE_2__*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static int
dm9000_open(struct net_device *dev)
{
	board_info_t *db = netdev_priv(dev);
	unsigned long irqflags = db->irq_res->flags & IRQF_TRIGGER_MASK;

	if (netif_msg_ifup(db))
		dev_dbg(db->dev, "enabling %s\n", dev->name);

	/* If there is no IRQ type specified, default to something that
	 * may work, and tell the user that this is a problem */

	if (irqflags == IRQF_TRIGGER_NONE)
		dev_warn(db->dev, "WARNING: no IRQ resource flags set.\n");

	irqflags |= IRQF_SHARED;

	if (request_irq(dev->irq, &dm9000_interrupt, irqflags, dev->name, dev))
		return -EAGAIN;

	/* Initialize DM9000 board */
	dm9000_reset(db);
	dm9000_init_dm9000(dev);

	/* Init driver variable */
	db->dbug_cnt = 0;

	mii_check_media(&db->mii, netif_msg_link(db), 1);
	netif_start_queue(dev);
	
	dm9000_schedule_poll(db);

	return 0;
}