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
struct sk_buff {int dummy; } ;
struct genl_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NLBL_UNLABEL_A_ACPTFLG ; 
 int /*<<< orphan*/  NLBL_UNLABEL_C_LIST ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put_reply (struct sk_buff*,struct genl_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netlabel_unlabel_acceptflg ; 
 int /*<<< orphan*/  netlbl_unlabel_gnl_family ; 
 int nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netlbl_unlabel_list(struct sk_buff *skb, struct genl_info *info)
{
	int ret_val = -EINVAL;
	struct sk_buff *ans_skb;
	void *data;

	ans_skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (ans_skb == NULL)
		goto list_failure;
	data = genlmsg_put_reply(ans_skb, info, &netlbl_unlabel_gnl_family,
				 0, NLBL_UNLABEL_C_LIST);
	if (data == NULL) {
		ret_val = -ENOMEM;
		goto list_failure;
	}

	ret_val = nla_put_u8(ans_skb,
			     NLBL_UNLABEL_A_ACPTFLG,
			     netlabel_unlabel_acceptflg);
	if (ret_val != 0)
		goto list_failure;

	genlmsg_end(ans_skb, data);
	return genlmsg_reply(ans_skb, info);

list_failure:
	kfree_skb(ans_skb);
	return ret_val;
}