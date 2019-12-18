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
struct nlattr {scalar_t__ nla_type; } ;
struct net_device {TYPE_1__* dcbnl_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* setpfccfg ) (struct net_device*,scalar_t__,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 size_t DCB_ATTR_PFC_CFG ; 
 int /*<<< orphan*/  DCB_CMD_PFC_SCFG ; 
 int DCB_PFC_UP_ATTR_0 ; 
 int DCB_PFC_UP_ATTR_7 ; 
 int /*<<< orphan*/  DCB_PFC_UP_ATTR_MAX ; 
 int EINVAL ; 
 int /*<<< orphan*/  RTM_SETDCB ; 
 int /*<<< orphan*/  dcbnl_pfc_up_nest ; 
 int dcbnl_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_u8 (struct nlattr*) ; 
 int nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dcbnl_setpfccfg(struct net_device *netdev, struct nlattr **tb,
                           u32 pid, u32 seq, u16 flags)
{
	struct nlattr *data[DCB_PFC_UP_ATTR_MAX + 1];
	int i;
	int ret = -EINVAL;
	u8 value;

	if (!tb[DCB_ATTR_PFC_CFG] || !netdev->dcbnl_ops->setpfccfg)
		return ret;

	ret = nla_parse_nested(data, DCB_PFC_UP_ATTR_MAX,
	                       tb[DCB_ATTR_PFC_CFG],
	                       dcbnl_pfc_up_nest);
	if (ret)
		goto err;

	for (i = DCB_PFC_UP_ATTR_0; i <= DCB_PFC_UP_ATTR_7; i++) {
		if (data[i] == NULL)
			continue;
		value = nla_get_u8(data[i]);
		netdev->dcbnl_ops->setpfccfg(netdev,
			data[i]->nla_type - DCB_PFC_UP_ATTR_0, value);
	}

	ret = dcbnl_reply(0, RTM_SETDCB, DCB_CMD_PFC_SCFG, DCB_ATTR_PFC_CFG,
	                  pid, seq, flags);
err:
	return ret;
}