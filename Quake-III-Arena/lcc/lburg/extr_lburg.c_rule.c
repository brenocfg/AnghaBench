#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* Tree ;
typedef  TYPE_2__* Term ;
struct TYPE_13__ {TYPE_3__* rules; scalar_t__ lhscount; } ;
struct TYPE_12__ {char* template; char* code; int cost; struct TYPE_12__* link; struct TYPE_12__* chain; struct TYPE_12__* next; scalar_t__ ern; TYPE_1__* pattern; struct TYPE_12__* decode; TYPE_8__* lhs; scalar_t__ packed; } ;
struct TYPE_11__ {scalar_t__ kind; TYPE_3__* chain; TYPE_3__* rules; } ;
struct TYPE_10__ {TYPE_2__* op; int /*<<< orphan*/ * right; int /*<<< orphan*/ * left; } ;
typedef  TYPE_3__* Rule ;
typedef  TYPE_2__* Nonterm ;

/* Variables and functions */
 scalar_t__ TERM ; 
 TYPE_3__* alloc (int) ; 
 TYPE_8__* nonterm (char*) ; 
 scalar_t__ nrules ; 
 TYPE_3__* rules ; 
 char* stringf (char*,char*) ; 
 int strtol (char*,char**,int) ; 
 int /*<<< orphan*/  yyerror (char*,char*) ; 

Rule rule(char *id, Tree pattern, char *template, char *code) {
	Rule r = alloc(sizeof *r), *q;
	Term p = pattern->op;
	char *end;

	r->lhs = nonterm(id);
	r->packed = ++r->lhs->lhscount;
	for (q = &r->lhs->rules; *q; q = &(*q)->decode)
		;
	*q = r;
	r->pattern = pattern;
	r->ern = ++nrules;
	r->template = template;
	r->code = code;
	r->cost = strtol(code, &end, 10);
	if (*end) {
		r->cost = -1;
		r->code = stringf("(%s)", code);
	}
	if (p->kind == TERM) {
		for (q = &p->rules; *q; q = &(*q)->next)
			;
		*q = r;
	} else if (pattern->left == NULL && pattern->right == NULL) {
		Nonterm p = pattern->op;
		r->chain = p->chain;
	        p->chain = r;
		if (r->cost == -1)
			yyerror("illegal nonconstant cost `%s'\n", code);
	}
	for (q = &rules; *q; q = &(*q)->link)
		;
	r->link = *q;
	*q = r;
	return r;
}