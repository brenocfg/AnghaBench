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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct net_device {struct dcbnl_rtnl_ops* dcbnl_ops; } ;
struct dcbnl_rtnl_ops {int /*<<< orphan*/  (* getpgbwgcfgtx ) (struct net_device*,int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* getpgbwgcfgrx ) (struct net_device*,int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* getpgtccfgtx ) (struct net_device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* getpgtccfgrx ) (struct net_device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int DCB_ATTR_CEE_RX_PG ; 
 int DCB_ATTR_CEE_TX_PG ; 
 int /*<<< orphan*/  DCB_ATTR_VALUE_UNDEFINED ; 
 int DCB_PG_ATTR_BW_ID_0 ; 
 int DCB_PG_ATTR_BW_ID_7 ; 
 int DCB_PG_ATTR_TC_0 ; 
 int DCB_PG_ATTR_TC_7 ; 
 int DCB_TC_ATTR_PARAM_BW_PCT ; 
 int DCB_TC_ATTR_PARAM_PGID ; 
 int DCB_TC_ATTR_PARAM_STRICT_PRIO ; 
 int DCB_TC_ATTR_PARAM_UP_MAPPING ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  NLA_PUT_U8 (struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct net_device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (struct net_device*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (struct net_device*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dcbnl_cee_pg_fill(struct sk_buff *skb, struct net_device *dev,
			     int dir)
{
	u8 pgid, up_map, prio, tc_pct;
	const struct dcbnl_rtnl_ops *ops = dev->dcbnl_ops;
	int i = dir ? DCB_ATTR_CEE_TX_PG : DCB_ATTR_CEE_RX_PG;
	struct nlattr *pg = nla_nest_start(skb, i);

	if (!pg)
		goto nla_put_failure;

	for (i = DCB_PG_ATTR_TC_0; i <= DCB_PG_ATTR_TC_7; i++) {
		struct nlattr *tc_nest = nla_nest_start(skb, i);

		if (!tc_nest)
			goto nla_put_failure;

		pgid = DCB_ATTR_VALUE_UNDEFINED;
		prio = DCB_ATTR_VALUE_UNDEFINED;
		tc_pct = DCB_ATTR_VALUE_UNDEFINED;
		up_map = DCB_ATTR_VALUE_UNDEFINED;

		if (!dir)
			ops->getpgtccfgrx(dev, i - DCB_PG_ATTR_TC_0,
					  &prio, &pgid, &tc_pct, &up_map);
		else
			ops->getpgtccfgtx(dev, i - DCB_PG_ATTR_TC_0,
					  &prio, &pgid, &tc_pct, &up_map);

		NLA_PUT_U8(skb, DCB_TC_ATTR_PARAM_PGID, pgid);
		NLA_PUT_U8(skb, DCB_TC_ATTR_PARAM_UP_MAPPING, up_map);
		NLA_PUT_U8(skb, DCB_TC_ATTR_PARAM_STRICT_PRIO, prio);
		NLA_PUT_U8(skb, DCB_TC_ATTR_PARAM_BW_PCT, tc_pct);
		nla_nest_end(skb, tc_nest);
	}

	for (i = DCB_PG_ATTR_BW_ID_0; i <= DCB_PG_ATTR_BW_ID_7; i++) {
		tc_pct = DCB_ATTR_VALUE_UNDEFINED;

		if (!dir)
			ops->getpgbwgcfgrx(dev, i - DCB_PG_ATTR_BW_ID_0,
					   &tc_pct);
		else
			ops->getpgbwgcfgtx(dev, i - DCB_PG_ATTR_BW_ID_0,
					   &tc_pct);
		NLA_PUT_U8(skb, i, tc_pct);
	}
	nla_nest_end(skb, pg);
	return 0;

nla_put_failure:
	return -EMSGSIZE;
}