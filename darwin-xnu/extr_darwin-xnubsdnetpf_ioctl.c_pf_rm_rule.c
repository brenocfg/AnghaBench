#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pf_rulequeue {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  list; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {int /*<<< orphan*/ * tqe_prev; } ;
struct pf_rule {scalar_t__ states; int nr; scalar_t__ src_nodes; TYPE_4__ rpool; int /*<<< orphan*/  kif; scalar_t__ overload_tbl; TYPE_3__ dst; TYPE_2__ src; int /*<<< orphan*/  match_tag; int /*<<< orphan*/  tag; TYPE_1__ entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  PFI_KIF_REF_RULE ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct pf_rulequeue*,struct pf_rule*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  pf_anchor_remove (struct pf_rule*) ; 
 int /*<<< orphan*/  pf_empty_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pf_rtlabel_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pf_rule_pl ; 
 int /*<<< orphan*/  pf_tag_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_tbladdr_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfi_dynaddr_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfi_kif_unref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfr_detach_table (scalar_t__) ; 
 int /*<<< orphan*/  pool_put (int /*<<< orphan*/ *,struct pf_rule*) ; 

void
pf_rm_rule(struct pf_rulequeue *rulequeue, struct pf_rule *rule)
{
	if (rulequeue != NULL) {
		if (rule->states <= 0) {
			/*
			 * XXX - we need to remove the table *before* detaching
			 * the rule to make sure the table code does not delete
			 * the anchor under our feet.
			 */
			pf_tbladdr_remove(&rule->src.addr);
			pf_tbladdr_remove(&rule->dst.addr);
			if (rule->overload_tbl)
				pfr_detach_table(rule->overload_tbl);
		}
		TAILQ_REMOVE(rulequeue, rule, entries);
		rule->entries.tqe_prev = NULL;
		rule->nr = -1;
	}

	if (rule->states > 0 || rule->src_nodes > 0 ||
	    rule->entries.tqe_prev != NULL)
		return;
	pf_tag_unref(rule->tag);
	pf_tag_unref(rule->match_tag);
	pf_rtlabel_remove(&rule->src.addr);
	pf_rtlabel_remove(&rule->dst.addr);
	pfi_dynaddr_remove(&rule->src.addr);
	pfi_dynaddr_remove(&rule->dst.addr);
	if (rulequeue == NULL) {
		pf_tbladdr_remove(&rule->src.addr);
		pf_tbladdr_remove(&rule->dst.addr);
		if (rule->overload_tbl)
			pfr_detach_table(rule->overload_tbl);
	}
	pfi_kif_unref(rule->kif, PFI_KIF_REF_RULE);
	pf_anchor_remove(rule);
	pf_empty_pool(&rule->rpool.list);
	pool_put(&pf_rule_pl, rule);
}