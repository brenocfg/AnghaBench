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
struct nlmsghdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* NLMSG_DATA (struct nlmsghdr*) ; 
 int NLMSG_DONE ; 
 struct nlmsghdr* NLMSG_NEW (struct sk_buff*,int,int,int,int,int) ; 
 int NLM_F_MULTI ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 struct sk_buff* nlmsg_new (int,int /*<<< orphan*/ ) ; 

struct sk_buff *audit_make_reply(int pid, int seq, int type, int done,
				 int multi, void *payload, int size)
{
	struct sk_buff	*skb;
	struct nlmsghdr	*nlh;
	void		*data;
	int		flags = multi ? NLM_F_MULTI : 0;
	int		t     = done  ? NLMSG_DONE  : type;

	skb = nlmsg_new(size, GFP_KERNEL);
	if (!skb)
		return NULL;

	nlh	= NLMSG_NEW(skb, pid, seq, t, size, flags);
	data	= NLMSG_DATA(nlh);
	memcpy(data, payload, size);
	return skb;

nlmsg_failure:			/* Used by NLMSG_NEW */
	if (skb)
		kfree_skb(skb);
	return NULL;
}