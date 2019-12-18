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
struct tcf_proto {struct fw_head* root; } ;
struct nlattr {int dummy; } ;
struct fw_head {struct fw_filter** ht; scalar_t__ mask; } ;
struct fw_filter {scalar_t__ id; struct fw_filter* next; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t TCA_FW_MASK ; 
 int /*<<< orphan*/  TCA_FW_MAX ; 
 size_t TCA_OPTIONS ; 
 int fw_change_attrs (struct tcf_proto*,struct fw_filter*,struct nlattr**,struct nlattr**,unsigned long) ; 
 size_t fw_hash (scalar_t__) ; 
 int /*<<< orphan*/  fw_policy ; 
 int /*<<< orphan*/  kfree (struct fw_filter*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_get_u32 (struct nlattr*) ; 
 int nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_tree_lock (struct tcf_proto*) ; 
 int /*<<< orphan*/  tcf_tree_unlock (struct tcf_proto*) ; 

__attribute__((used)) static int fw_change(struct tcf_proto *tp, unsigned long base,
		     u32 handle,
		     struct nlattr **tca,
		     unsigned long *arg)
{
	struct fw_head *head = (struct fw_head*)tp->root;
	struct fw_filter *f = (struct fw_filter *) *arg;
	struct nlattr *opt = tca[TCA_OPTIONS];
	struct nlattr *tb[TCA_FW_MAX + 1];
	int err;

	if (!opt)
		return handle ? -EINVAL : 0;

	err = nla_parse_nested(tb, TCA_FW_MAX, opt, fw_policy);
	if (err < 0)
		return err;

	if (f != NULL) {
		if (f->id != handle && handle)
			return -EINVAL;
		return fw_change_attrs(tp, f, tb, tca, base);
	}

	if (!handle)
		return -EINVAL;

	if (head == NULL) {
		u32 mask = 0xFFFFFFFF;
		if (tb[TCA_FW_MASK])
			mask = nla_get_u32(tb[TCA_FW_MASK]);

		head = kzalloc(sizeof(struct fw_head), GFP_KERNEL);
		if (head == NULL)
			return -ENOBUFS;
		head->mask = mask;

		tcf_tree_lock(tp);
		tp->root = head;
		tcf_tree_unlock(tp);
	}

	f = kzalloc(sizeof(struct fw_filter), GFP_KERNEL);
	if (f == NULL)
		return -ENOBUFS;

	f->id = handle;

	err = fw_change_attrs(tp, f, tb, tca, base);
	if (err < 0)
		goto errout;

	f->next = head->ht[fw_hash(handle)];
	tcf_tree_lock(tp);
	head->ht[fw_hash(handle)] = f;
	tcf_tree_unlock(tp);

	*arg = (unsigned long)f;
	return 0;

errout:
	kfree(f);
	return err;
}