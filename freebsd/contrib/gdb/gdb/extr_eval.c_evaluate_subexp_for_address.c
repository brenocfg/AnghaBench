#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct value {int dummy; } ;
struct type {int dummy; } ;
struct symbol {int dummy; } ;
struct expression {TYPE_1__* elts; } ;
typedef  enum noside { ____Placeholder_noside } noside ;
typedef  enum exp_opcode { ____Placeholder_exp_opcode } exp_opcode ;
typedef  enum address_class { ____Placeholder_address_class } address_class ;
struct TYPE_2__ {int opcode; int /*<<< orphan*/  block; struct symbol* symbol; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EVAL_AVOID_SIDE_EFFECTS ; 
 int LOC_CONST ; 
 int LOC_CONST_BYTES ; 
 int LOC_REGISTER ; 
 int LOC_REGPARM ; 
 int /*<<< orphan*/  NULL_TYPE ; 
#define  OP_VAR_VALUE 130 
 int SYMBOL_CLASS (struct symbol*) ; 
 int /*<<< orphan*/  SYMBOL_TYPE (struct symbol*) ; 
 int /*<<< orphan*/  TYPE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_CODE_REF ; 
#define  UNOP_IND 129 
#define  UNOP_MEMVAL 128 
 int /*<<< orphan*/  VALUE_LVAL (struct value*) ; 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 int /*<<< orphan*/  block_innermost_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 struct value* evaluate_subexp (int /*<<< orphan*/ ,struct expression*,int*,int) ; 
 struct value* locate_var_value (struct symbol*,int /*<<< orphan*/ ) ; 
 struct type* lookup_pointer_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lval_memory ; 
 int /*<<< orphan*/  not_lval ; 
 struct value* value_addr (struct value*) ; 
 struct value* value_cast (struct type*,struct value*) ; 
 struct value* value_zero (struct type*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct value *
evaluate_subexp_for_address (struct expression *exp, int *pos,
			     enum noside noside)
{
  enum exp_opcode op;
  int pc;
  struct symbol *var;

  pc = (*pos);
  op = exp->elts[pc].opcode;

  switch (op)
    {
    case UNOP_IND:
      (*pos)++;
      return evaluate_subexp (NULL_TYPE, exp, pos, noside);

    case UNOP_MEMVAL:
      (*pos) += 3;
      return value_cast (lookup_pointer_type (exp->elts[pc + 1].type),
			 evaluate_subexp (NULL_TYPE, exp, pos, noside));

    case OP_VAR_VALUE:
      var = exp->elts[pc + 2].symbol;

      /* C++: The "address" of a reference should yield the address
       * of the object pointed to. Let value_addr() deal with it. */
      if (TYPE_CODE (SYMBOL_TYPE (var)) == TYPE_CODE_REF)
	goto default_case;

      (*pos) += 4;
      if (noside == EVAL_AVOID_SIDE_EFFECTS)
	{
	  struct type *type =
	  lookup_pointer_type (SYMBOL_TYPE (var));
	  enum address_class sym_class = SYMBOL_CLASS (var);

	  if (sym_class == LOC_CONST
	      || sym_class == LOC_CONST_BYTES
	      || sym_class == LOC_REGISTER
	      || sym_class == LOC_REGPARM)
	    error ("Attempt to take address of register or constant.");

	  return
	    value_zero (type, not_lval);
	}
      else
	return
	  locate_var_value
	  (var,
	   block_innermost_frame (exp->elts[pc + 1].block));

    default:
    default_case:
      if (noside == EVAL_AVOID_SIDE_EFFECTS)
	{
	  struct value *x = evaluate_subexp (NULL_TYPE, exp, pos, noside);
	  if (VALUE_LVAL (x) == lval_memory)
	    return value_zero (lookup_pointer_type (VALUE_TYPE (x)),
			       not_lval);
	  else
	    error ("Attempt to take address of non-lval");
	}
      return value_addr (evaluate_subexp (NULL_TYPE, exp, pos, noside));
    }
}