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
struct tcf_nat {int /*<<< orphan*/  tcf_lock; int /*<<< orphan*/  tcf_action; int /*<<< orphan*/  flags; int /*<<< orphan*/  mask; int /*<<< orphan*/  new_addr; int /*<<< orphan*/  old_addr; } ;
struct tcf_common {int dummy; } ;
struct tc_nat {int /*<<< orphan*/  action; int /*<<< orphan*/  flags; int /*<<< orphan*/  mask; int /*<<< orphan*/  new_addr; int /*<<< orphan*/  old_addr; int /*<<< orphan*/  index; } ;
struct tc_action {int dummy; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int ACT_P_CREATED ; 
 int EEXIST ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct tcf_common*) ; 
 int PTR_ERR (struct tcf_common*) ; 
 int /*<<< orphan*/  TCA_NAT_MAX ; 
 size_t TCA_NAT_PARMS ; 
 int /*<<< orphan*/  nat_hash_info ; 
 int /*<<< orphan*/  nat_idx_gen ; 
 int /*<<< orphan*/  nat_policy ; 
 struct tc_nat* nla_data (struct nlattr*) ; 
 int nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct tcf_common* tcf_hash_check (int /*<<< orphan*/ ,struct tc_action*,int,int /*<<< orphan*/ *) ; 
 struct tcf_common* tcf_hash_create (int /*<<< orphan*/ ,struct nlattr*,struct tc_action*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_hash_insert (struct tcf_common*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_hash_release (struct tcf_common*,int,int /*<<< orphan*/ *) ; 
 struct tcf_nat* to_tcf_nat (struct tcf_common*) ; 

__attribute__((used)) static int tcf_nat_init(struct nlattr *nla, struct nlattr *est,
			struct tc_action *a, int ovr, int bind)
{
	struct nlattr *tb[TCA_NAT_MAX + 1];
	struct tc_nat *parm;
	int ret = 0, err;
	struct tcf_nat *p;
	struct tcf_common *pc;

	if (nla == NULL)
		return -EINVAL;

	err = nla_parse_nested(tb, TCA_NAT_MAX, nla, nat_policy);
	if (err < 0)
		return err;

	if (tb[TCA_NAT_PARMS] == NULL)
		return -EINVAL;
	parm = nla_data(tb[TCA_NAT_PARMS]);

	pc = tcf_hash_check(parm->index, a, bind, &nat_hash_info);
	if (!pc) {
		pc = tcf_hash_create(parm->index, est, a, sizeof(*p), bind,
				     &nat_idx_gen, &nat_hash_info);
		if (IS_ERR(pc))
		    return PTR_ERR(pc);
		p = to_tcf_nat(pc);
		ret = ACT_P_CREATED;
	} else {
		p = to_tcf_nat(pc);
		if (!ovr) {
			tcf_hash_release(pc, bind, &nat_hash_info);
			return -EEXIST;
		}
	}

	spin_lock_bh(&p->tcf_lock);
	p->old_addr = parm->old_addr;
	p->new_addr = parm->new_addr;
	p->mask = parm->mask;
	p->flags = parm->flags;

	p->tcf_action = parm->action;
	spin_unlock_bh(&p->tcf_lock);

	if (ret == ACT_P_CREATED)
		tcf_hash_insert(pc, &nat_hash_info);

	return ret;
}