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
struct nlattr {int dummy; } ;
struct net_device {TYPE_1__* dcbnl_ops; } ;
struct TYPE_2__ {int (* setfeatcfg ) (struct net_device*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 size_t DCB_ATTR_FEATCFG ; 
 int /*<<< orphan*/  DCB_CMD_SFEATCFG ; 
 int DCB_FEATCFG_ATTR_ALL ; 
 int DCB_FEATCFG_ATTR_MAX ; 
 int EINVAL ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  RTM_SETDCB ; 
 int /*<<< orphan*/  dcbnl_featcfg_nest ; 
 int /*<<< orphan*/  dcbnl_reply (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_u8 (struct nlattr*) ; 
 int nla_parse_nested (struct nlattr**,int,struct nlattr*,int /*<<< orphan*/ ) ; 
 int stub1 (struct net_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dcbnl_setfeatcfg(struct net_device *netdev, struct nlattr **tb,
			    u32 pid, u32 seq, u16 flags)
{
	struct nlattr *data[DCB_FEATCFG_ATTR_MAX + 1];
	int ret, i;
	u8 value;

	if (!netdev->dcbnl_ops->setfeatcfg)
		return -ENOTSUPP;

	if (!tb[DCB_ATTR_FEATCFG])
		return -EINVAL;

	ret = nla_parse_nested(data, DCB_FEATCFG_ATTR_MAX, tb[DCB_ATTR_FEATCFG],
			       dcbnl_featcfg_nest);

	if (ret)
		goto err;

	for (i = DCB_FEATCFG_ATTR_ALL+1; i <= DCB_FEATCFG_ATTR_MAX; i++) {
		if (data[i] == NULL)
			continue;

		value = nla_get_u8(data[i]);

		ret = netdev->dcbnl_ops->setfeatcfg(netdev, i, value);

		if (ret)
			goto err;
	}
err:
	dcbnl_reply(ret, RTM_SETDCB, DCB_CMD_SFEATCFG, DCB_ATTR_FEATCFG,
		    pid, seq, flags);

	return ret;
}