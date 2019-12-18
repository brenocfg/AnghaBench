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
struct tcf_proto {struct cls_cgroup_head* root; } ;
struct cls_cgroup_head {int /*<<< orphan*/  ematches; int /*<<< orphan*/  exts; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct cls_cgroup_head*) ; 
 int /*<<< orphan*/  tcf_em_tree_destroy (struct tcf_proto*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_exts_destroy (struct tcf_proto*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cls_cgroup_destroy(struct tcf_proto *tp)
{
	struct cls_cgroup_head *head = tp->root;

	if (head) {
		tcf_exts_destroy(tp, &head->exts);
		tcf_em_tree_destroy(tp, &head->ematches);
		kfree(head);
	}
}