#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int (* _rule ) (int /*<<< orphan*/ ,int) ;} ;
struct TYPE_11__ {TYPE_1__ x; } ;
struct TYPE_9__ {int /*<<< orphan*/  state; } ;
struct TYPE_10__ {int /*<<< orphan*/  op; TYPE_2__ x; } ;
typedef  TYPE_3__* Node ;

/* Variables and functions */
 TYPE_7__* IR ; 
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 int /*<<< orphan*/  fprint (int /*<<< orphan*/ ,char*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  src ; 
 int /*<<< orphan*/  stderr ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int getrule(Node p, int nt) {
	int rulenum;

	assert(p);
	rulenum = (*IR->x._rule)(p->x.state, nt);
	if (!rulenum) {
		fprint(stderr, "(%x->op=%s at %w is corrupt.)\n", p, opname(p->op), &src);
		assert(0);
	}
	return rulenum;
}