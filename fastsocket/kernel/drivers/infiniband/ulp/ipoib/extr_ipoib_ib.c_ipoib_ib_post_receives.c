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
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ipoib_alloc_rx_skb (struct net_device*,int) ; 
 scalar_t__ ipoib_ib_post_receive (struct net_device*,int) ; 
 int ipoib_recvq_size ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*,int) ; 
 struct ipoib_dev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ipoib_ib_post_receives(struct net_device *dev)
{
	struct ipoib_dev_priv *priv = netdev_priv(dev);
	int i;

	for (i = 0; i < ipoib_recvq_size; ++i) {
		if (!ipoib_alloc_rx_skb(dev, i)) {
			ipoib_warn(priv, "failed to allocate receive buffer %d\n", i);
			return -ENOMEM;
		}
		if (ipoib_ib_post_receive(dev, i)) {
			ipoib_warn(priv, "ipoib_ib_post_receive failed for buf %d\n", i);
			return -EIO;
		}
	}

	return 0;
}