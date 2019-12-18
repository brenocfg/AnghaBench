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
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct genl_multicast_group {int /*<<< orphan*/  name; int /*<<< orphan*/  id; TYPE_1__* family; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_ATTR_FAMILY_ID ; 
 int /*<<< orphan*/  CTRL_ATTR_FAMILY_NAME ; 
 int CTRL_ATTR_MCAST_GROUPS ; 
 int /*<<< orphan*/  CTRL_ATTR_MCAST_GRP_ID ; 
 int /*<<< orphan*/  CTRL_ATTR_MCAST_GRP_NAME ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  NLA_PUT_STRING (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLA_PUT_U16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLA_PUT_U32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genl_ctrl ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int) ; 

__attribute__((used)) static int ctrl_fill_mcgrp_info(struct genl_multicast_group *grp, u32 pid,
				u32 seq, u32 flags, struct sk_buff *skb,
				u8 cmd)
{
	void *hdr;
	struct nlattr *nla_grps;
	struct nlattr *nest;

	hdr = genlmsg_put(skb, pid, seq, &genl_ctrl, flags, cmd);
	if (hdr == NULL)
		return -1;

	NLA_PUT_STRING(skb, CTRL_ATTR_FAMILY_NAME, grp->family->name);
	NLA_PUT_U16(skb, CTRL_ATTR_FAMILY_ID, grp->family->id);

	nla_grps = nla_nest_start(skb, CTRL_ATTR_MCAST_GROUPS);
	if (nla_grps == NULL)
		goto nla_put_failure;

	nest = nla_nest_start(skb, 1);
	if (nest == NULL)
		goto nla_put_failure;

	NLA_PUT_U32(skb, CTRL_ATTR_MCAST_GRP_ID, grp->id);
	NLA_PUT_STRING(skb, CTRL_ATTR_MCAST_GRP_NAME,
		       grp->name);

	nla_nest_end(skb, nest);
	nla_nest_end(skb, nla_grps);

	return genlmsg_end(skb, hdr);

nla_put_failure:
	genlmsg_cancel(skb, hdr);
	return -EMSGSIZE;
}