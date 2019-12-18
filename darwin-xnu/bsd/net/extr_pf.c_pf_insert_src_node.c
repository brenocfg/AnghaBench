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
struct TYPE_7__ {struct pf_rule* ptr; } ;
struct pf_src_node {scalar_t__ states; TYPE_3__ rule; int /*<<< orphan*/  ruletype; int /*<<< orphan*/  creation; int /*<<< orphan*/  addr; void* af; int /*<<< orphan*/  conn_rate; } ;
struct TYPE_6__ {int opts; } ;
struct TYPE_5__ {int /*<<< orphan*/  seconds; int /*<<< orphan*/  limit; } ;
struct pf_rule {int rule_flag; scalar_t__ max_src_nodes; scalar_t__ src_nodes; scalar_t__ max_src_states; int /*<<< orphan*/  action; TYPE_2__ rpool; TYPE_1__ max_src_conn_rate; } ;
struct pf_addr {int dummy; } ;
typedef  void* sa_family_t ;
struct TYPE_8__ {scalar_t__ debug; int /*<<< orphan*/ * lcounters; int /*<<< orphan*/  src_nodes; int /*<<< orphan*/ * scounters; } ;

/* Variables and functions */
 size_t LCNT_SRCNODES ; 
 size_t LCNT_SRCSTATES ; 
 int PFRULE_RULESRCTRACK ; 
 int /*<<< orphan*/  PF_ACPY (int /*<<< orphan*/ *,struct pf_addr*,void*) ; 
 scalar_t__ PF_DEBUG_MISC ; 
 int PF_POOL_STICKYADDR ; 
 int /*<<< orphan*/  PR_WAITOK ; 
 struct pf_src_node* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pf_src_node*) ; 
 int /*<<< orphan*/ * RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pf_src_node*) ; 
 size_t SCNT_SRC_NODE_INSERT ; 
 size_t SCNT_SRC_NODE_SEARCH ; 
 int /*<<< orphan*/  bzero (struct pf_src_node*,int) ; 
 int /*<<< orphan*/  pf_init_threshold (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_print_host (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pf_src_tree ; 
 int /*<<< orphan*/  pf_src_tree_pl ; 
 TYPE_4__ pf_status ; 
 int /*<<< orphan*/  pf_time_second () ; 
 struct pf_src_node* pool_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pool_put (int /*<<< orphan*/ *,struct pf_src_node*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  tree_src_tracking ; 

int
pf_insert_src_node(struct pf_src_node **sn, struct pf_rule *rule,
    struct pf_addr *src, sa_family_t af)
{
	struct pf_src_node	k;

	if (*sn == NULL) {
		k.af = af;
		PF_ACPY(&k.addr, src, af);
		if (rule->rule_flag & PFRULE_RULESRCTRACK ||
		    rule->rpool.opts & PF_POOL_STICKYADDR)
			k.rule.ptr = rule;
		else
			k.rule.ptr = NULL;
		pf_status.scounters[SCNT_SRC_NODE_SEARCH]++;
		*sn = RB_FIND(pf_src_tree, &tree_src_tracking, &k);
	}
	if (*sn == NULL) {
		if (!rule->max_src_nodes ||
		    rule->src_nodes < rule->max_src_nodes)
			(*sn) = pool_get(&pf_src_tree_pl, PR_WAITOK);
		else
			pf_status.lcounters[LCNT_SRCNODES]++;
		if ((*sn) == NULL)
			return (-1);
		bzero(*sn, sizeof (struct pf_src_node));

		pf_init_threshold(&(*sn)->conn_rate,
		    rule->max_src_conn_rate.limit,
		    rule->max_src_conn_rate.seconds);

		(*sn)->af = af;
		if (rule->rule_flag & PFRULE_RULESRCTRACK ||
		    rule->rpool.opts & PF_POOL_STICKYADDR)
			(*sn)->rule.ptr = rule;
		else
			(*sn)->rule.ptr = NULL;
		PF_ACPY(&(*sn)->addr, src, af);
		if (RB_INSERT(pf_src_tree,
		    &tree_src_tracking, *sn) != NULL) {
			if (pf_status.debug >= PF_DEBUG_MISC) {
				printf("pf: src_tree insert failed: ");
				pf_print_host(&(*sn)->addr, 0, af);
				printf("\n");
			}
			pool_put(&pf_src_tree_pl, *sn);
			return (-1);
		}
		(*sn)->creation = pf_time_second();
		(*sn)->ruletype = rule->action;
		if ((*sn)->rule.ptr != NULL)
			(*sn)->rule.ptr->src_nodes++;
		pf_status.scounters[SCNT_SRC_NODE_INSERT]++;
		pf_status.src_nodes++;
	} else {
		if (rule->max_src_states &&
		    (*sn)->states >= rule->max_src_states) {
			pf_status.lcounters[LCNT_SRCSTATES]++;
			return (-1);
		}
	}
	return (0);
}