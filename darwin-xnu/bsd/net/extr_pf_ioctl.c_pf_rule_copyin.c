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
typedef  scalar_t__ uint8_t ;
struct proc {int /*<<< orphan*/  p_pid; int /*<<< orphan*/  p_ucred; } ;
struct TYPE_4__ {int /*<<< orphan*/ * tqe_next; int /*<<< orphan*/ * tqe_prev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * cur; int /*<<< orphan*/  list; } ;
struct pf_rule {char* label; char* ifname; char* qname; char* pqname; char* tagname; char* match_tagname; char* overload_tblname; int /*<<< orphan*/  rule_flag; TYPE_2__ entries; scalar_t__ src_nodes; scalar_t__ states; TYPE_1__ rpool; int /*<<< orphan*/ * overload_tbl; int /*<<< orphan*/ * kif; int /*<<< orphan*/ * anchor; int /*<<< orphan*/  cpid; int /*<<< orphan*/  cuid; } ;

/* Variables and functions */
 scalar_t__ PFDEV_PFM ; 
 int /*<<< orphan*/  PFRULE_PFM ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcopy (struct pf_rule*,struct pf_rule*,int) ; 
 int /*<<< orphan*/  kauth_cred_getuid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pf_rule_copyin(struct pf_rule *src, struct pf_rule *dst, struct proc *p,
    int minordev)
{
	bcopy(src, dst, sizeof (struct pf_rule));

	dst->label[sizeof (dst->label) - 1] = '\0';
	dst->ifname[sizeof (dst->ifname) - 1] = '\0';
	dst->qname[sizeof (dst->qname) - 1] = '\0';
	dst->pqname[sizeof (dst->pqname) - 1] = '\0';
	dst->tagname[sizeof (dst->tagname) - 1] = '\0';
	dst->match_tagname[sizeof (dst->match_tagname) - 1] = '\0';
	dst->overload_tblname[sizeof (dst->overload_tblname) - 1] = '\0';

	dst->cuid = kauth_cred_getuid(p->p_ucred);
	dst->cpid = p->p_pid;

	dst->anchor = NULL;
	dst->kif = NULL;
	dst->overload_tbl = NULL;

	TAILQ_INIT(&dst->rpool.list);
	dst->rpool.cur = NULL;

	/* initialize refcounting */
	dst->states = 0;
	dst->src_nodes = 0;

	dst->entries.tqe_prev = NULL;
	dst->entries.tqe_next = NULL;
	if ((uint8_t)minordev == PFDEV_PFM)
		dst->rule_flag |= PFRULE_PFM;
}