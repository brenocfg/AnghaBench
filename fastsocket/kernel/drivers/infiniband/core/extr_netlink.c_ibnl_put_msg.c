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
struct nlmsghdr {int nlmsg_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int /*<<< orphan*/  RDMA_NL_GET_TYPE (int,int) ; 
 void* nlmsg_data (struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,unsigned char*) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 

void *ibnl_put_msg(struct sk_buff *skb, struct nlmsghdr **nlh, int seq,
		   int len, int client, int op)
{
	unsigned char *prev_tail;

	prev_tail = skb_tail_pointer(skb);
	*nlh = nlmsg_put(skb, 0, seq, RDMA_NL_GET_TYPE(client, op),
			 len, NLM_F_MULTI);
	if (!*nlh)
		goto out_nlmsg_trim;
	(*nlh)->nlmsg_len = skb_tail_pointer(skb) - prev_tail;
	return nlmsg_data(*nlh);

out_nlmsg_trim:
	nlmsg_trim(skb, prev_tail);
	return NULL;
}