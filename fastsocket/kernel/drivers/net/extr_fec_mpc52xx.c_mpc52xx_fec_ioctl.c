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
struct mpc52xx_fec_priv {int /*<<< orphan*/  phydev; } ;
struct ifreq {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  if_mii (struct ifreq*) ; 
 struct mpc52xx_fec_priv* netdev_priv (struct net_device*) ; 
 int phy_mii_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mpc52xx_fec_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
	struct mpc52xx_fec_priv *priv = netdev_priv(dev);

	if (!priv->phydev)
		return -ENOTSUPP;

	return phy_mii_ioctl(priv->phydev, if_mii(rq), cmd);
}