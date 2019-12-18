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
struct expression {TYPE_1__* elts; } ;
typedef  enum exp_opcode { ____Placeholder_exp_opcode } exp_opcode ;
struct TYPE_2__ {int opcode; int /*<<< orphan*/  symbol; struct type* type; } ;
typedef  int /*<<< orphan*/  LONGEST ;

/* Variables and functions */
 int /*<<< orphan*/  EVAL_AVOID_SIDE_EFFECTS ; 
 int /*<<< orphan*/  NULL_TYPE ; 
#define  OP_VAR_VALUE 130 
 struct type* SYMBOL_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_CODE (struct type*) ; 
 int /*<<< orphan*/  TYPE_CODE_ARRAY ; 
 int /*<<< orphan*/  TYPE_CODE_PTR ; 
 int /*<<< orphan*/  TYPE_CODE_REF ; 
 int /*<<< orphan*/  TYPE_LENGTH (struct type*) ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
#define  UNOP_IND 129 
#define  UNOP_MEMVAL 128 
 struct type* VALUE_TYPE (struct value*) ; 
 int /*<<< orphan*/  builtin_type_int ; 
 struct type* check_typedef (struct type*) ; 
 int /*<<< orphan*/  error (char*) ; 
 struct value* evaluate_subexp (int /*<<< orphan*/ ,struct expression*,int*,int /*<<< orphan*/ ) ; 
 struct value* value_from_longest (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct value *
evaluate_subexp_for_sizeof (struct expression *exp, int *pos)
{
  enum exp_opcode op;
  int pc;
  struct type *type;
  struct value *val;

  pc = (*pos);
  op = exp->elts[pc].opcode;

  switch (op)
    {
      /* This case is handled specially
         so that we avoid creating a value for the result type.
         If the result type is very big, it's desirable not to
         create a value unnecessarily.  */
    case UNOP_IND:
      (*pos)++;
      val = evaluate_subexp (NULL_TYPE, exp, pos, EVAL_AVOID_SIDE_EFFECTS);
      type = check_typedef (VALUE_TYPE (val));
      if (TYPE_CODE (type) != TYPE_CODE_PTR
	  && TYPE_CODE (type) != TYPE_CODE_REF
	  && TYPE_CODE (type) != TYPE_CODE_ARRAY)
	error ("Attempt to take contents of a non-pointer value.");
      type = check_typedef (TYPE_TARGET_TYPE (type));
      return value_from_longest (builtin_type_int, (LONGEST)
				 TYPE_LENGTH (type));

    case UNOP_MEMVAL:
      (*pos) += 3;
      type = check_typedef (exp->elts[pc + 1].type);
      return value_from_longest (builtin_type_int,
				 (LONGEST) TYPE_LENGTH (type));

    case OP_VAR_VALUE:
      (*pos) += 4;
      type = check_typedef (SYMBOL_TYPE (exp->elts[pc + 2].symbol));
      return
	value_from_longest (builtin_type_int, (LONGEST) TYPE_LENGTH (type));

    default:
      val = evaluate_subexp (NULL_TYPE, exp, pos, EVAL_AVOID_SIDE_EFFECTS);
      return value_from_longest (builtin_type_int,
				 (LONGEST) TYPE_LENGTH (VALUE_TYPE (val)));
    }
}