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
typedef  scalar_t__ u_int32_t ;
struct pf_ruleset {TYPE_2__* rules; } ;
struct pf_rule {int dummy; } ;
struct TYPE_3__ {int open; scalar_t__ ticket; int /*<<< orphan*/  rcount; int /*<<< orphan*/  ptr; } ;
struct TYPE_4__ {TYPE_1__ inactive; } ;

/* Variables and functions */
 int EINVAL ; 
 int PF_RULESET_MAX ; 
 struct pf_rule* TAILQ_FIRST (int /*<<< orphan*/ ) ; 
 struct pf_ruleset* pf_find_or_create_ruleset (char const*) ; 
 int /*<<< orphan*/  pf_rm_rule (int /*<<< orphan*/ ,struct pf_rule*) ; 

__attribute__((used)) static int
pf_begin_rules(u_int32_t *ticket, int rs_num, const char *anchor)
{
	struct pf_ruleset	*rs;
	struct pf_rule		*rule;

	if (rs_num < 0 || rs_num >= PF_RULESET_MAX)
		return (EINVAL);
	rs = pf_find_or_create_ruleset(anchor);
	if (rs == NULL)
		return (EINVAL);
	while ((rule = TAILQ_FIRST(rs->rules[rs_num].inactive.ptr)) != NULL) {
		pf_rm_rule(rs->rules[rs_num].inactive.ptr, rule);
		rs->rules[rs_num].inactive.rcount--;
	}
	*ticket = ++rs->rules[rs_num].inactive.ticket;
	rs->rules[rs_num].inactive.open = 1;
	return (0);
}