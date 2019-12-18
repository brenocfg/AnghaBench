#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; TYPE_1__* ops; int /*<<< orphan*/  xfrm; } ;
struct TYPE_3__ {int (* local_out ) (struct sk_buff*) ;int /*<<< orphan*/  family; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int /*<<< orphan*/  NF_INET_POST_ROUTING ; 
 int dst_output (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 int nf_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_reset (struct sk_buff*) ; 
 TYPE_2__* skb_dst (struct sk_buff*) ; 
 int stub1 (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xfrm_output2 ; 
 int xfrm_output_one (struct sk_buff*,int) ; 

int xfrm_output_resume(struct sk_buff *skb, int err)
{
	while (likely((err = xfrm_output_one(skb, err)) == 0)) {
		nf_reset(skb);

		err = skb_dst(skb)->ops->local_out(skb);
		if (unlikely(err != 1))
			goto out;

		if (!skb_dst(skb)->xfrm)
			return dst_output(skb);

		err = nf_hook(skb_dst(skb)->ops->family,
			      NF_INET_POST_ROUTING, skb,
			      NULL, skb_dst(skb)->dev, xfrm_output2);
		if (unlikely(err != 1))
			goto out;
	}

	if (err == -EINPROGRESS)
		err = 0;

out:
	return err;
}