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
struct datapath {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct sk_buff* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct sk_buff* genlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int ovs_dp_cmd_fill_info (struct datapath*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovs_dp_cmd_msg_size () ; 

__attribute__((used)) static struct sk_buff *ovs_dp_cmd_build_info(struct datapath *dp, u32 pid,
					     u32 seq, u8 cmd)
{
	struct sk_buff *skb;
	int retval;

	skb = genlmsg_new(ovs_dp_cmd_msg_size(), GFP_KERNEL);
	if (!skb)
		return ERR_PTR(-ENOMEM);

	retval = ovs_dp_cmd_fill_info(dp, skb, pid, seq, 0, cmd);
	if (retval < 0) {
		kfree_skb(skb);
		return ERR_PTR(retval);
	}
	return skb;
}