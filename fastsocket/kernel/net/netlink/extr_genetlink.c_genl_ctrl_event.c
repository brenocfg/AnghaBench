#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct genl_multicast_group {struct genl_family* family; } ;
struct genl_family {int /*<<< orphan*/  netnsok; } ;
struct TYPE_3__ {int /*<<< orphan*/  genl_sock; } ;

/* Variables and functions */
#define  CTRL_CMD_DELFAMILY 131 
#define  CTRL_CMD_DELMCAST_GRP 130 
#define  CTRL_CMD_NEWFAMILY 129 
#define  CTRL_CMD_NEWMCAST_GRP 128 
 int EINVAL ; 
 int /*<<< orphan*/  GENL_ID_CTRL ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 struct sk_buff* ctrl_build_family_msg (struct genl_family*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct sk_buff* ctrl_build_mcgrp_msg (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  genlmsg_multicast_allns (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genlmsg_multicast_netns (TYPE_1__*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ init_net ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int genl_ctrl_event(int event, void *data)
{
	struct sk_buff *msg;
	struct genl_family *family;
	struct genl_multicast_group *grp;

	/* genl is still initialising */
	if (!init_net.genl_sock)
		return 0;

	switch (event) {
	case CTRL_CMD_NEWFAMILY:
	case CTRL_CMD_DELFAMILY:
		family = data;
		msg = ctrl_build_family_msg(family, 0, 0, event);
		break;
	case CTRL_CMD_NEWMCAST_GRP:
	case CTRL_CMD_DELMCAST_GRP:
		grp = data;
		family = grp->family;
		msg = ctrl_build_mcgrp_msg(data, 0, 0, event);
		break;
	default:
		return -EINVAL;
	}

	if (IS_ERR(msg))
		return PTR_ERR(msg);

	if (!family->netnsok) {
		genlmsg_multicast_netns(&init_net, msg, 0,
					GENL_ID_CTRL, GFP_KERNEL);
	} else {
		rcu_read_lock();
		genlmsg_multicast_allns(msg, 0, GENL_ID_CTRL, GFP_ATOMIC);
		rcu_read_unlock();
	}

	return 0;
}