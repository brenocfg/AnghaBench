#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct net_device {int dummy; } ;
struct mlx4_en_priv {int /*<<< orphan*/  rx_ring_num; int /*<<< orphan*/  port_up; struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {TYPE_2__* dev; } ;
struct TYPE_6__ {int location; } ;
struct ethtool_rxnfc {int cmd; int rule_cnt; TYPE_3__ fs; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {scalar_t__ steering_mode; } ;
struct TYPE_5__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
#define  ETHTOOL_GRXCLSRLALL 131 
#define  ETHTOOL_GRXCLSRLCNT 130 
#define  ETHTOOL_GRXCLSRULE 129 
#define  ETHTOOL_GRXRINGS 128 
 scalar_t__ MLX4_STEERING_MODE_DEVICE_MANAGED ; 
 int mlx4_en_get_flow (struct net_device*,struct ethtool_rxnfc*,int) ; 
 int mlx4_en_get_num_flows (struct mlx4_en_priv*) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx4_en_get_rxnfc(struct net_device *dev, struct ethtool_rxnfc *cmd,
			     void *data)
{
	u32 *rule_locs = data;
	struct mlx4_en_priv *priv = netdev_priv(dev);
	struct mlx4_en_dev *mdev = priv->mdev;
	int err = 0;
	int i = 0, priority = 0;

	if ((cmd->cmd == ETHTOOL_GRXCLSRLCNT ||
	     cmd->cmd == ETHTOOL_GRXCLSRULE ||
	     cmd->cmd == ETHTOOL_GRXCLSRLALL) &&
	    (mdev->dev->caps.steering_mode !=
	     MLX4_STEERING_MODE_DEVICE_MANAGED || !priv->port_up))
		return -EINVAL;

	switch (cmd->cmd) {
	case ETHTOOL_GRXRINGS:
		cmd->data = priv->rx_ring_num;
		break;
	case ETHTOOL_GRXCLSRLCNT:
		cmd->rule_cnt = mlx4_en_get_num_flows(priv);
		break;
	case ETHTOOL_GRXCLSRULE:
		err = mlx4_en_get_flow(dev, cmd, cmd->fs.location);
		break;
	case ETHTOOL_GRXCLSRLALL:
		while ((!err || err == -ENOENT) && priority < cmd->rule_cnt) {
			err = mlx4_en_get_flow(dev, cmd, i);
			if (!err)
				rule_locs[priority++] = i;
			i++;
		}
		err = 0;
		break;
	default:
		err = -EOPNOTSUPP;
		break;
	}

	return err;
}