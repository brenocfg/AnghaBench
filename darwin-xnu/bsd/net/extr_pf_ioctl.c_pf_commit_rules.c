#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
struct pf_ruleset {TYPE_3__* rules; } ;
struct pf_rulequeue {int dummy; } ;
struct pf_rule {int rule_flag; } ;
struct TYPE_5__ {scalar_t__ ticket; scalar_t__ rcount; scalar_t__ open; struct pf_rule** ptr_array; struct pf_rulequeue* ptr; } ;
struct TYPE_4__ {scalar_t__ rcount; scalar_t__ ticket; struct pf_rulequeue* ptr; struct pf_rule** ptr_array; } ;
struct TYPE_6__ {TYPE_2__ inactive; TYPE_1__ active; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  M_TEMP ; 
 int PFRULE_PFM ; 
 int PF_RULESET_MAX ; 
 struct pf_rule* TAILQ_FIRST (struct pf_rulequeue*) ; 
 struct pf_rule* TAILQ_NEXT (struct pf_rule*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _FREE (struct pf_rule**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  pf_calc_skip_steps (struct pf_rulequeue*) ; 
 struct pf_ruleset* pf_find_ruleset (char*) ; 
 int /*<<< orphan*/  pf_lock ; 
 struct pf_ruleset pf_main_ruleset ; 
 int /*<<< orphan*/  pf_remove_if_empty_ruleset (struct pf_ruleset*) ; 
 int /*<<< orphan*/  pf_rm_rule (struct pf_rulequeue*,struct pf_rule*) ; 
 int pf_setup_pfsync_matching (struct pf_ruleset*) ; 
 int /*<<< orphan*/  pffwrules ; 

__attribute__((used)) static int
pf_commit_rules(u_int32_t ticket, int rs_num, char *anchor)
{
	struct pf_ruleset	*rs;
	struct pf_rule		*rule, **old_array, *r;
	struct pf_rulequeue	*old_rules;
	int			 error;
	u_int32_t		 old_rcount;

	LCK_MTX_ASSERT(pf_lock, LCK_MTX_ASSERT_OWNED);

	if (rs_num < 0 || rs_num >= PF_RULESET_MAX)
		return (EINVAL);
	rs = pf_find_ruleset(anchor);
	if (rs == NULL || !rs->rules[rs_num].inactive.open ||
	    ticket != rs->rules[rs_num].inactive.ticket)
		return (EBUSY);

	/* Calculate checksum for the main ruleset */
	if (rs == &pf_main_ruleset) {
		error = pf_setup_pfsync_matching(rs);
		if (error != 0)
			return (error);
	}

	/* Swap rules, keep the old. */
	old_rules = rs->rules[rs_num].active.ptr;
	old_rcount = rs->rules[rs_num].active.rcount;
	old_array = rs->rules[rs_num].active.ptr_array;

	if(old_rcount != 0) {
		r = TAILQ_FIRST(rs->rules[rs_num].active.ptr);
		while (r) {
			if (r->rule_flag & PFRULE_PFM)
				pffwrules--;
			r = TAILQ_NEXT(r, entries);
		}
	}


	rs->rules[rs_num].active.ptr =
	    rs->rules[rs_num].inactive.ptr;
	rs->rules[rs_num].active.ptr_array =
	    rs->rules[rs_num].inactive.ptr_array;
	rs->rules[rs_num].active.rcount =
	    rs->rules[rs_num].inactive.rcount;
	rs->rules[rs_num].inactive.ptr = old_rules;
	rs->rules[rs_num].inactive.ptr_array = old_array;
	rs->rules[rs_num].inactive.rcount = old_rcount;

	rs->rules[rs_num].active.ticket =
	    rs->rules[rs_num].inactive.ticket;
	pf_calc_skip_steps(rs->rules[rs_num].active.ptr);


	/* Purge the old rule list. */
	while ((rule = TAILQ_FIRST(old_rules)) != NULL)
		pf_rm_rule(old_rules, rule);
	if (rs->rules[rs_num].inactive.ptr_array)
		_FREE(rs->rules[rs_num].inactive.ptr_array, M_TEMP);
	rs->rules[rs_num].inactive.ptr_array = NULL;
	rs->rules[rs_num].inactive.rcount = 0;
	rs->rules[rs_num].inactive.open = 0;
	pf_remove_if_empty_ruleset(rs);
	return (0);
}