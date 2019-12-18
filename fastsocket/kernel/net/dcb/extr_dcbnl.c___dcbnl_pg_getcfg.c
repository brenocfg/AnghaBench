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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct net_device {TYPE_1__* dcbnl_ops; } ;
struct dcbmsg {int /*<<< orphan*/  cmd; int /*<<< orphan*/  dcb_family; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* getpgbwgcfgtx ) (struct net_device*,int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* getpgbwgcfgrx ) (struct net_device*,int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* getpgtccfgtx ) (struct net_device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* getpgtccfgrx ) (struct net_device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 size_t DCB_ATTR_PG_CFG ; 
 int /*<<< orphan*/  DCB_ATTR_VALUE_UNDEFINED ; 
 int /*<<< orphan*/  DCB_CMD_PGRX_GCFG ; 
 int /*<<< orphan*/  DCB_CMD_PGTX_GCFG ; 
 int DCB_PG_ATTR_BW_ID_0 ; 
 int DCB_PG_ATTR_BW_ID_7 ; 
 size_t DCB_PG_ATTR_BW_ID_ALL ; 
 int /*<<< orphan*/  DCB_PG_ATTR_MAX ; 
 int DCB_PG_ATTR_TC_0 ; 
 int DCB_PG_ATTR_TC_7 ; 
 size_t DCB_PG_ATTR_TC_ALL ; 
 size_t DCB_TC_ATTR_PARAM_ALL ; 
 size_t DCB_TC_ATTR_PARAM_BW_PCT ; 
 int /*<<< orphan*/  DCB_TC_ATTR_PARAM_MAX ; 
 size_t DCB_TC_ATTR_PARAM_PGID ; 
 size_t DCB_TC_ATTR_PARAM_STRICT_PRIO ; 
 size_t DCB_TC_ATTR_PARAM_UP_MAPPING ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct dcbmsg* NLMSG_DATA (struct nlmsghdr*) ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 struct nlmsghdr* NLMSG_NEW (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTM_GETDCB ; 
 int /*<<< orphan*/  dcbnl_pg_nest ; 
 int /*<<< orphan*/  dcbnl_tc_param_nest ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int) ; 
 int nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ) ; 
 int nla_put_u8 (struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rtnl_unicast (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct net_device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (struct net_device*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (struct net_device*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __dcbnl_pg_getcfg(struct net_device *netdev, struct nlattr **tb,
                             u32 pid, u32 seq, u16 flags, int dir)
{
	struct sk_buff *dcbnl_skb;
	struct nlmsghdr *nlh;
	struct dcbmsg *dcb;
	struct nlattr *pg_nest, *param_nest, *data;
	struct nlattr *pg_tb[DCB_PG_ATTR_MAX + 1];
	struct nlattr *param_tb[DCB_TC_ATTR_PARAM_MAX + 1];
	u8 prio, pgid, tc_pct, up_map;
	int ret  = -EINVAL;
	int getall = 0;
	int i;

	if (!tb[DCB_ATTR_PG_CFG] ||
	    !netdev->dcbnl_ops->getpgtccfgtx ||
	    !netdev->dcbnl_ops->getpgtccfgrx ||
	    !netdev->dcbnl_ops->getpgbwgcfgtx ||
	    !netdev->dcbnl_ops->getpgbwgcfgrx)
		return ret;

	ret = nla_parse_nested(pg_tb, DCB_PG_ATTR_MAX,
	                       tb[DCB_ATTR_PG_CFG], dcbnl_pg_nest);

	if (ret)
		goto err_out;

	dcbnl_skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!dcbnl_skb)
		goto err_out;

	nlh = NLMSG_NEW(dcbnl_skb, pid, seq, RTM_GETDCB, sizeof(*dcb), flags);

	dcb = NLMSG_DATA(nlh);
	dcb->dcb_family = AF_UNSPEC;
	dcb->cmd = (dir) ? DCB_CMD_PGRX_GCFG : DCB_CMD_PGTX_GCFG;

	pg_nest = nla_nest_start(dcbnl_skb, DCB_ATTR_PG_CFG);
	if (!pg_nest)
		goto err;

	if (pg_tb[DCB_PG_ATTR_TC_ALL])
		getall = 1;

	for (i = DCB_PG_ATTR_TC_0; i <= DCB_PG_ATTR_TC_7; i++) {
		if (!getall && !pg_tb[i])
			continue;

		if (pg_tb[DCB_PG_ATTR_TC_ALL])
			data = pg_tb[DCB_PG_ATTR_TC_ALL];
		else
			data = pg_tb[i];
		ret = nla_parse_nested(param_tb, DCB_TC_ATTR_PARAM_MAX,
				       data, dcbnl_tc_param_nest);
		if (ret)
			goto err_pg;

		param_nest = nla_nest_start(dcbnl_skb, i);
		if (!param_nest)
			goto err_pg;

		pgid = DCB_ATTR_VALUE_UNDEFINED;
		prio = DCB_ATTR_VALUE_UNDEFINED;
		tc_pct = DCB_ATTR_VALUE_UNDEFINED;
		up_map = DCB_ATTR_VALUE_UNDEFINED;

		if (dir) {
			/* Rx */
			netdev->dcbnl_ops->getpgtccfgrx(netdev,
						i - DCB_PG_ATTR_TC_0, &prio,
						&pgid, &tc_pct, &up_map);
		} else {
			/* Tx */
			netdev->dcbnl_ops->getpgtccfgtx(netdev,
						i - DCB_PG_ATTR_TC_0, &prio,
						&pgid, &tc_pct, &up_map);
		}

		if (param_tb[DCB_TC_ATTR_PARAM_PGID] ||
		    param_tb[DCB_TC_ATTR_PARAM_ALL]) {
			ret = nla_put_u8(dcbnl_skb,
			                 DCB_TC_ATTR_PARAM_PGID, pgid);
			if (ret)
				goto err_param;
		}
		if (param_tb[DCB_TC_ATTR_PARAM_UP_MAPPING] ||
		    param_tb[DCB_TC_ATTR_PARAM_ALL]) {
			ret = nla_put_u8(dcbnl_skb,
			                 DCB_TC_ATTR_PARAM_UP_MAPPING, up_map);
			if (ret)
				goto err_param;
		}
		if (param_tb[DCB_TC_ATTR_PARAM_STRICT_PRIO] ||
		    param_tb[DCB_TC_ATTR_PARAM_ALL]) {
			ret = nla_put_u8(dcbnl_skb,
			                 DCB_TC_ATTR_PARAM_STRICT_PRIO, prio);
			if (ret)
				goto err_param;
		}
		if (param_tb[DCB_TC_ATTR_PARAM_BW_PCT] ||
		    param_tb[DCB_TC_ATTR_PARAM_ALL]) {
			ret = nla_put_u8(dcbnl_skb, DCB_TC_ATTR_PARAM_BW_PCT,
			                 tc_pct);
			if (ret)
				goto err_param;
		}
		nla_nest_end(dcbnl_skb, param_nest);
	}

	if (pg_tb[DCB_PG_ATTR_BW_ID_ALL])
		getall = 1;
	else
		getall = 0;

	for (i = DCB_PG_ATTR_BW_ID_0; i <= DCB_PG_ATTR_BW_ID_7; i++) {
		if (!getall && !pg_tb[i])
			continue;

		tc_pct = DCB_ATTR_VALUE_UNDEFINED;

		if (dir) {
			/* Rx */
			netdev->dcbnl_ops->getpgbwgcfgrx(netdev,
					i - DCB_PG_ATTR_BW_ID_0, &tc_pct);
		} else {
			/* Tx */
			netdev->dcbnl_ops->getpgbwgcfgtx(netdev,
					i - DCB_PG_ATTR_BW_ID_0, &tc_pct);
		}
		ret = nla_put_u8(dcbnl_skb, i, tc_pct);

		if (ret)
			goto err_pg;
	}

	nla_nest_end(dcbnl_skb, pg_nest);

	nlmsg_end(dcbnl_skb, nlh);

	ret = rtnl_unicast(dcbnl_skb, &init_net, pid);
	if (ret)
		goto err_out;

	return 0;

err_param:
	nla_nest_cancel(dcbnl_skb, param_nest);
err_pg:
	nla_nest_cancel(dcbnl_skb, pg_nest);
nlmsg_failure:
err:
	kfree_skb(dcbnl_skb);
err_out:
	ret  = -EINVAL;
	return ret;
}