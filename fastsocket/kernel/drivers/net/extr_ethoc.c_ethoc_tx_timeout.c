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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int /*<<< orphan*/  irq; } ;
struct ethoc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_SOURCE ; 
 int /*<<< orphan*/  ethoc_interrupt (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  ethoc_read (struct ethoc*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 struct ethoc* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ethoc_tx_timeout(struct net_device *dev)
{
	struct ethoc *priv = netdev_priv(dev);
	u32 pending = ethoc_read(priv, INT_SOURCE);
	if (likely(pending))
		ethoc_interrupt(dev->irq, dev);
}