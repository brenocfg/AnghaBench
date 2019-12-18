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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct tcf_skbedit {int flags; int priority; int /*<<< orphan*/  tcf_lock; int /*<<< orphan*/  tcf_action; int /*<<< orphan*/  queue_mapping; } ;
struct tcf_common {int dummy; } ;
struct tc_skbedit {int /*<<< orphan*/  action; int /*<<< orphan*/  index; } ;
struct tc_action {int dummy; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int ACT_P_CREATED ; 
 int EEXIST ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct tcf_common*) ; 
 int PTR_ERR (struct tcf_common*) ; 
 int SKBEDIT_F_PRIORITY ; 
 int SKBEDIT_F_QUEUE_MAPPING ; 
 int /*<<< orphan*/  TCA_SKBEDIT_MAX ; 
 size_t TCA_SKBEDIT_PARMS ; 
 size_t TCA_SKBEDIT_PRIORITY ; 
 size_t TCA_SKBEDIT_QUEUE_MAPPING ; 
 void* nla_data (struct nlattr*) ; 
 int nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skbedit_hash_info ; 
 int /*<<< orphan*/  skbedit_idx_gen ; 
 int /*<<< orphan*/  skbedit_policy ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct tcf_common* tcf_hash_check (int /*<<< orphan*/ ,struct tc_action*,int,int /*<<< orphan*/ *) ; 
 struct tcf_common* tcf_hash_create (int /*<<< orphan*/ ,struct nlattr*,struct tc_action*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_hash_insert (struct tcf_common*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_hash_release (struct tcf_common*,int,int /*<<< orphan*/ *) ; 
 struct tcf_skbedit* to_skbedit (struct tcf_common*) ; 

__attribute__((used)) static int tcf_skbedit_init(struct nlattr *nla, struct nlattr *est,
			 struct tc_action *a, int ovr, int bind)
{
	struct nlattr *tb[TCA_SKBEDIT_MAX + 1];
	struct tc_skbedit *parm;
	struct tcf_skbedit *d;
	struct tcf_common *pc;
	u32 flags = 0, *priority = NULL;
	u16 *queue_mapping = NULL;
	int ret = 0, err;

	if (nla == NULL)
		return -EINVAL;

	err = nla_parse_nested(tb, TCA_SKBEDIT_MAX, nla, skbedit_policy);
	if (err < 0)
		return err;

	if (tb[TCA_SKBEDIT_PARMS] == NULL)
		return -EINVAL;

	if (tb[TCA_SKBEDIT_PRIORITY] != NULL) {
		flags |= SKBEDIT_F_PRIORITY;
		priority = nla_data(tb[TCA_SKBEDIT_PRIORITY]);
	}

	if (tb[TCA_SKBEDIT_QUEUE_MAPPING] != NULL) {
		flags |= SKBEDIT_F_QUEUE_MAPPING;
		queue_mapping = nla_data(tb[TCA_SKBEDIT_QUEUE_MAPPING]);
	}
	if (!flags)
		return -EINVAL;

	parm = nla_data(tb[TCA_SKBEDIT_PARMS]);

	pc = tcf_hash_check(parm->index, a, bind, &skbedit_hash_info);
	if (!pc) {
		pc = tcf_hash_create(parm->index, est, a, sizeof(*d), bind,
				     &skbedit_idx_gen, &skbedit_hash_info);
		if (IS_ERR(pc))
		    return PTR_ERR(pc);

		d = to_skbedit(pc);
		ret = ACT_P_CREATED;
	} else {
		d = to_skbedit(pc);
		if (!ovr) {
			tcf_hash_release(pc, bind, &skbedit_hash_info);
			return -EEXIST;
		}
	}

	spin_lock_bh(&d->tcf_lock);

	d->flags = flags;
	if (flags & SKBEDIT_F_PRIORITY)
		d->priority = *priority;
	if (flags & SKBEDIT_F_QUEUE_MAPPING)
		d->queue_mapping = *queue_mapping;
	d->tcf_action = parm->action;

	spin_unlock_bh(&d->tcf_lock);

	if (ret == ACT_P_CREATED)
		tcf_hash_insert(pc, &skbedit_hash_info);
	return ret;
}