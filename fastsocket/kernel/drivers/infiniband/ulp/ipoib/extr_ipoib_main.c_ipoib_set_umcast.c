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
struct ipoib_dev_priv {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPOIB_FLAG_UMCAST ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*) ; 
 struct ipoib_dev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ipoib_set_umcast(struct net_device *ndev, int umcast_val)
{
	struct ipoib_dev_priv *priv = netdev_priv(ndev);

	if (umcast_val > 0) {
		set_bit(IPOIB_FLAG_UMCAST, &priv->flags);
		ipoib_warn(priv, "ignoring multicast groups joined directly "
				"by userspace\n");
	} else
		clear_bit(IPOIB_FLAG_UMCAST, &priv->flags);
}