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
 int EMSGSIZE ; 
 scalar_t__ nla_put (struct sk_buff*,int,int,void*) ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,unsigned char*) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 

int ibnl_put_attr(struct sk_buff *skb, struct nlmsghdr *nlh,
		  int len, void *data, int type)
{
	unsigned char *prev_tail;

	prev_tail = skb_tail_pointer(skb);
	if (nla_put(skb, type, len, data))
		goto nla_put_failure;
	nlh->nlmsg_len += skb_tail_pointer(skb) - prev_tail;
	return 0;

nla_put_failure:
	nlmsg_trim(skb, prev_tail - nlh->nlmsg_len);
	return -EMSGSIZE;
}