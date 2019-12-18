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
struct niu {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  location; } ;
struct ethtool_rxnfc {int cmd; TYPE_1__ fs; } ;

/* Variables and functions */
 int EINVAL ; 
#define  ETHTOOL_SRXCLSRLDEL 130 
#define  ETHTOOL_SRXCLSRLINS 129 
#define  ETHTOOL_SRXFH 128 
 struct niu* netdev_priv (struct net_device*) ; 
 int niu_add_ethtool_tcam_entry (struct niu*,struct ethtool_rxnfc*) ; 
 int niu_del_ethtool_tcam_entry (struct niu*,int /*<<< orphan*/ ) ; 
 int niu_set_hash_opts (struct niu*,struct ethtool_rxnfc*) ; 

__attribute__((used)) static int niu_set_nfc(struct net_device *dev, struct ethtool_rxnfc *cmd)
{
	struct niu *np = netdev_priv(dev);
	int ret = 0;

	switch (cmd->cmd) {
	case ETHTOOL_SRXFH:
		ret = niu_set_hash_opts(np, cmd);
		break;
	case ETHTOOL_SRXCLSRLINS:
		ret = niu_add_ethtool_tcam_entry(np, cmd);
		break;
	case ETHTOOL_SRXCLSRLDEL:
		ret = niu_del_ethtool_tcam_entry(np, cmd->fs.location);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}