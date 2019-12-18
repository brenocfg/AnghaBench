#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_3__ {unsigned long data; int /*<<< orphan*/  function; scalar_t__ expires; } ;
struct bmac_data {int timeout_active; int /*<<< orphan*/  lock; TYPE_1__ tx_timeout; } ;

/* Variables and functions */
 scalar_t__ TX_TIMEOUT ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  bmac_tx_timeout ; 
 int /*<<< orphan*/  del_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 struct bmac_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void bmac_set_timeout(struct net_device *dev)
{
	struct bmac_data *bp = netdev_priv(dev);
	unsigned long flags;

	spin_lock_irqsave(&bp->lock, flags);
	if (bp->timeout_active)
		del_timer(&bp->tx_timeout);
	bp->tx_timeout.expires = jiffies + TX_TIMEOUT;
	bp->tx_timeout.function = bmac_tx_timeout;
	bp->tx_timeout.data = (unsigned long) dev;
	add_timer(&bp->tx_timeout);
	bp->timeout_active = 1;
	spin_unlock_irqrestore(&bp->lock, flags);
}