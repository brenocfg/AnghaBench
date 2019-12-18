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
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  dlm_nl_seqnum ; 
 int /*<<< orphan*/  family ; 
 struct sk_buff* genlmsg_new (size_t,int /*<<< orphan*/ ) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 

__attribute__((used)) static int prepare_data(u8 cmd, struct sk_buff **skbp, size_t size)
{
	struct sk_buff *skb;
	void *data;

	skb = genlmsg_new(size, GFP_NOFS);
	if (!skb)
		return -ENOMEM;

	/* add the message headers */
	data = genlmsg_put(skb, 0, dlm_nl_seqnum++, &family, 0, cmd);
	if (!data) {
		nlmsg_free(skb);
		return -EINVAL;
	}

	*skbp = skb;
	return 0;
}