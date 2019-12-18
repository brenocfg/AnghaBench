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
struct TYPE_2__ {int /*<<< orphan*/  (* setdcbx ) (struct net_device*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 size_t DCB_ATTR_DCBX ; 
 int /*<<< orphan*/  DCB_CMD_SDCBX ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  RTM_SETDCB ; 
 int dcbnl_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_get_u8 (struct nlattr*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dcbnl_setdcbx(struct net_device *netdev, struct nlattr **tb,
			 u32 pid, u32 seq, u16 flags)
{
	int ret;
	u8 value;

	if (!netdev->dcbnl_ops->setdcbx)
		return -EOPNOTSUPP;

	if (!tb[DCB_ATTR_DCBX])
		return -EINVAL;

	value = nla_get_u8(tb[DCB_ATTR_DCBX]);

	ret = dcbnl_reply(netdev->dcbnl_ops->setdcbx(netdev, value),
			  RTM_SETDCB, DCB_CMD_SDCBX, DCB_ATTR_DCBX,
			  pid, seq, flags);

	return ret;
}