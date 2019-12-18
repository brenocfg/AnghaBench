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
struct tcf_result {int dummy; } ;
struct tc_action {struct tc_action* next; TYPE_1__* ops; } ;
struct sk_buff {int tc_verd; } ;
struct TYPE_2__ {int (* act ) (struct sk_buff*,struct tc_action*,struct tcf_result*) ;} ;

/* Variables and functions */
 int CLR_TC_MUNGED (int) ; 
 int CLR_TC_NCLS (int) ; 
 int SET_TC_OK2MUNGE (int) ; 
 int TC_ACT_OK ; 
 int TC_ACT_PIPE ; 
 int TC_ACT_REPEAT ; 
 int TC_MUNGED ; 
 int TC_NCLS ; 
 int stub1 (struct sk_buff*,struct tc_action*,struct tcf_result*) ; 

int tcf_action_exec(struct sk_buff *skb, struct tc_action *act,
		    struct tcf_result *res)
{
	struct tc_action *a;
	int ret = -1;

	if (skb->tc_verd & TC_NCLS) {
		skb->tc_verd = CLR_TC_NCLS(skb->tc_verd);
		ret = TC_ACT_OK;
		goto exec_done;
	}
	while ((a = act) != NULL) {
repeat:
		if (a->ops && a->ops->act) {
			ret = a->ops->act(skb, a, res);
			if (TC_MUNGED & skb->tc_verd) {
				/* copied already, allow trampling */
				skb->tc_verd = SET_TC_OK2MUNGE(skb->tc_verd);
				skb->tc_verd = CLR_TC_MUNGED(skb->tc_verd);
			}
			if (ret == TC_ACT_REPEAT)
				goto repeat;	/* we need a ttl - JHS */
			if (ret != TC_ACT_PIPE)
				goto exec_done;
		}
		act = a->next;
	}
exec_done:
	return ret;
}