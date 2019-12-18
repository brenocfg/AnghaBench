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
struct ucc_geth_private {int /*<<< orphan*/  timeout_work; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct ucc_geth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ucc_geth_timeout(struct net_device *dev)
{
	struct ucc_geth_private *ugeth = netdev_priv(dev);

	netif_carrier_off(dev);
	schedule_work(&ugeth->timeout_work);
}