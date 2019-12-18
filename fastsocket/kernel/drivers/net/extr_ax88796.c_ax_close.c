#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  name; } ;
struct ei_device {scalar_t__ mem; } ;
struct ax_device {int /*<<< orphan*/  mii_timer; scalar_t__ running; TYPE_1__* plat; TYPE_2__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int gpoc_val; } ;

/* Variables and functions */
 scalar_t__ EI_SHIFT (int) ; 
 int /*<<< orphan*/  ax_ei_close (struct net_device*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ei_outb (int,scalar_t__) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 struct ei_device* netdev_priv (struct net_device*) ; 
 struct ax_device* to_ax_dev (struct net_device*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int ax_close(struct net_device *dev)
{
	struct ax_device *ax = to_ax_dev(dev);
	struct ei_device *ei_local = netdev_priv(dev);

	dev_dbg(&ax->dev->dev, "%s: close\n", dev->name);

	/* turn the phy off */

	ei_outb(ax->plat->gpoc_val | (1<<6),
	       ei_local->mem + EI_SHIFT(0x17));

	ax->running = 0;
	wmb();

	del_timer_sync(&ax->mii_timer);
	ax_ei_close(dev);

	free_irq(dev->irq, dev);
	return 0;
}