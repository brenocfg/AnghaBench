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
struct pcnet32_private {int /*<<< orphan*/  napi; } ;
struct net_device {int /*<<< orphan*/  trans_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct pcnet32_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_disable (struct net_device*) ; 

__attribute__((used)) static void pcnet32_netif_stop(struct net_device *dev)
{
	struct pcnet32_private *lp = netdev_priv(dev);

	dev->trans_start = jiffies;
	napi_disable(&lp->napi);
	netif_tx_disable(dev);
}