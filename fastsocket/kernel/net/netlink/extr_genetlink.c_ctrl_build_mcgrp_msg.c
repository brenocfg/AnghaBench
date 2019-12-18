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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct genl_multicast_group {int dummy; } ;

/* Variables and functions */
 int ENOBUFS ; 
 struct sk_buff* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int ctrl_fill_mcgrp_info (struct genl_multicast_group*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *ctrl_build_mcgrp_msg(struct genl_multicast_group *grp,
					    u32 pid, int seq, u8 cmd)
{
	struct sk_buff *skb;
	int err;

	skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (skb == NULL)
		return ERR_PTR(-ENOBUFS);

	err = ctrl_fill_mcgrp_info(grp, pid, seq, 0, skb, cmd);
	if (err < 0) {
		nlmsg_free(skb);
		return ERR_PTR(err);
	}

	return skb;
}