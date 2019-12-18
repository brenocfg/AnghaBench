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
struct tcf_proto {int dummy; } ;
struct tcf_exts {struct tc_action* action; } ;
struct tc_action {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCA_ACT_UNBIND ; 
 int /*<<< orphan*/  tcf_action_destroy (struct tc_action*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_tree_lock (struct tcf_proto*) ; 
 int /*<<< orphan*/  tcf_tree_unlock (struct tcf_proto*) ; 

void tcf_exts_change(struct tcf_proto *tp, struct tcf_exts *dst,
		     struct tcf_exts *src)
{
#ifdef CONFIG_NET_CLS_ACT
	if (src->action) {
		struct tc_action *act;
		tcf_tree_lock(tp);
		act = dst->action;
		dst->action = src->action;
		tcf_tree_unlock(tp);
		if (act)
			tcf_action_destroy(act, TCA_ACT_UNBIND);
	}
#endif
}