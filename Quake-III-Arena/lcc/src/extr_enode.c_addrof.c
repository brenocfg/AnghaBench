#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* Tree ;
struct TYPE_11__ {int /*<<< orphan*/  sym; } ;
struct TYPE_12__ {int /*<<< orphan*/  type; struct TYPE_12__** kids; TYPE_1__ u; int /*<<< orphan*/  op; } ;
typedef  int /*<<< orphan*/  Symbol ;

/* Variables and functions */
#define  ASGN 131 
#define  COND 130 
#define  INDIR 129 
#define  RIGHT 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  error (char*) ; 
 int generic (int /*<<< orphan*/ ) ; 
 TYPE_2__* idtree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  root (TYPE_2__*) ; 
 TYPE_2__* tree (int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* value (TYPE_2__*) ; 

Tree addrof(Tree p) {
	Tree q = p;

	for (;;)
		switch (generic(q->op)) {
		case RIGHT:
			assert(q->kids[0] || q->kids[1]);
			q = q->kids[1] ? q->kids[1] : q->kids[0];
			continue;
		case ASGN:
			q = q->kids[1];
			continue;
		case COND: {
			Symbol t1 = q->u.sym;
			q->u.sym = 0;
			q = idtree(t1);
			/* fall thru */
			}
		case INDIR:
			if (p == q)
				return q->kids[0];
			q = q->kids[0];
			return tree(RIGHT, q->type, root(p), q);
		default:
			error("addressable object required\n");
			return value(p);
		}
}