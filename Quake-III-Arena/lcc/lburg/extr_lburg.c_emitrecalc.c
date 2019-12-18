#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* Term ;
struct TYPE_7__ {struct TYPE_7__* link; } ;
struct TYPE_6__ {scalar_t__ kind; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__* Nonterm ;

/* Variables and functions */
 scalar_t__ TERM ; 
 TYPE_2__* nts ; 
 int /*<<< orphan*/  print (char*,char*,...) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void emitrecalc(char *pre, Term root, Term kid) {
	if (root->kind == TERM && strncmp(root->name, "INDIR", 5) == 0
	&&   kid->kind == TERM &&  strcmp(kid->name,  "VREGP"   ) == 0) {
		Nonterm p;
		print("%sif (mayrecalc(a)) {\n", pre);
		print("%s%1struct %Pstate *q = a->syms[RX]->u.t.cse->x.state;\n", pre);
		for (p = nts; p; p = p->link) {
			print("%s%1if (q->cost[%P%S_NT] == 0) {\n", pre, p);
			print("%s%2p->cost[%P%S_NT] = 0;\n", pre, p);
			print("%s%2p->rule.%P%S = q->rule.%P%S;\n", pre, p, p);
			print("%s%1}\n", pre);
		}
		print("%s}\n", pre);
	}
}