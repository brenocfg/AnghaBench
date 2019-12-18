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
struct htc_target {int /*<<< orphan*/  dev; int /*<<< orphan*/  cmd_wait; int /*<<< orphan*/  htc_flags; int /*<<< orphan*/  credits; } ;
struct htc_frame_hdr {int dummy; } ;
struct htc_config_pipe_msg {int /*<<< orphan*/  credits; int /*<<< orphan*/  pipe_id; int /*<<< orphan*/  message_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ENDPOINT0 ; 
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  HTC_MSG_CONFIG_PIPE_ID ; 
 int /*<<< orphan*/  HTC_OP_CONFIG_PIPE_CREDITS ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  USB_WLAN_TX_PIPE ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int htc_issue_send (struct htc_target*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int htc_config_pipe_credits(struct htc_target *target)
{
	struct sk_buff *skb;
	struct htc_config_pipe_msg *cp_msg;
	int ret, time_left;

	skb = alloc_skb(50 + sizeof(struct htc_frame_hdr), GFP_ATOMIC);
	if (!skb) {
		dev_err(target->dev, "failed to allocate send buffer\n");
		return -ENOMEM;
	}
	skb_reserve(skb, sizeof(struct htc_frame_hdr));

	cp_msg = (struct htc_config_pipe_msg *)
		skb_put(skb, sizeof(struct htc_config_pipe_msg));

	cp_msg->message_id = cpu_to_be16(HTC_MSG_CONFIG_PIPE_ID);
	cp_msg->pipe_id = USB_WLAN_TX_PIPE;
	cp_msg->credits = target->credits;

	target->htc_flags |= HTC_OP_CONFIG_PIPE_CREDITS;

	ret = htc_issue_send(target, skb, skb->len, 0, ENDPOINT0);
	if (ret)
		goto err;

	time_left = wait_for_completion_timeout(&target->cmd_wait, HZ);
	if (!time_left) {
		dev_err(target->dev, "HTC credit config timeout\n");
		return -ETIMEDOUT;
	}

	return 0;
err:
	kfree_skb(skb);
	return -EINVAL;
}