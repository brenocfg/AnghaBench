#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tc_action {TYPE_1__* ops; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int (* dump ) (struct sk_buff*,struct tc_action*,int,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct sk_buff*,struct tc_action*,int,int) ; 

int
tcf_action_dump_old(struct sk_buff *skb, struct tc_action *a, int bind, int ref)
{
	int err = -EINVAL;

	if (a->ops == NULL || a->ops->dump == NULL)
		return err;
	return a->ops->dump(skb, a, bind, ref);
}