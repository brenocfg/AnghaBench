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
struct net_device {scalar_t__ base_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  rrastart; } ;
typedef  TYPE_1__ ibmlana_priv ;

/* Variables and functions */
 scalar_t__ SONIC_RRP ; 
 scalar_t__ SONIC_RWP ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void irqrbe_handler(struct net_device *dev)
{
	ibmlana_priv *priv = netdev_priv(dev);

	/* point the SONIC back to the RRA start */

	outw(priv->rrastart, dev->base_addr + SONIC_RRP);
	outw(priv->rrastart, dev->base_addr + SONIC_RWP);
}