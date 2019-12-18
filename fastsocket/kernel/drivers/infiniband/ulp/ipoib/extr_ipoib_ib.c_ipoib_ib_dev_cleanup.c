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
struct net_device {int dummy; } ;
struct ipoib_dev_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipoib_dbg (struct ipoib_dev_priv*,char*) ; 
 int /*<<< orphan*/  ipoib_mcast_dev_flush (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_mcast_stop_thread (struct net_device*,int) ; 
 int /*<<< orphan*/  ipoib_transport_dev_cleanup (struct net_device*) ; 
 struct ipoib_dev_priv* netdev_priv (struct net_device*) ; 

void ipoib_ib_dev_cleanup(struct net_device *dev)
{
	struct ipoib_dev_priv *priv = netdev_priv(dev);

	ipoib_dbg(priv, "cleaning up ib_dev\n");

	ipoib_mcast_stop_thread(dev, 1);
	ipoib_mcast_dev_flush(dev);

	ipoib_transport_dev_cleanup(dev);
}