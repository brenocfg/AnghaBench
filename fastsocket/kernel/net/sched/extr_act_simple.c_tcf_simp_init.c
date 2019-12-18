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
struct tcf_defact {int /*<<< orphan*/  tcf_action; } ;
struct tcf_common {int dummy; } ;
struct tc_defact {int /*<<< orphan*/  action; int /*<<< orphan*/  index; } ;
struct tc_action {int dummy; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int ACT_P_CREATED ; 
 int EEXIST ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct tcf_common*) ; 
 int PTR_ERR (struct tcf_common*) ; 
 size_t TCA_DEF_DATA ; 
 int /*<<< orphan*/  TCA_DEF_MAX ; 
 size_t TCA_DEF_PARMS ; 
 int alloc_defdata (struct tcf_defact*,char*) ; 
 int /*<<< orphan*/  kfree (struct tcf_common*) ; 
 void* nla_data (struct nlattr*) ; 
 int nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_policy (struct tcf_defact*,char*,struct tc_defact*) ; 
 int /*<<< orphan*/  simp_hash_info ; 
 int /*<<< orphan*/  simp_idx_gen ; 
 int /*<<< orphan*/  simple_policy ; 
 struct tcf_common* tcf_hash_check (int /*<<< orphan*/ ,struct tc_action*,int,int /*<<< orphan*/ *) ; 
 struct tcf_common* tcf_hash_create (int /*<<< orphan*/ ,struct nlattr*,struct tc_action*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_hash_insert (struct tcf_common*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_simp_release (struct tcf_defact*,int) ; 
 struct tcf_defact* to_defact (struct tcf_common*) ; 

__attribute__((used)) static int tcf_simp_init(struct nlattr *nla, struct nlattr *est,
			 struct tc_action *a, int ovr, int bind)
{
	struct nlattr *tb[TCA_DEF_MAX + 1];
	struct tc_defact *parm;
	struct tcf_defact *d;
	struct tcf_common *pc;
	char *defdata;
	int ret = 0, err;

	if (nla == NULL)
		return -EINVAL;

	err = nla_parse_nested(tb, TCA_DEF_MAX, nla, simple_policy);
	if (err < 0)
		return err;

	if (tb[TCA_DEF_PARMS] == NULL)
		return -EINVAL;

	if (tb[TCA_DEF_DATA] == NULL)
		return -EINVAL;

	parm = nla_data(tb[TCA_DEF_PARMS]);
	defdata = nla_data(tb[TCA_DEF_DATA]);

	pc = tcf_hash_check(parm->index, a, bind, &simp_hash_info);
	if (!pc) {
		pc = tcf_hash_create(parm->index, est, a, sizeof(*d), bind,
				     &simp_idx_gen, &simp_hash_info);
		if (IS_ERR(pc))
		    return PTR_ERR(pc);

		d = to_defact(pc);
		ret = alloc_defdata(d, defdata);
		if (ret < 0) {
			kfree(pc);
			return ret;
		}
		d->tcf_action = parm->action;
		ret = ACT_P_CREATED;
	} else {
		d = to_defact(pc);
		if (!ovr) {
			tcf_simp_release(d, bind);
			return -EEXIST;
		}
		reset_policy(d, defdata, parm);
	}

	if (ret == ACT_P_CREATED)
		tcf_hash_insert(pc, &simp_hash_info);
	return ret;
}