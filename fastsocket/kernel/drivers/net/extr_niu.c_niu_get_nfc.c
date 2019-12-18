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
typedef  int /*<<< orphan*/  u32 ;
struct niu {int /*<<< orphan*/  num_rx_rings; } ;
struct net_device {int dummy; } ;
struct ethtool_rxnfc {int cmd; int /*<<< orphan*/  rule_cnt; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int EINVAL ; 
#define  ETHTOOL_GRXCLSRLALL 132 
#define  ETHTOOL_GRXCLSRLCNT 131 
#define  ETHTOOL_GRXCLSRULE 130 
#define  ETHTOOL_GRXFH 129 
#define  ETHTOOL_GRXRINGS 128 
 struct niu* netdev_priv (struct net_device*) ; 
 int niu_get_ethtool_tcam_all (struct niu*,struct ethtool_rxnfc*,int /*<<< orphan*/ *) ; 
 int niu_get_ethtool_tcam_entry (struct niu*,struct ethtool_rxnfc*) ; 
 int niu_get_hash_opts (struct niu*,struct ethtool_rxnfc*) ; 
 int /*<<< orphan*/  tcam_get_valid_entry_cnt (struct niu*) ; 

__attribute__((used)) static int niu_get_nfc(struct net_device *dev, struct ethtool_rxnfc *cmd,
		       void *rule_locs)
{
	struct niu *np = netdev_priv(dev);
	int ret = 0;

	switch (cmd->cmd) {
	case ETHTOOL_GRXFH:
		ret = niu_get_hash_opts(np, cmd);
		break;
	case ETHTOOL_GRXRINGS:
		cmd->data = np->num_rx_rings;
		break;
	case ETHTOOL_GRXCLSRLCNT:
		cmd->rule_cnt = tcam_get_valid_entry_cnt(np);
		break;
	case ETHTOOL_GRXCLSRULE:
		ret = niu_get_ethtool_tcam_entry(np, cmd);
		break;
	case ETHTOOL_GRXCLSRLALL:
		ret = niu_get_ethtool_tcam_all(np, cmd, (u32 *)rule_locs);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}