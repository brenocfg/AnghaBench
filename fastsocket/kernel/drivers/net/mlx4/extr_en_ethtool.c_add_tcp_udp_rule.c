#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {void* dst_port_msk; void* src_port_msk; int /*<<< orphan*/  dst_port; int /*<<< orphan*/  src_port; } ;
struct TYPE_13__ {void* dst_ip_msk; void* src_ip_msk; int /*<<< orphan*/  dst_ip; int /*<<< orphan*/  src_ip; } ;
struct mlx4_spec_list {int /*<<< orphan*/  list; TYPE_7__ tcp_udp; TYPE_6__ ipv4; int /*<<< orphan*/  id; } ;
struct mlx4_en_priv {int dummy; } ;
struct list_head {int dummy; } ;
struct ethtool_tcpip4_spec {scalar_t__ pdst; scalar_t__ psrc; scalar_t__ ip4dst; scalar_t__ ip4src; } ;
struct TYPE_10__ {int /*<<< orphan*/  pdst; int /*<<< orphan*/  psrc; int /*<<< orphan*/  ip4dst; int /*<<< orphan*/  ip4src; } ;
struct TYPE_9__ {int /*<<< orphan*/  pdst; int /*<<< orphan*/  psrc; int /*<<< orphan*/  ip4dst; int /*<<< orphan*/  ip4src; } ;
struct TYPE_11__ {TYPE_3__ udp_ip4_spec; TYPE_2__ tcp_ip4_spec; } ;
struct TYPE_8__ {struct ethtool_tcpip4_spec tcp_ip4_spec; } ;
struct TYPE_12__ {TYPE_4__ h_u; TYPE_1__ m_u; } ;
struct ethtool_rxnfc {TYPE_5__ fs; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* EN_ETHTOOL_SHORT_MASK ; 
 void* EN_ETHTOOL_WORD_MASK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MLX4_NET_TRANS_RULE_ID_IPV4 ; 
 int /*<<< orphan*/  MLX4_NET_TRANS_RULE_ID_TCP ; 
 int /*<<< orphan*/  MLX4_NET_TRANS_RULE_ID_UDP ; 
 int TCP_V4_FLOW ; 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*) ; 
 int /*<<< orphan*/  kfree (struct mlx4_spec_list*) ; 
 struct mlx4_spec_list* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int mlx4_en_ethtool_add_mac_rule_by_ipv4 (struct mlx4_en_priv*,struct ethtool_rxnfc*,struct list_head*,struct mlx4_spec_list*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_tcp_udp_rule(struct mlx4_en_priv *priv,
			     struct ethtool_rxnfc *cmd,
			     struct list_head *list_h, int proto)
{
	int err;
	struct mlx4_spec_list *spec_l2 = NULL;
	struct mlx4_spec_list *spec_l3 = NULL;
	struct mlx4_spec_list *spec_l4 = NULL;
	struct ethtool_tcpip4_spec *l4_mask = &cmd->fs.m_u.tcp_ip4_spec;

	spec_l2 = kzalloc(sizeof(*spec_l2), GFP_KERNEL);
	spec_l3 = kzalloc(sizeof(*spec_l3), GFP_KERNEL);
	spec_l4 = kzalloc(sizeof(*spec_l4), GFP_KERNEL);
	if (!spec_l2 || !spec_l3 || !spec_l4) {
		en_err(priv, "Fail to alloc ethtool rule.\n");
		err = -ENOMEM;
		goto free_spec;
	}

	spec_l3->id = MLX4_NET_TRANS_RULE_ID_IPV4;

	if (proto == TCP_V4_FLOW) {
		err = mlx4_en_ethtool_add_mac_rule_by_ipv4(priv, cmd, list_h,
							   spec_l2,
							   cmd->fs.h_u.
							   tcp_ip4_spec.ip4dst);
		if (err)
			goto free_spec;
		spec_l4->id = MLX4_NET_TRANS_RULE_ID_TCP;
		spec_l3->ipv4.src_ip = cmd->fs.h_u.tcp_ip4_spec.ip4src;
		spec_l3->ipv4.dst_ip = cmd->fs.h_u.tcp_ip4_spec.ip4dst;
		spec_l4->tcp_udp.src_port = cmd->fs.h_u.tcp_ip4_spec.psrc;
		spec_l4->tcp_udp.dst_port = cmd->fs.h_u.tcp_ip4_spec.pdst;
	} else {
		err = mlx4_en_ethtool_add_mac_rule_by_ipv4(priv, cmd, list_h,
							   spec_l2,
							   cmd->fs.h_u.
							   udp_ip4_spec.ip4dst);
		if (err)
			goto free_spec;
		spec_l4->id = MLX4_NET_TRANS_RULE_ID_UDP;
		spec_l3->ipv4.src_ip = cmd->fs.h_u.udp_ip4_spec.ip4src;
		spec_l3->ipv4.dst_ip = cmd->fs.h_u.udp_ip4_spec.ip4dst;
		spec_l4->tcp_udp.src_port = cmd->fs.h_u.udp_ip4_spec.psrc;
		spec_l4->tcp_udp.dst_port = cmd->fs.h_u.udp_ip4_spec.pdst;
	}

	if (l4_mask->ip4src)
		spec_l3->ipv4.src_ip_msk = EN_ETHTOOL_WORD_MASK;
	if (l4_mask->ip4dst)
		spec_l3->ipv4.dst_ip_msk = EN_ETHTOOL_WORD_MASK;

	if (l4_mask->psrc)
		spec_l4->tcp_udp.src_port_msk = EN_ETHTOOL_SHORT_MASK;
	if (l4_mask->pdst)
		spec_l4->tcp_udp.dst_port_msk = EN_ETHTOOL_SHORT_MASK;

	list_add_tail(&spec_l3->list, list_h);
	list_add_tail(&spec_l4->list, list_h);

	return 0;

free_spec:
	kfree(spec_l2);
	kfree(spec_l3);
	kfree(spec_l4);
	return err;
}