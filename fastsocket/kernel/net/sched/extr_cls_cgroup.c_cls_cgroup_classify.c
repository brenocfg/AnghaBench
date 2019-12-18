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
typedef  scalar_t__ u32 ;
struct tcf_result {scalar_t__ class; scalar_t__ classid; } ;
struct tcf_proto {struct cls_cgroup_head* root; } ;
struct sk_buff {TYPE_1__* sk; } ;
struct cls_cgroup_head {int /*<<< orphan*/  exts; int /*<<< orphan*/  ematches; } ;
struct TYPE_4__ {scalar_t__ classid; } ;
struct TYPE_3__ {scalar_t__ sk_classid; } ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 scalar_t__ in_serving_softirq () ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 TYPE_2__* task_cls_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_em_tree_match (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int tcf_exts_exec (struct sk_buff*,int /*<<< orphan*/ *,struct tcf_result*) ; 

__attribute__((used)) static int cls_cgroup_classify(struct sk_buff *skb, struct tcf_proto *tp,
			       struct tcf_result *res)
{
	struct cls_cgroup_head *head = tp->root;
	u32 classid;

	rcu_read_lock();
	classid = task_cls_state(current)->classid;
	rcu_read_unlock();

	/*
	 * Due to the nature of the classifier it is required to ignore all
	 * packets originating from softirq context as accessing `current'
	 * would lead to false results.
	 *
	 * This test assumes that all callers of dev_queue_xmit() explicitely
	 * disable bh. Knowing this, it is possible to detect softirq based
	 * calls by looking at the number of nested bh disable calls because
	 * softirqs always disables bh.
	 */
	if (in_serving_softirq()) {
		/* If there is an sk_classid we'll use that. */
		if (!skb->sk)
			return -1;
		classid = skb->sk->sk_classid;
	}

	if (!classid)
		return -1;

	if (!tcf_em_tree_match(skb, &head->ematches, NULL))
		return -1;

	res->classid = classid;
	res->class = 0;
	return tcf_exts_exec(skb, &head->exts, res);
}