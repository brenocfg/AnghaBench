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
struct tc_action {int order; struct tc_action* next; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 struct tc_action* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct tc_action*) ; 
 int TCA_ACT_MAX_PRIO ; 
 int nla_parse_nested (struct nlattr**,int,struct nlattr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_action_destroy (struct tc_action*,int) ; 
 struct tc_action* tcf_action_init_1 (struct nlattr*,struct nlattr*,char*,int,int) ; 

struct tc_action *tcf_action_init(struct nlattr *nla, struct nlattr *est,
				  char *name, int ovr, int bind)
{
	struct nlattr *tb[TCA_ACT_MAX_PRIO+1];
	struct tc_action *head = NULL, *act, *act_prev = NULL;
	int err;
	int i;

	err = nla_parse_nested(tb, TCA_ACT_MAX_PRIO, nla, NULL);
	if (err < 0)
		return ERR_PTR(err);

	for (i = 1; i <= TCA_ACT_MAX_PRIO && tb[i]; i++) {
		act = tcf_action_init_1(tb[i], est, name, ovr, bind);
		if (IS_ERR(act))
			goto err;
		act->order = i;

		if (head == NULL)
			head = act;
		else
			act_prev->next = act;
		act_prev = act;
	}
	return head;

err:
	if (head != NULL)
		tcf_action_destroy(head, bind);
	return act;
}