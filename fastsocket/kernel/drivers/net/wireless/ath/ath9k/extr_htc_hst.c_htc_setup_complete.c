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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct htc_target {int /*<<< orphan*/  dev; int /*<<< orphan*/  cmd_wait; int /*<<< orphan*/  htc_flags; } ;
struct htc_frame_hdr {int dummy; } ;
struct htc_comp_msg {int /*<<< orphan*/  msg_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ENDPOINT0 ; 
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  HTC_MSG_SETUP_COMPLETE_ID ; 
 int /*<<< orphan*/  HTC_OP_START_WAIT ; 
 int /*<<< orphan*/  HZ ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int htc_issue_send (struct htc_target*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int htc_setup_complete(struct htc_target *target)
{
	struct sk_buff *skb;
	struct htc_comp_msg *comp_msg;
	int ret = 0, time_left;

	skb = alloc_skb(50 + sizeof(struct htc_frame_hdr), GFP_ATOMIC);
	if (!skb) {
		dev_err(target->dev, "failed to allocate send buffer\n");
		return -ENOMEM;
	}
	skb_reserve(skb, sizeof(struct htc_frame_hdr));

	comp_msg = (struct htc_comp_msg *)
		skb_put(skb, sizeof(struct htc_comp_msg));
	comp_msg->msg_id = cpu_to_be16(HTC_MSG_SETUP_COMPLETE_ID);

	target->htc_flags |= HTC_OP_START_WAIT;

	ret = htc_issue_send(target, skb, skb->len, 0, ENDPOINT0);
	if (ret)
		goto err;

	time_left = wait_for_completion_timeout(&target->cmd_wait, HZ);
	if (!time_left) {
		dev_err(target->dev, "HTC start timeout\n");
		return -ETIMEDOUT;
	}

	return 0;

err:
	kfree_skb(skb);
	return -EINVAL;
}