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
struct symbol {int dummy; } ;
struct expression {TYPE_1__* elts; } ;
typedef  enum noside { ____Placeholder_noside } noside ;
typedef  enum exp_opcode { ____Placeholder_exp_opcode } exp_opcode ;
struct TYPE_2__ {int opcode; int /*<<< orphan*/  block; struct symbol* symbol; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_IS_CONVERSION ; 
 int /*<<< orphan*/  NULL_TYPE ; 
#define  OP_VAR_VALUE 128 
 int /*<<< orphan*/  SYMBOL_TYPE (struct symbol*) ; 
 int /*<<< orphan*/  TYPE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_CODE_ARRAY ; 
 int /*<<< orphan*/  TYPE_TARGET_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_innermost_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_typedef (int /*<<< orphan*/ ) ; 
 struct value* evaluate_subexp (int /*<<< orphan*/ ,struct expression*,int*,int) ; 
 struct value* locate_var_value (struct symbol*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lookup_pointer_type (int /*<<< orphan*/ ) ; 
 struct value* value_cast (int /*<<< orphan*/ ,struct value*) ; 

struct value *
evaluate_subexp_with_coercion (struct expression *exp,
			       int *pos, enum noside noside)
{
  enum exp_opcode op;
  int pc;
  struct value *val;
  struct symbol *var;

  pc = (*pos);
  op = exp->elts[pc].opcode;

  switch (op)
    {
    case OP_VAR_VALUE:
      var = exp->elts[pc + 2].symbol;
      if (TYPE_CODE (check_typedef (SYMBOL_TYPE (var))) == TYPE_CODE_ARRAY
	  && CAST_IS_CONVERSION)
	{
	  (*pos) += 4;
	  val =
	    locate_var_value
	    (var, block_innermost_frame (exp->elts[pc + 1].block));
	  return value_cast (lookup_pointer_type (TYPE_TARGET_TYPE (check_typedef (SYMBOL_TYPE (var)))),
			     val);
	}
      /* FALLTHROUGH */

    default:
      return evaluate_subexp (NULL_TYPE, exp, pos, noside);
    }
}