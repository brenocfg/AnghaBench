#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ Type ;
typedef  TYPE_1__* Tree ;
struct TYPE_5__ {scalar_t__ type; int /*<<< orphan*/  u; int /*<<< orphan*/  node; int /*<<< orphan*/ * kids; int /*<<< orphan*/  op; } ;

/* Variables and functions */
 TYPE_1__* tree (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Tree retype(Tree p, Type ty) {
	Tree q;

	if (p->type == ty)
		return p;
	q = tree(p->op, ty, p->kids[0], p->kids[1]);
	q->node = p->node;
	q->u = p->u;
	return q;
}