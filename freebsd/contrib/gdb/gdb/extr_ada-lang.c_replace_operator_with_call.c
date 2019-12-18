#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct symbol {int dummy; } ;
struct expression {int nelts; TYPE_1__* elts; int /*<<< orphan*/  language_defn; } ;
struct block {int dummy; } ;
struct TYPE_3__ {struct symbol* symbol; struct block* block; int /*<<< orphan*/  opcode; scalar_t__ longconst; } ;
typedef  scalar_t__ LONGEST ;

/* Variables and functions */
 scalar_t__ EXP_ELEM_TO_BYTES (int) ; 
 int /*<<< orphan*/  OP_FUNCALL ; 
 int /*<<< orphan*/  OP_VAR_VALUE ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  xfree (struct expression*) ; 
 scalar_t__ xmalloc (scalar_t__) ; 

__attribute__((used)) static void
replace_operator_with_call (struct expression **expp, int pc, int nargs,
			    int oplen, struct symbol *sym,
			    struct block *block)
{
  /* A new expression, with 6 more elements (3 for funcall, 4 for function
     symbol, -oplen for operator being replaced). */
  struct expression *newexp = (struct expression *)
    xmalloc (sizeof (struct expression)
	     + EXP_ELEM_TO_BYTES ((*expp)->nelts + 7 - oplen));
  struct expression *exp = *expp;

  newexp->nelts = exp->nelts + 7 - oplen;
  newexp->language_defn = exp->language_defn;
  memcpy (newexp->elts, exp->elts, EXP_ELEM_TO_BYTES (pc));
  memcpy (newexp->elts + pc + 7, exp->elts + pc + oplen,
	  EXP_ELEM_TO_BYTES (exp->nelts - pc - oplen));

  newexp->elts[pc].opcode = newexp->elts[pc + 2].opcode = OP_FUNCALL;
  newexp->elts[pc + 1].longconst = (LONGEST) nargs;

  newexp->elts[pc + 3].opcode = newexp->elts[pc + 6].opcode = OP_VAR_VALUE;
  newexp->elts[pc + 4].block = block;
  newexp->elts[pc + 5].symbol = sym;

  *expp = newexp;
  xfree (exp);
}