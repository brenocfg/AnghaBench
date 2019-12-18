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
typedef  int /*<<< orphan*/  ulong ;
struct pcnet32_access {int (* read_bcr ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* write_bcr ) (int /*<<< orphan*/ ,int,int) ;} ;
struct pcnet32_private {int /*<<< orphan*/  blink_timer; int /*<<< orphan*/  lock; struct pcnet32_access a; } ;
struct net_device {int /*<<< orphan*/  base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCNET32_BLINK_TIMEOUT ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pcnet32_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int) ; 
 int stub2 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pcnet32_led_blink_callback(struct net_device *dev)
{
	struct pcnet32_private *lp = netdev_priv(dev);
	struct pcnet32_access *a = &lp->a;
	ulong ioaddr = dev->base_addr;
	unsigned long flags;
	int i;

	spin_lock_irqsave(&lp->lock, flags);
	for (i = 4; i < 8; i++) {
		a->write_bcr(ioaddr, i, a->read_bcr(ioaddr, i) ^ 0x4000);
	}
	spin_unlock_irqrestore(&lp->lock, flags);

	mod_timer(&lp->blink_timer, PCNET32_BLINK_TIMEOUT);
}