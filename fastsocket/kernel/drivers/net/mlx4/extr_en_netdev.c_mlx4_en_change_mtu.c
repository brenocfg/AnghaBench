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
struct net_device {int mtu; } ;
struct mlx4_en_priv {int max_mtu; int port; int /*<<< orphan*/  watchdog_task; struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {int /*<<< orphan*/  state_lock; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  device_up; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV ; 
 int EPERM ; 
 int MLX4_EN_MIN_MTU ; 
 int /*<<< orphan*/  en_dbg (int /*<<< orphan*/ ,struct mlx4_en_priv*,char*,...) ; 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*,int) ; 
 int mlx4_en_start_port (struct net_device*) ; 
 int /*<<< orphan*/  mlx4_en_stop_port (struct net_device*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx4_en_change_mtu(struct net_device *dev, int new_mtu)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	struct mlx4_en_dev *mdev = priv->mdev;
	int err = 0;

	en_dbg(DRV, priv, "Change MTU called - current:%d new:%d\n",
		 dev->mtu, new_mtu);

	if ((new_mtu < MLX4_EN_MIN_MTU) || (new_mtu > priv->max_mtu)) {
		en_err(priv, "Bad MTU size:%d.\n", new_mtu);
		return -EPERM;
	}
	dev->mtu = new_mtu;

	if (netif_running(dev)) {
		mutex_lock(&mdev->state_lock);
		if (!mdev->device_up) {
			/* NIC is probably restarting - let watchdog task reset
			 * the port */
			en_dbg(DRV, priv, "Change MTU called with card down!?\n");
		} else {
			mlx4_en_stop_port(dev, 1);
			err = mlx4_en_start_port(dev);
			if (err) {
				en_err(priv, "Failed restarting port:%d\n",
					 priv->port);
				queue_work(mdev->workqueue, &priv->watchdog_task);
			}
		}
		mutex_unlock(&mdev->state_lock);
	}
	return 0;
}