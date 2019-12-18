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
typedef  int /*<<< orphan*/  u32 ;
struct tc_action {struct tc_action* next; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_flags; int /*<<< orphan*/  nlmsg_seq; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct tc_action*) ; 
 int PTR_ERR (struct tc_action*) ; 
 int /*<<< orphan*/  RTM_NEWACTION ; 
 int /*<<< orphan*/  kfree (struct tc_action*) ; 
 struct tc_action* tcf_action_init (struct nlattr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int tcf_add_notify (struct tc_action*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tcf_action_add(struct nlattr *nla, struct nlmsghdr *n, u32 pid, int ovr)
{
	int ret = 0;
	struct tc_action *act;
	struct tc_action *a;
	u32 seq = n->nlmsg_seq;

	act = tcf_action_init(nla, NULL, NULL, ovr, 0);
	if (act == NULL)
		goto done;
	if (IS_ERR(act)) {
		ret = PTR_ERR(act);
		goto done;
	}

	/* dump then free all the actions after update; inserted policy
	 * stays intact
	 * */
	ret = tcf_add_notify(act, pid, seq, RTM_NEWACTION, n->nlmsg_flags);
	for (a = act; a; a = act) {
		act = a->next;
		kfree(a);
	}
done:
	return ret;
}