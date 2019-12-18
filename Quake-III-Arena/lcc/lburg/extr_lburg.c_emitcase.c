#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* Term ;
struct TYPE_11__ {int /*<<< orphan*/  nterms; int /*<<< orphan*/  op; } ;
struct TYPE_10__ {int cost; char* code; TYPE_1__* pattern; struct TYPE_10__* next; } ;
struct TYPE_9__ {int arity; TYPE_3__* rules; int /*<<< orphan*/  esn; } ;
struct TYPE_8__ {int nterms; TYPE_4__* right; TYPE_4__* left; int /*<<< orphan*/  op; } ;
typedef  TYPE_3__* Rule ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitcost (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  emitrecalc (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitrecord (char*,TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emittest (TYPE_4__*,char*,char*) ; 
 int /*<<< orphan*/  print (char*,...) ; 

__attribute__((used)) static void emitcase(Term p, int ntnumber) {
	Rule r;

	print("%1case %d: /* %S */\n", p->esn, p);
	switch (p->arity) {
	case 0: case -1:
		break;
	case 1:
		print("%2%Plabel(LEFT_CHILD(a));\n");
		break;
	case 2:
		print("%2%Plabel(LEFT_CHILD(a));\n");
		print("%2%Plabel(RIGHT_CHILD(a));\n");
		break;
	default: assert(0);
	}
	for (r = p->rules; r; r = r->next) {
		char *indent = "\t\t\0";
		switch (p->arity) {
		case 0: case -1:
			print("%2/* %R */\n", r);
			if (r->cost == -1) {
				print("%2c = %s;\n", r->code);
				emitrecord("\t\t", r, "c", 0);
			} else
				emitrecord("\t\t", r, r->code, 0);
			break;
		case 1:
			if (r->pattern->nterms > 1) {
				print("%2if (%1/* %R */\n", r);
				emittest(r->pattern->left, "LEFT_CHILD(a)", " ");
				print("%2) {\n");
				indent = "\t\t\t";
			} else
				print("%2/* %R */\n", r);
			if (r->pattern->nterms == 2 && r->pattern->left
			&&  r->pattern->right == NULL)
				emitrecalc(indent, r->pattern->op, r->pattern->left->op);
			print("%sc = ", indent);
			emitcost(r->pattern->left, "LEFT_CHILD(a)");
			print("%s;\n", r->code);
			emitrecord(indent, r, "c", 0);
			if (indent[2])
				print("%2}\n");
			break;
		case 2:
			if (r->pattern->nterms > 1) {
				print("%2if (%1/* %R */\n", r);
				emittest(r->pattern->left,  "LEFT_CHILD(a)",
					r->pattern->right->nterms ? " && " : " ");
				emittest(r->pattern->right, "RIGHT_CHILD(a)", " ");
				print("%2) {\n");
				indent = "\t\t\t";
			} else
				print("%2/* %R */\n", r);
			print("%sc = ", indent);
			emitcost(r->pattern->left,  "LEFT_CHILD(a)");
			emitcost(r->pattern->right, "RIGHT_CHILD(a)");
			print("%s;\n", r->code);
			emitrecord(indent, r, "c", 0);
			if (indent[2])
				print("%2}\n");
			break;
		default: assert(0);
		}
	}
	print("%2break;\n");
}