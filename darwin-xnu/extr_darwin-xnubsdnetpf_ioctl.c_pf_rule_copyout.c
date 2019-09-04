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
struct TYPE_3__ {int /*<<< orphan*/ * tqe_next; int /*<<< orphan*/ * tqe_prev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * cur; int /*<<< orphan*/  list; } ;
struct pf_rule {TYPE_1__ entries; TYPE_2__ rpool; int /*<<< orphan*/ * overload_tbl; int /*<<< orphan*/ * kif; int /*<<< orphan*/ * anchor; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcopy (struct pf_rule*,struct pf_rule*,int) ; 

__attribute__((used)) static void
pf_rule_copyout(struct pf_rule *src, struct pf_rule *dst)
{
	bcopy(src, dst, sizeof (struct pf_rule));

	dst->anchor = NULL;
	dst->kif = NULL;
	dst->overload_tbl = NULL;

	TAILQ_INIT(&dst->rpool.list);
	dst->rpool.cur = NULL;

	dst->entries.tqe_prev = NULL;
	dst->entries.tqe_next = NULL;
}