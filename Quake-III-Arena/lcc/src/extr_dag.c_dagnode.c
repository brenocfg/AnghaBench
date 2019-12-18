#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int op; int /*<<< orphan*/ * syms; TYPE_2__** kids; } ;
struct dag {TYPE_1__ node; } ;
struct TYPE_6__ {int /*<<< orphan*/  count; } ;
typedef  int /*<<< orphan*/  Symbol ;
typedef  TYPE_2__* Node ;

/* Variables and functions */
 int /*<<< orphan*/  FUNC ; 
 int /*<<< orphan*/  NEW0 (struct dag*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dag *dagnode(int op, Node l, Node r, Symbol sym) {
	struct dag *p;

	NEW0(p, FUNC);
	p->node.op = op;
	if ((p->node.kids[0] = l) != NULL)
		++l->count;
	if ((p->node.kids[1] = r) != NULL)
		++r->count;
	p->node.syms[0] = sym;
	return p;
}