#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct mlx4_en_priv {TYPE_1__* mdev; struct ethtool_flow_id* ethtool_rules; } ;
struct TYPE_4__ {size_t location; } ;
struct ethtool_rxnfc {TYPE_2__ fs; } ;
struct ethtool_rx_flow_spec {int dummy; } ;
struct ethtool_flow_id {int /*<<< orphan*/  list; int /*<<< orphan*/  flow_spec; scalar_t__ id; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 size_t MAX_NUM_OF_FS_RULES ; 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*,size_t,scalar_t__) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int mlx4_flow_detach (int /*<<< orphan*/ ,scalar_t__) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx4_en_flow_detach(struct net_device *dev,
			       struct ethtool_rxnfc *cmd)
{
	int err = 0;
	struct ethtool_flow_id *rule;
	struct mlx4_en_priv *priv = netdev_priv(dev);

	if (cmd->fs.location >= MAX_NUM_OF_FS_RULES)
		return -EINVAL;

	rule = &priv->ethtool_rules[cmd->fs.location];
	if (!rule->id) {
		err =  -ENOENT;
		goto out;
	}

	err = mlx4_flow_detach(priv->mdev->dev, rule->id);
	if (err) {
		en_err(priv, "Fail to detach network rule at location %d. registration id = 0x%llx\n",
		       cmd->fs.location, rule->id);
		goto out;
	}
	rule->id = 0;
	memset(&rule->flow_spec, 0, sizeof(struct ethtool_rx_flow_spec));
	list_del(&rule->list);
out:
	return err;

}