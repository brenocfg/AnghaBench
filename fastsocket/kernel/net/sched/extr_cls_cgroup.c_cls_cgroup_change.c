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
typedef  scalar_t__ u32 ;
struct tcf_proto {struct cls_cgroup_head* root; } ;
struct tcf_exts {int dummy; } ;
struct tcf_ematch_tree {int dummy; } ;
struct nlattr {int dummy; } ;
struct cls_cgroup_head {scalar_t__ handle; int /*<<< orphan*/  ematches; int /*<<< orphan*/  exts; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 int ENOENT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t TCA_CGROUP_EMATCHES ; 
 int /*<<< orphan*/  TCA_CGROUP_MAX ; 
 size_t TCA_OPTIONS ; 
 size_t TCA_RATE ; 
 int /*<<< orphan*/  cgroup_ext_map ; 
 int /*<<< orphan*/  cgroup_policy ; 
 struct cls_cgroup_head* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_em_tree_change (struct tcf_proto*,int /*<<< orphan*/ *,struct tcf_ematch_tree*) ; 
 int tcf_em_tree_validate (struct tcf_proto*,struct nlattr*,struct tcf_ematch_tree*) ; 
 int /*<<< orphan*/  tcf_exts_change (struct tcf_proto*,int /*<<< orphan*/ *,struct tcf_exts*) ; 
 int tcf_exts_validate (struct tcf_proto*,struct nlattr**,struct nlattr*,struct tcf_exts*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_tree_lock (struct tcf_proto*) ; 
 int /*<<< orphan*/  tcf_tree_unlock (struct tcf_proto*) ; 

__attribute__((used)) static int cls_cgroup_change(struct tcf_proto *tp, unsigned long base,
			     u32 handle, struct nlattr **tca,
			     unsigned long *arg)
{
	struct nlattr *tb[TCA_CGROUP_MAX+1];
	struct cls_cgroup_head *head = tp->root;
	struct tcf_ematch_tree t;
	struct tcf_exts e;
	int err;

	if (!tca[TCA_OPTIONS])
		return -EINVAL;

	if (head == NULL) {
		if (!handle)
			return -EINVAL;

		head = kzalloc(sizeof(*head), GFP_KERNEL);
		if (head == NULL)
			return -ENOBUFS;

		head->handle = handle;

		tcf_tree_lock(tp);
		tp->root = head;
		tcf_tree_unlock(tp);
	}

	if (handle != head->handle)
		return -ENOENT;

	err = nla_parse_nested(tb, TCA_CGROUP_MAX, tca[TCA_OPTIONS],
			       cgroup_policy);
	if (err < 0)
		return err;

	err = tcf_exts_validate(tp, tb, tca[TCA_RATE], &e, &cgroup_ext_map);
	if (err < 0)
		return err;

	err = tcf_em_tree_validate(tp, tb[TCA_CGROUP_EMATCHES], &t);
	if (err < 0)
		return err;

	tcf_exts_change(tp, &head->exts, &e);
	tcf_em_tree_change(tp, &head->ematches, &t);

	return 0;
}