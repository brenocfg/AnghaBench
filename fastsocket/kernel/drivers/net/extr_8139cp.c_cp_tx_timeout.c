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
struct net_device {int /*<<< orphan*/  name; } ;
struct cp_private {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  Cmd ; 
 int /*<<< orphan*/  CpCmd ; 
 int /*<<< orphan*/  IntrMask ; 
 int /*<<< orphan*/  IntrStatus ; 
 int /*<<< orphan*/  cp_clean_rings (struct cp_private*) ; 
 int cp_init_rings (struct cp_private*) ; 
 int /*<<< orphan*/  cp_start_hw (struct cp_private*) ; 
 int /*<<< orphan*/  cp_stop_hw (struct cp_private*) ; 
 int /*<<< orphan*/  cpr16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpr8 (int /*<<< orphan*/ ) ; 
 struct cp_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void cp_tx_timeout(struct net_device *dev)
{
	struct cp_private *cp = netdev_priv(dev);
	unsigned long flags;
	int rc;

	pr_warning("%s: Transmit timeout, status %2x %4x %4x %4x\n",
	       dev->name, cpr8(Cmd), cpr16(CpCmd),
	       cpr16(IntrStatus), cpr16(IntrMask));

	spin_lock_irqsave(&cp->lock, flags);

	cp_stop_hw(cp);
	cp_clean_rings(cp);
	rc = cp_init_rings(cp);
	cp_start_hw(cp);

	netif_wake_queue(dev);

	spin_unlock_irqrestore(&cp->lock, flags);

	return;
}