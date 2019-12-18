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
struct sk_buff {int len; } ;
struct nlmsghdr {int nlmsg_len; } ;
struct cn_msg {int dummy; } ;

/* Variables and functions */
 int CONNECTOR_MAX_MSG_SIZE ; 
 int NLMSG_SPACE (int /*<<< orphan*/ ) ; 
 int cn_call_callback (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct nlmsghdr* nlmsg_hdr (struct sk_buff*) ; 
 struct sk_buff* skb_get (struct sk_buff*) ; 

__attribute__((used)) static void cn_rx_skb(struct sk_buff *__skb)
{
	struct nlmsghdr *nlh;
	int err;
	struct sk_buff *skb;

	skb = skb_get(__skb);

	if (skb->len >= NLMSG_SPACE(0)) {
		nlh = nlmsg_hdr(skb);

		if (nlh->nlmsg_len < sizeof(struct cn_msg) ||
		    skb->len < nlh->nlmsg_len ||
		    nlh->nlmsg_len > CONNECTOR_MAX_MSG_SIZE) {
			kfree_skb(skb);
			return;
		}

		err = cn_call_callback(skb);
		if (err < 0)
			kfree_skb(skb);
	}
}