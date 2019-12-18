#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_22__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_26__ {int spills; int /*<<< orphan*/  listed; TYPE_6__* next; } ;
struct TYPE_29__ {int /*<<< orphan*/  op; TYPE_3__ x; } ;
struct TYPE_23__ {int /*<<< orphan*/  regnode; int /*<<< orphan*/  name; } ;
struct TYPE_28__ {TYPE_1__ x; int /*<<< orphan*/  name; int /*<<< orphan*/  sclass; } ;
struct TYPE_27__ {int /*<<< orphan*/  (* rmap ) (unsigned int) ;} ;
struct TYPE_25__ {int /*<<< orphan*/  size; } ;
struct TYPE_24__ {TYPE_4__ x; TYPE_2__ ptrmetric; } ;
typedef  TYPE_5__* Symbol ;
typedef  TYPE_6__* Node ;

/* Variables and functions */
 scalar_t__ ADDRL ; 
 scalar_t__ ASGN ; 
 int /*<<< orphan*/  FUNC ; 
 scalar_t__ INDIR ; 
 TYPE_22__* IR ; 
 int /*<<< orphan*/  NEW0 (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NeedsReg ; 
 scalar_t__ P ; 
 int /*<<< orphan*/  REGISTER ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dumptree (TYPE_6__*) ; 
 int /*<<< orphan*/  fprint (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  linearize (TYPE_6__*,TYPE_6__*) ; 
 TYPE_6__* newnode (scalar_t__,TYPE_6__*,TYPE_6__*,TYPE_5__*) ; 
 size_t opindex (int /*<<< orphan*/ ) ; 
 unsigned int opkind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prune (TYPE_6__*,TYPE_6__**) ; 
 int /*<<< orphan*/  ralloc (TYPE_6__*) ; 
 int /*<<< orphan*/  rewrite (TYPE_6__*) ; 
 scalar_t__ sizeop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 (unsigned int) ; 

__attribute__((used)) static void genspill(Symbol r, Node last, Symbol tmp) {
	Node p, q;
	Symbol s;
	unsigned ty;

	debug(fprint(stderr, "(spilling %s to local %s)\n", r->x.name, tmp->x.name));
	debug(fprint(stderr, "(genspill: "));
	debug(dumptree(last));
	debug(fprint(stderr, ")\n"));
	ty = opkind(last->op);
	NEW0(s, FUNC);
	s->sclass = REGISTER;
	s->name = s->x.name = r->x.name;
	s->x.regnode = r->x.regnode;
	q = newnode(ADDRL+P + sizeop(IR->ptrmetric.size), NULL, NULL, s);
	q = newnode(INDIR + ty, q, NULL, NULL);
	p = newnode(ADDRL+P + sizeop(IR->ptrmetric.size), NULL, NULL, tmp);
	p = newnode(ASGN + ty, p, q, NULL);
	p->x.spills = 1;
	rewrite(p);
	prune(p, &q);
	q = last->x.next;
	linearize(p, q);
	for (p = last->x.next; p != q; p = p->x.next) {
		ralloc(p);
		assert(!p->x.listed || !NeedsReg[opindex(p->op)] || !(*IR->x.rmap)(opkind(p->op)));
	}
}