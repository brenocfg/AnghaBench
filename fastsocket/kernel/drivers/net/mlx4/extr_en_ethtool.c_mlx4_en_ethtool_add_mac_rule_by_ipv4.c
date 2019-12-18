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
struct mlx4_spec_list {int dummy; } ;
struct mlx4_en_priv {TYPE_3__* dev; } ;
struct list_head {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  h_dest; } ;
struct TYPE_5__ {int flow_type; TYPE_1__ h_ext; } ;
struct ethtool_rxnfc {TYPE_2__ fs; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_6__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETH_ALEN ; 
 int FLOW_MAC_EXT ; 
 int /*<<< orphan*/  ip_eth_mc_map (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  ipv4_is_multicast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char**,int /*<<< orphan*/ ,int) ; 
 int mlx4_en_ethtool_add_mac_rule (struct ethtool_rxnfc*,struct list_head*,struct mlx4_spec_list*,unsigned char*) ; 

__attribute__((used)) static int mlx4_en_ethtool_add_mac_rule_by_ipv4(struct mlx4_en_priv *priv,
						struct ethtool_rxnfc *cmd,
						struct list_head *rule_list_h,
						struct mlx4_spec_list *spec_l2,
						__be32 ipv4_dst)
{
#ifdef CONFIG_INET
	unsigned char mac[ETH_ALEN];

	if (!ipv4_is_multicast(ipv4_dst)) {
		if (cmd->fs.flow_type & FLOW_MAC_EXT)
			memcpy(&mac, cmd->fs.h_ext.h_dest, ETH_ALEN);
		else
			memcpy(&mac, priv->dev->dev_addr, ETH_ALEN);
	} else {
		ip_eth_mc_map(ipv4_dst, mac);
	}

	return mlx4_en_ethtool_add_mac_rule(cmd, rule_list_h, spec_l2, &mac[0]);
#else
	return -EINVAL;
#endif
}