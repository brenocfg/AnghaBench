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
struct tcf_gact {scalar_t__ tcfg_ptype; int /*<<< orphan*/  tcf_lock; int /*<<< orphan*/  tcfg_pval; int /*<<< orphan*/  tcfg_paction; int /*<<< orphan*/  tcf_action; } ;
struct tcf_common {int dummy; } ;
struct tc_gact_p {scalar_t__ ptype; int /*<<< orphan*/  pval; int /*<<< orphan*/  paction; } ;
struct tc_gact {int /*<<< orphan*/  action; int /*<<< orphan*/  index; } ;
struct tc_action {int dummy; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int ACT_P_CREATED ; 
 int EEXIST ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct tcf_common*) ; 
 scalar_t__ MAX_RAND ; 
 int PTR_ERR (struct tcf_common*) ; 
 int /*<<< orphan*/  TCA_GACT_MAX ; 
 size_t TCA_GACT_PARMS ; 
 size_t TCA_GACT_PROB ; 
 int /*<<< orphan*/  gact_hash_info ; 
 int /*<<< orphan*/  gact_idx_gen ; 
 int /*<<< orphan*/  gact_policy ; 
 void* nla_data (struct nlattr*) ; 
 int nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct tcf_common* tcf_hash_check (int /*<<< orphan*/ ,struct tc_action*,int,int /*<<< orphan*/ *) ; 
 struct tcf_common* tcf_hash_create (int /*<<< orphan*/ ,struct nlattr*,struct tc_action*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_hash_insert (struct tcf_common*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_hash_release (struct tcf_common*,int,int /*<<< orphan*/ *) ; 
 struct tcf_gact* to_gact (struct tcf_common*) ; 

__attribute__((used)) static int tcf_gact_init(struct nlattr *nla, struct nlattr *est,
			 struct tc_action *a, int ovr, int bind)
{
	struct nlattr *tb[TCA_GACT_MAX + 1];
	struct tc_gact *parm;
	struct tcf_gact *gact;
	struct tcf_common *pc;
	int ret = 0;
	int err;
#ifdef CONFIG_GACT_PROB
	struct tc_gact_p *p_parm = NULL;
#endif

	if (nla == NULL)
		return -EINVAL;

	err = nla_parse_nested(tb, TCA_GACT_MAX, nla, gact_policy);
	if (err < 0)
		return err;

	if (tb[TCA_GACT_PARMS] == NULL)
		return -EINVAL;
	parm = nla_data(tb[TCA_GACT_PARMS]);

#ifndef CONFIG_GACT_PROB
	if (tb[TCA_GACT_PROB] != NULL)
		return -EOPNOTSUPP;
#else
	if (tb[TCA_GACT_PROB]) {
		p_parm = nla_data(tb[TCA_GACT_PROB]);
		if (p_parm->ptype >= MAX_RAND)
			return -EINVAL;
	}
#endif

	pc = tcf_hash_check(parm->index, a, bind, &gact_hash_info);
	if (!pc) {
		pc = tcf_hash_create(parm->index, est, a, sizeof(*gact),
				     bind, &gact_idx_gen, &gact_hash_info);
		if (IS_ERR(pc))
		    return PTR_ERR(pc);
		ret = ACT_P_CREATED;
	} else {
		if (!ovr) {
			tcf_hash_release(pc, bind, &gact_hash_info);
			return -EEXIST;
		}
	}

	gact = to_gact(pc);

	spin_lock_bh(&gact->tcf_lock);
	gact->tcf_action = parm->action;
#ifdef CONFIG_GACT_PROB
	if (p_parm) {
		gact->tcfg_paction = p_parm->paction;
		gact->tcfg_pval    = p_parm->pval;
		gact->tcfg_ptype   = p_parm->ptype;
	}
#endif
	spin_unlock_bh(&gact->tcf_lock);
	if (ret == ACT_P_CREATED)
		tcf_hash_insert(pc, &gact_hash_info);
	return ret;
}