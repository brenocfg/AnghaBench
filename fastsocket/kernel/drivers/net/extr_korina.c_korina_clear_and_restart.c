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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct korina_private {TYPE_1__* eth_regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  ethintfc; } ;

/* Variables and functions */
 int /*<<< orphan*/  korina_restart (struct net_device*) ; 
 struct korina_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void korina_clear_and_restart(struct net_device *dev, u32 value)
{
	struct korina_private *lp = netdev_priv(dev);

	netif_stop_queue(dev);
	writel(value, &lp->eth_regs->ethintfc);
	korina_restart(dev);
}