#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pf_ruleset {TYPE_2__* rules; } ;
struct pf_rule {int dummy; } ;
struct pf_anchor_stackframe {TYPE_4__* r; struct pf_ruleset* rs; TYPE_5__* child; int /*<<< orphan*/ * parent; } ;
struct TYPE_11__ {struct pf_ruleset ruleset; scalar_t__ match; } ;
struct TYPE_10__ {int quick; TYPE_3__* anchor; } ;
struct TYPE_9__ {int match; } ;
struct TYPE_7__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_8__ {TYPE_1__ active; } ;

/* Variables and functions */
 TYPE_5__* RB_NEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_5__*) ; 
 struct pf_rule* TAILQ_FIRST (int /*<<< orphan*/ ) ; 
 struct pf_rule* TAILQ_NEXT (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  pf_anchor_node ; 
 struct pf_anchor_stackframe* pf_anchor_stack ; 

int
pf_step_out_of_anchor(int *depth, struct pf_ruleset **rs, int n,
    struct pf_rule **r, struct pf_rule **a, int *match)
{
	struct pf_anchor_stackframe	*f;
	int quick = 0;

	do {
		if (*depth <= 0)
			break;
		f = pf_anchor_stack + *depth - 1;
		if (f->parent != NULL && f->child != NULL) {
			if (f->child->match ||
			    (match != NULL && *match)) {
				f->r->anchor->match = 1;
				if (match)
					*match = 0;
			}
			f->child = RB_NEXT(pf_anchor_node, f->parent, f->child);
			if (f->child != NULL) {
				*rs = &f->child->ruleset;
				*r = TAILQ_FIRST((*rs)->rules[n].active.ptr);
				if (*r == NULL)
					continue;
				else
					break;
			}
		}
		(*depth)--;
		if (*depth == 0 && a != NULL)
			*a = NULL;
		*rs = f->rs;
		if (f->r->anchor->match || (match  != NULL && *match))
			quick = f->r->quick;
		*r = TAILQ_NEXT(f->r, entries);
	} while (*r == NULL);

	return (quick);
}