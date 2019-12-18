#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  list_ty ;
struct TYPE_9__ {struct TYPE_9__* link; TYPE_2__** kids; TYPE_1__** syms; int /*<<< orphan*/  op; } ;
struct TYPE_8__ {TYPE_1__** syms; int /*<<< orphan*/  op; } ;
struct TYPE_7__ {scalar_t__ scope; } ;
typedef  TYPE_3__* Node ;

/* Variables and functions */
 scalar_t__ ADDRG ; 
 scalar_t__ JUMP ; 
 scalar_t__ LABELS ; 
 scalar_t__ P ; 
 int /*<<< orphan*/  Seq_addhi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Seq_new (int /*<<< orphan*/ ) ; 
 scalar_t__ V ; 
 int /*<<< orphan*/  put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcc_Forest (int /*<<< orphan*/ ) ; 
 scalar_t__ specific (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * temps ; 
 int /*<<< orphan*/  visit (TYPE_3__*) ; 

__attribute__((used)) static Node asdl_gen(Node p) {
	Node q;
	list_ty forest = Seq_new(0);

	for (q = p; p != NULL; p = p->link)
		if (specific(p->op) == JUMP+V && specific(p->kids[0]->op) == ADDRG+P
		&& p->kids[0]->syms[0]->scope == LABELS) {
			p->syms[0] = p->kids[0]->syms[0];
			p->kids[0] = NULL;
		}
	for (p = q; p != NULL; p = p->link)
		Seq_addhi(forest, visit(p));
	put(rcc_Forest(forest));
	temps = NULL;
	return q;
}