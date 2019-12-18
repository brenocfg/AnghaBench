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
typedef  enum noside { ____Placeholder_noside } noside ;
typedef  enum exp_opcode { ____Placeholder_exp_opcode } exp_opcode ;
typedef  enum ada_attribute { ____Placeholder_ada_attribute } ada_attribute ;
struct TYPE_2__ {int opcode; int /*<<< orphan*/  string; int /*<<< orphan*/  longconst; int /*<<< orphan*/  symbol; struct type* type; } ;
typedef  int /*<<< orphan*/  LONGEST ;

/* Variables and functions */
#define  BINOP_ADD 149 
#define  BINOP_ASSIGN 148 
#define  BINOP_DIV 147 
#define  BINOP_EXP 146 
 int BINOP_MOD ; 
#define  BINOP_MUL 145 
 int BINOP_REM ; 
#define  BINOP_SUB 144 
 int /*<<< orphan*/  BYTES_TO_EXP_ELEM (int) ; 
 int EVAL_AVOID_SIDE_EFFECTS ; 
 int /*<<< orphan*/  EVAL_NORMAL ; 
 int EVAL_SKIP ; 
 struct type* NULL_TYPE ; 
#define  OP_ARRAY 143 
#define  OP_FUNCALL 142 
 int /*<<< orphan*/  OP_NULL ; 
#define  OP_TYPE 141 
#define  OP_VAR_VALUE 140 
#define  STRUCTOP_PTR 139 
#define  STRUCTOP_STRUCT 138 
 int /*<<< orphan*/  SYMBOL_TYPE (int /*<<< orphan*/ ) ; 
#define  TERNOP_SLICE 137 
 int const TYPE_CODE (struct type*) ; 
#define  TYPE_CODE_ARRAY 136 
#define  TYPE_CODE_FUNC 135 
 int const TYPE_CODE_INT ; 
#define  TYPE_CODE_PTR 134 
 int const TYPE_CODE_REF ; 
#define  TYPE_CODE_STRUCT 133 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
#define  UNOP_ABS 132 
#define  UNOP_CAST 131 
#define  UNOP_IND 130 
#define  UNOP_NEG 129 
#define  UNOP_PLUS 128 
 scalar_t__ VALUE_ADDRESS (struct value*) ; 
 int /*<<< orphan*/  VALUE_LVAL (struct value*) ; 
 scalar_t__ VALUE_OFFSET (struct value*) ; 
 struct type* VALUE_TYPE (struct value*) ; 
 struct type* ada_aligned_type (struct type*) ; 
 int ada_array_arity (struct type*) ; 
 struct type* ada_array_element_type (struct type*,int) ; 
 struct value* ada_coerce_ref (struct value*) ; 
 struct value* ada_coerce_to_simple_array (struct value*) ; 
 int /*<<< orphan*/  ada_is_array_descriptor (struct type*) ; 
 int /*<<< orphan*/  ada_is_fixed_point_type (struct type*) ; 
 int /*<<< orphan*/  ada_is_packed_array_type (struct type*) ; 
 struct type* ada_lookup_struct_elt_type (struct type*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct value* ada_to_fixed_value (struct type*,int /*<<< orphan*/ ,scalar_t__,struct value*) ; 
 int /*<<< orphan*/  ada_type_name (struct type*) ; 
 struct type* ada_type_of_array (struct value*,int /*<<< orphan*/ ) ; 
 struct value* ada_value_assign (struct value*,struct value*) ; 
 struct value* ada_value_ind (struct value*) ; 
 struct value* ada_value_ptr_subscript (struct value*,struct type*,int,struct value**) ; 
 struct value* ada_value_struct_elt (struct value*,int /*<<< orphan*/ *,char*) ; 
 struct value* ada_value_subscript (struct value*,int,struct value**) ; 
 scalar_t__ alloca (int) ; 
 struct value* allocate_value (struct type*) ; 
 int /*<<< orphan*/  binop_user_defined_p (int,struct value*,struct value*) ; 
 struct type* builtin_type_int ; 
 int /*<<< orphan*/  builtin_type_long ; 
 struct type* builtin_type_void ; 
 struct value* call_function_by_hand (struct value*,int,struct value**) ; 
 struct value* cast_from_fixed_to_double (struct value*) ; 
 struct value* cast_to_fixed (struct type*,struct value*) ; 
 struct type* check_typedef (struct type*) ; 
 struct value* coerce_for_assign (struct type*,struct value*) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 struct value* evaluate_subexp (struct type*,struct expression*,int*,int) ; 
 struct value* evaluate_subexp_standard (struct type*,struct expression*,int*,int) ; 
 struct value* evaluate_subexp_with_coercion (struct expression*,int*,int) ; 
 int longest_to_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lval_memory ; 
 int /*<<< orphan*/  not_lval ; 
 struct type* static_unwrap_type (int /*<<< orphan*/ ) ; 
 struct type* to_fixed_array_type (struct type*,int /*<<< orphan*/ *,int) ; 
 struct type* to_static_fixed_type (struct type*) ; 
 int /*<<< orphan*/  unop_user_defined_p (int,struct value*) ; 
 struct value* unwrap_value (struct value*) ; 
 struct value* value_add (struct value*,struct value*) ; 
 struct value* value_addr (struct value*) ; 
 struct value* value_array (int,int,struct value**) ; 
 int value_as_long (struct value*) ; 
 struct value* value_at_lazy (struct type*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct value* value_binop (struct value*,struct value*,int) ; 
 struct value* value_cast (struct type*,struct value*) ; 
 struct value* value_from_longest (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  value_less (struct value*,struct value*) ; 
 struct value* value_neg (struct value*) ; 
 struct value* value_slice (struct value*,int,int) ; 
 struct value* value_sub (struct value*,struct value*) ; 
 struct value* value_x_binop (struct value*,struct value*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct value* value_x_unop (struct value*,int,int /*<<< orphan*/ ) ; 
 struct value* value_zero (struct type*,int /*<<< orphan*/ ) ; 

struct value *
ada_evaluate_subexp (struct type *expect_type, struct expression *exp,
		     int *pos, enum noside noside)
{
  enum exp_opcode op;
  enum ada_attribute atr;
  int tem, tem2, tem3;
  int pc;
  struct value *arg1 = NULL, *arg2 = NULL, *arg3;
  struct type *type;
  int nargs;
  struct value **argvec;

  pc = *pos;
  *pos += 1;
  op = exp->elts[pc].opcode;

  switch (op)
    {
    default:
      *pos -= 1;
      return
	unwrap_value (evaluate_subexp_standard
		      (expect_type, exp, pos, noside));

    case UNOP_CAST:
      (*pos) += 2;
      type = exp->elts[pc + 1].type;
      arg1 = evaluate_subexp (type, exp, pos, noside);
      if (noside == EVAL_SKIP)
	goto nosideret;
      if (type != check_typedef (VALUE_TYPE (arg1)))
	{
	  if (ada_is_fixed_point_type (type))
	    arg1 = cast_to_fixed (type, arg1);
	  else if (ada_is_fixed_point_type (VALUE_TYPE (arg1)))
	    arg1 = value_cast (type, cast_from_fixed_to_double (arg1));
	  else if (VALUE_LVAL (arg1) == lval_memory)
	    {
	      /* This is in case of the really obscure (and undocumented,
	         but apparently expected) case of (Foo) Bar.all, where Bar 
	         is an integer constant and Foo is a dynamic-sized type.
	         If we don't do this, ARG1 will simply be relabeled with
	         TYPE. */
	      if (noside == EVAL_AVOID_SIDE_EFFECTS)
		return value_zero (to_static_fixed_type (type), not_lval);
	      arg1 =
		ada_to_fixed_value
		(type, 0, VALUE_ADDRESS (arg1) + VALUE_OFFSET (arg1), 0);
	    }
	  else
	    arg1 = value_cast (type, arg1);
	}
      return arg1;

      /* FIXME:  UNOP_QUAL should be defined in expression.h */
      /*    case UNOP_QUAL:
         (*pos) += 2;
         type = exp->elts[pc + 1].type;
         return ada_evaluate_subexp (type, exp, pos, noside);
       */
    case BINOP_ASSIGN:
      arg1 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
      arg2 = evaluate_subexp (VALUE_TYPE (arg1), exp, pos, noside);
      if (noside == EVAL_SKIP || noside == EVAL_AVOID_SIDE_EFFECTS)
	return arg1;
      if (binop_user_defined_p (op, arg1, arg2))
	return value_x_binop (arg1, arg2, op, OP_NULL, EVAL_NORMAL);
      else
	{
	  if (ada_is_fixed_point_type (VALUE_TYPE (arg1)))
	    arg2 = cast_to_fixed (VALUE_TYPE (arg1), arg2);
	  else if (ada_is_fixed_point_type (VALUE_TYPE (arg2)))
	    error
	      ("Fixed-point values must be assigned to fixed-point variables");
	  else
	    arg2 = coerce_for_assign (VALUE_TYPE (arg1), arg2);
	  return ada_value_assign (arg1, arg2);
	}

    case BINOP_ADD:
      arg1 = evaluate_subexp_with_coercion (exp, pos, noside);
      arg2 = evaluate_subexp_with_coercion (exp, pos, noside);
      if (noside == EVAL_SKIP)
	goto nosideret;
      if (binop_user_defined_p (op, arg1, arg2))
	return value_x_binop (arg1, arg2, op, OP_NULL, EVAL_NORMAL);
      else
	{
	  if ((ada_is_fixed_point_type (VALUE_TYPE (arg1))
	       || ada_is_fixed_point_type (VALUE_TYPE (arg2)))
	      && VALUE_TYPE (arg1) != VALUE_TYPE (arg2))
	    error
	      ("Operands of fixed-point addition must have the same type");
	  return value_cast (VALUE_TYPE (arg1), value_add (arg1, arg2));
	}

    case BINOP_SUB:
      arg1 = evaluate_subexp_with_coercion (exp, pos, noside);
      arg2 = evaluate_subexp_with_coercion (exp, pos, noside);
      if (noside == EVAL_SKIP)
	goto nosideret;
      if (binop_user_defined_p (op, arg1, arg2))
	return value_x_binop (arg1, arg2, op, OP_NULL, EVAL_NORMAL);
      else
	{
	  if ((ada_is_fixed_point_type (VALUE_TYPE (arg1))
	       || ada_is_fixed_point_type (VALUE_TYPE (arg2)))
	      && VALUE_TYPE (arg1) != VALUE_TYPE (arg2))
	    error
	      ("Operands of fixed-point subtraction must have the same type");
	  return value_cast (VALUE_TYPE (arg1), value_sub (arg1, arg2));
	}

    case BINOP_MUL:
    case BINOP_DIV:
      arg1 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
      arg2 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
      if (noside == EVAL_SKIP)
	goto nosideret;
      if (binop_user_defined_p (op, arg1, arg2))
	return value_x_binop (arg1, arg2, op, OP_NULL, EVAL_NORMAL);
      else
	if (noside == EVAL_AVOID_SIDE_EFFECTS
	    && (op == BINOP_DIV || op == BINOP_REM || op == BINOP_MOD))
	return value_zero (VALUE_TYPE (arg1), not_lval);
      else
	{
	  if (ada_is_fixed_point_type (VALUE_TYPE (arg1)))
	    arg1 = cast_from_fixed_to_double (arg1);
	  if (ada_is_fixed_point_type (VALUE_TYPE (arg2)))
	    arg2 = cast_from_fixed_to_double (arg2);
	  return value_binop (arg1, arg2, op);
	}

    case UNOP_NEG:
      arg1 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
      if (noside == EVAL_SKIP)
	goto nosideret;
      if (unop_user_defined_p (op, arg1))
	return value_x_unop (arg1, op, EVAL_NORMAL);
      else if (ada_is_fixed_point_type (VALUE_TYPE (arg1)))
	return value_cast (VALUE_TYPE (arg1), value_neg (arg1));
      else
	return value_neg (arg1);

      /* FIXME:  OP_UNRESOLVED_VALUE should be defined in expression.h */
      /*    case OP_UNRESOLVED_VALUE:
         /* Only encountered when an unresolved symbol occurs in a
         context other than a function call, in which case, it is
   illegal. *//*
   (*pos) += 3;
   if (noside == EVAL_SKIP)
   goto nosideret;
   else 
   error ("Unexpected unresolved symbol, %s, during evaluation",
   ada_demangle (exp->elts[pc + 2].name));
 */
    case OP_VAR_VALUE:
      *pos -= 1;
      if (noside == EVAL_SKIP)
	{
	  *pos += 4;
	  goto nosideret;
	}
      else if (noside == EVAL_AVOID_SIDE_EFFECTS)
	{
	  *pos += 4;
	  return value_zero
	    (to_static_fixed_type
	     (static_unwrap_type (SYMBOL_TYPE (exp->elts[pc + 2].symbol))),
	     not_lval);
	}
      else
	{
	  arg1 =
	    unwrap_value (evaluate_subexp_standard
			  (expect_type, exp, pos, noside));
	  return ada_to_fixed_value (VALUE_TYPE (arg1), 0,
				     VALUE_ADDRESS (arg1) +
				     VALUE_OFFSET (arg1), arg1);
	}

    case OP_ARRAY:
      (*pos) += 3;
      tem2 = longest_to_int (exp->elts[pc + 1].longconst);
      tem3 = longest_to_int (exp->elts[pc + 2].longconst);
      nargs = tem3 - tem2 + 1;
      type = expect_type ? check_typedef (expect_type) : NULL_TYPE;

      argvec =
	(struct value * *) alloca (sizeof (struct value *) * (nargs + 1));
      for (tem = 0; tem == 0 || tem < nargs; tem += 1)
	/* At least one element gets inserted for the type */
	{
	  /* Ensure that array expressions are coerced into pointer objects. */
	  argvec[tem] = evaluate_subexp_with_coercion (exp, pos, noside);
	}
      if (noside == EVAL_SKIP)
	goto nosideret;
      return value_array (tem2, tem3, argvec);

    case OP_FUNCALL:
      (*pos) += 2;

      /* Allocate arg vector, including space for the function to be
         called in argvec[0] and a terminating NULL */
      nargs = longest_to_int (exp->elts[pc + 1].longconst);
      argvec =
	(struct value * *) alloca (sizeof (struct value *) * (nargs + 2));

      /* FIXME: OP_UNRESOLVED_VALUE should be defined in expression.h */
      /* FIXME: name should be defined in expresion.h */
      /*      if (exp->elts[*pos].opcode == OP_UNRESOLVED_VALUE)
         error ("Unexpected unresolved symbol, %s, during evaluation",
         ada_demangle (exp->elts[pc + 5].name));
       */
      if (0)
	{
	  error ("unexpected code path, FIXME");
	}
      else
	{
	  for (tem = 0; tem <= nargs; tem += 1)
	    argvec[tem] = evaluate_subexp (NULL_TYPE, exp, pos, noside);
	  argvec[tem] = 0;

	  if (noside == EVAL_SKIP)
	    goto nosideret;
	}

      if (TYPE_CODE (VALUE_TYPE (argvec[0])) == TYPE_CODE_REF)
	argvec[0] = value_addr (argvec[0]);

      if (ada_is_packed_array_type (VALUE_TYPE (argvec[0])))
	argvec[0] = ada_coerce_to_simple_array (argvec[0]);

      type = check_typedef (VALUE_TYPE (argvec[0]));
      if (TYPE_CODE (type) == TYPE_CODE_PTR)
	{
	  switch (TYPE_CODE (check_typedef (TYPE_TARGET_TYPE (type))))
	    {
	    case TYPE_CODE_FUNC:
	      type = check_typedef (TYPE_TARGET_TYPE (type));
	      break;
	    case TYPE_CODE_ARRAY:
	      break;
	    case TYPE_CODE_STRUCT:
	      if (noside != EVAL_AVOID_SIDE_EFFECTS)
		argvec[0] = ada_value_ind (argvec[0]);
	      type = check_typedef (TYPE_TARGET_TYPE (type));
	      break;
	    default:
	      error ("cannot subscript or call something of type `%s'",
		     ada_type_name (VALUE_TYPE (argvec[0])));
	      break;
	    }
	}

      switch (TYPE_CODE (type))
	{
	case TYPE_CODE_FUNC:
	  if (noside == EVAL_AVOID_SIDE_EFFECTS)
	    return allocate_value (TYPE_TARGET_TYPE (type));
	  return call_function_by_hand (argvec[0], nargs, argvec + 1);
	case TYPE_CODE_STRUCT:
	  {
	    int arity = ada_array_arity (type);
	    type = ada_array_element_type (type, nargs);
	    if (type == NULL)
	      error ("cannot subscript or call a record");
	    if (arity != nargs)
	      error ("wrong number of subscripts; expecting %d", arity);
	    if (noside == EVAL_AVOID_SIDE_EFFECTS)
	      return allocate_value (ada_aligned_type (type));
	    return
	      unwrap_value (ada_value_subscript
			    (argvec[0], nargs, argvec + 1));
	  }
	case TYPE_CODE_ARRAY:
	  if (noside == EVAL_AVOID_SIDE_EFFECTS)
	    {
	      type = ada_array_element_type (type, nargs);
	      if (type == NULL)
		error ("element type of array unknown");
	      else
		return allocate_value (ada_aligned_type (type));
	    }
	  return
	    unwrap_value (ada_value_subscript
			  (ada_coerce_to_simple_array (argvec[0]),
			   nargs, argvec + 1));
	case TYPE_CODE_PTR:	/* Pointer to array */
	  type = to_fixed_array_type (TYPE_TARGET_TYPE (type), NULL, 1);
	  if (noside == EVAL_AVOID_SIDE_EFFECTS)
	    {
	      type = ada_array_element_type (type, nargs);
	      if (type == NULL)
		error ("element type of array unknown");
	      else
		return allocate_value (ada_aligned_type (type));
	    }
	  return
	    unwrap_value (ada_value_ptr_subscript (argvec[0], type,
						   nargs, argvec + 1));

	default:
	  error ("Internal error in evaluate_subexp");
	}

    case TERNOP_SLICE:
      {
	struct value *array = evaluate_subexp (NULL_TYPE, exp, pos, noside);
	int lowbound
	  = value_as_long (evaluate_subexp (NULL_TYPE, exp, pos, noside));
	int upper
	  = value_as_long (evaluate_subexp (NULL_TYPE, exp, pos, noside));
	if (noside == EVAL_SKIP)
	  goto nosideret;

	/* If this is a reference to an array, then dereference it */
	if (TYPE_CODE (VALUE_TYPE (array)) == TYPE_CODE_REF
	    && TYPE_TARGET_TYPE (VALUE_TYPE (array)) != NULL
	    && TYPE_CODE (TYPE_TARGET_TYPE (VALUE_TYPE (array))) ==
	    TYPE_CODE_ARRAY
	    && !ada_is_array_descriptor (check_typedef (VALUE_TYPE (array))))
	  {
	    array = ada_coerce_ref (array);
	  }

	if (noside == EVAL_AVOID_SIDE_EFFECTS &&
	    ada_is_array_descriptor (check_typedef (VALUE_TYPE (array))))
	  {
	    /* Try to dereference the array, in case it is an access to array */
	    struct type *arrType = ada_type_of_array (array, 0);
	    if (arrType != NULL)
	      array = value_at_lazy (arrType, 0, NULL);
	  }
	if (ada_is_array_descriptor (VALUE_TYPE (array)))
	  array = ada_coerce_to_simple_array (array);

	/* If at this point we have a pointer to an array, it means that
	   it is a pointer to a simple (non-ada) array. We just then
	   dereference it */
	if (TYPE_CODE (VALUE_TYPE (array)) == TYPE_CODE_PTR
	    && TYPE_TARGET_TYPE (VALUE_TYPE (array)) != NULL
	    && TYPE_CODE (TYPE_TARGET_TYPE (VALUE_TYPE (array))) ==
	    TYPE_CODE_ARRAY)
	  {
	    array = ada_value_ind (array);
	  }

	if (noside == EVAL_AVOID_SIDE_EFFECTS)
	  /* The following will get the bounds wrong, but only in contexts
	     where the value is not being requested (FIXME?). */
	  return array;
	else
	  return value_slice (array, lowbound, upper - lowbound + 1);
      }

      /* FIXME: UNOP_MBR should be defined in expression.h */
      /*    case UNOP_MBR:
         (*pos) += 2;
         arg1 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
         type = exp->elts[pc + 1].type;

         if (noside == EVAL_SKIP)
         goto nosideret;

         switch (TYPE_CODE (type)) 
         {
         default:
         warning ("Membership test incompletely implemented; always returns true");
         return value_from_longest (builtin_type_int, (LONGEST) 1);

         case TYPE_CODE_RANGE:
         arg2 = value_from_longest (builtin_type_int, 
         (LONGEST) TYPE_LOW_BOUND (type));
         arg3 = value_from_longest (builtin_type_int, 
         (LONGEST) TYPE_HIGH_BOUND (type));
         return 
         value_from_longest (builtin_type_int,
         (value_less (arg1,arg3) 
         || value_equal (arg1,arg3))
         && (value_less (arg2,arg1)
         || value_equal (arg2,arg1)));
         }
       */
      /* FIXME: BINOP_MBR should be defined in expression.h */
      /*    case BINOP_MBR:
         (*pos) += 2;
         arg1 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
         arg2 = evaluate_subexp (NULL_TYPE, exp, pos, noside);

         if (noside == EVAL_SKIP)
         goto nosideret;

         if (noside == EVAL_AVOID_SIDE_EFFECTS)
         return value_zero (builtin_type_int, not_lval);

         tem = longest_to_int (exp->elts[pc + 1].longconst);

         if (tem < 1 || tem > ada_array_arity (VALUE_TYPE (arg2)))
         error ("invalid dimension number to '%s", "range");

         arg3 = ada_array_bound (arg2, tem, 1);
         arg2 = ada_array_bound (arg2, tem, 0);

         return 
         value_from_longest (builtin_type_int,
         (value_less (arg1,arg3) 
         || value_equal (arg1,arg3))
         && (value_less (arg2,arg1)
         || value_equal (arg2,arg1)));
       */
      /* FIXME: TERNOP_MBR should be defined in expression.h */
      /*    case TERNOP_MBR:
         arg1 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
         arg2 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
         arg3 = evaluate_subexp (NULL_TYPE, exp, pos, noside);

         if (noside == EVAL_SKIP)
         goto nosideret;

         return 
         value_from_longest (builtin_type_int,
         (value_less (arg1,arg3) 
         || value_equal (arg1,arg3))
         && (value_less (arg2,arg1)
         || value_equal (arg2,arg1)));
       */
      /* FIXME: OP_ATTRIBUTE should be defined in expression.h */
      /*    case OP_ATTRIBUTE:
         *pos += 3;
         atr = (enum ada_attribute) longest_to_int (exp->elts[pc + 2].longconst);
         switch (atr) 
         {
         default:
         error ("unexpected attribute encountered");

         case ATR_FIRST:
         case ATR_LAST:
         case ATR_LENGTH:
         {
         struct type* type_arg;
         if (exp->elts[*pos].opcode == OP_TYPE)
         {
         evaluate_subexp (NULL_TYPE, exp, pos, EVAL_SKIP);
         arg1 = NULL;
         type_arg = exp->elts[pc + 5].type;
         }
         else
         {
         arg1 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
         type_arg = NULL;
         }

         if (exp->elts[*pos].opcode != OP_LONG) 
         error ("illegal operand to '%s", ada_attribute_name (atr));
         tem = longest_to_int (exp->elts[*pos+2].longconst);
         *pos += 4;

         if (noside == EVAL_SKIP)
         goto nosideret;

         if (type_arg == NULL)
         {
         arg1 = ada_coerce_ref (arg1);

         if (ada_is_packed_array_type (VALUE_TYPE (arg1)))
         arg1 = ada_coerce_to_simple_array (arg1);

         if (tem < 1 || tem > ada_array_arity (VALUE_TYPE (arg1)))
         error ("invalid dimension number to '%s", 
         ada_attribute_name (atr));

         if (noside == EVAL_AVOID_SIDE_EFFECTS)
         {
         type = ada_index_type (VALUE_TYPE (arg1), tem);
         if (type == NULL) 
         error ("attempt to take bound of something that is not an array");
         return allocate_value (type);
         }

         switch (atr) 
         {
         default: 
         error ("unexpected attribute encountered");
         case ATR_FIRST:
         return ada_array_bound (arg1, tem, 0);
         case ATR_LAST:
         return ada_array_bound (arg1, tem, 1);
         case ATR_LENGTH:
         return ada_array_length (arg1, tem);
         }
         }
         else if (TYPE_CODE (type_arg) == TYPE_CODE_RANGE
         || TYPE_CODE (type_arg) == TYPE_CODE_INT) 
         {
         struct type* range_type;
         char* name = ada_type_name (type_arg);
         if (name == NULL)
         {
         if (TYPE_CODE (type_arg) == TYPE_CODE_RANGE) 
         range_type = type_arg;
         else
         error ("unimplemented type attribute");
         }
         else 
         range_type = 
         to_fixed_range_type (name, NULL, TYPE_OBJFILE (type_arg));
         switch (atr) 
         {
         default: 
         error ("unexpected attribute encountered");
         case ATR_FIRST:
         return value_from_longest (TYPE_TARGET_TYPE (range_type),
         TYPE_LOW_BOUND (range_type));
         case ATR_LAST:
         return value_from_longest (TYPE_TARGET_TYPE (range_type),
         TYPE_HIGH_BOUND (range_type));
         }
         }              
         else if (TYPE_CODE (type_arg) == TYPE_CODE_ENUM)
         {
         switch (atr) 
         {
         default: 
         error ("unexpected attribute encountered");
         case ATR_FIRST:
         return value_from_longest 
         (type_arg, TYPE_FIELD_BITPOS (type_arg, 0));
         case ATR_LAST:
         return value_from_longest 
         (type_arg, 
         TYPE_FIELD_BITPOS (type_arg,
         TYPE_NFIELDS (type_arg) - 1));
         }
         }
         else if (TYPE_CODE (type_arg) == TYPE_CODE_FLT)
         error ("unimplemented type attribute");
         else 
         {
         LONGEST low, high;

         if (ada_is_packed_array_type (type_arg))
         type_arg = decode_packed_array_type (type_arg);

         if (tem < 1 || tem > ada_array_arity (type_arg))
         error ("invalid dimension number to '%s", 
         ada_attribute_name (atr));

         if (noside == EVAL_AVOID_SIDE_EFFECTS)
         {
         type = ada_index_type (type_arg, tem);
         if (type == NULL) 
         error ("attempt to take bound of something that is not an array");
         return allocate_value (type);
         }

         switch (atr) 
         {
         default: 
         error ("unexpected attribute encountered");
         case ATR_FIRST:
         low = ada_array_bound_from_type (type_arg, tem, 0, &type);
         return value_from_longest (type, low);
         case ATR_LAST:
         high = ada_array_bound_from_type (type_arg, tem, 1, &type);
         return value_from_longest (type, high);
         case ATR_LENGTH:
         low = ada_array_bound_from_type (type_arg, tem, 0, &type);
         high = ada_array_bound_from_type (type_arg, tem, 1, NULL);
         return value_from_longest (type, high-low+1);
         }
         }
         }

         case ATR_TAG:
         arg1 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
         if (noside == EVAL_SKIP)
         goto nosideret;

         if (noside == EVAL_AVOID_SIDE_EFFECTS)
         return         
         value_zero (ada_tag_type (arg1), not_lval);

         return ada_value_tag (arg1);

         case ATR_MIN:
         case ATR_MAX:
         evaluate_subexp (NULL_TYPE, exp, pos, EVAL_SKIP);
         arg1 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
         arg2 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
         if (noside == EVAL_SKIP)
         goto nosideret;
         else if (noside == EVAL_AVOID_SIDE_EFFECTS)
         return value_zero (VALUE_TYPE (arg1), not_lval);
         else
         return value_binop (arg1, arg2, 
         atr == ATR_MIN ? BINOP_MIN : BINOP_MAX);

         case ATR_MODULUS:
         {
         struct type* type_arg = exp->elts[pc + 5].type;
         evaluate_subexp (NULL_TYPE, exp, pos, EVAL_SKIP);
         *pos += 4;

         if (noside == EVAL_SKIP)
         goto nosideret;

         if (! ada_is_modular_type (type_arg))
         error ("'modulus must be applied to modular type");

         return value_from_longest (TYPE_TARGET_TYPE (type_arg),
         ada_modulus (type_arg));
         }


         case ATR_POS:
         evaluate_subexp (NULL_TYPE, exp, pos, EVAL_SKIP);
         arg1 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
         if (noside == EVAL_SKIP)
         goto nosideret;
         else if (noside == EVAL_AVOID_SIDE_EFFECTS)
         return value_zero (builtin_type_ada_int, not_lval);
         else 
         return value_pos_atr (arg1);

         case ATR_SIZE:
         arg1 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
         if (noside == EVAL_SKIP)
         goto nosideret;
         else if (noside == EVAL_AVOID_SIDE_EFFECTS)
         return value_zero (builtin_type_ada_int, not_lval);
         else
         return value_from_longest (builtin_type_ada_int,
         TARGET_CHAR_BIT 
         * TYPE_LENGTH (VALUE_TYPE (arg1)));

         case ATR_VAL:
         evaluate_subexp (NULL_TYPE, exp, pos, EVAL_SKIP);
         arg1 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
         type = exp->elts[pc + 5].type;
         if (noside == EVAL_SKIP)
         goto nosideret;
         else if (noside == EVAL_AVOID_SIDE_EFFECTS)
         return value_zero (type, not_lval);
         else 
         return value_val_atr (type, arg1);
         } */
    case BINOP_EXP:
      arg1 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
      arg2 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
      if (noside == EVAL_SKIP)
	goto nosideret;
      if (binop_user_defined_p (op, arg1, arg2))
	return unwrap_value (value_x_binop (arg1, arg2, op, OP_NULL,
					    EVAL_NORMAL));
      else if (noside == EVAL_AVOID_SIDE_EFFECTS)
	return value_zero (VALUE_TYPE (arg1), not_lval);
      else
	return value_binop (arg1, arg2, op);

    case UNOP_PLUS:
      arg1 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
      if (noside == EVAL_SKIP)
	goto nosideret;
      if (unop_user_defined_p (op, arg1))
	return unwrap_value (value_x_unop (arg1, op, EVAL_NORMAL));
      else
	return arg1;

    case UNOP_ABS:
      arg1 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
      if (noside == EVAL_SKIP)
	goto nosideret;
      if (value_less (arg1, value_zero (VALUE_TYPE (arg1), not_lval)))
	return value_neg (arg1);
      else
	return arg1;

    case UNOP_IND:
      if (expect_type && TYPE_CODE (expect_type) == TYPE_CODE_PTR)
	expect_type = TYPE_TARGET_TYPE (check_typedef (expect_type));
      arg1 = evaluate_subexp (expect_type, exp, pos, noside);
      if (noside == EVAL_SKIP)
	goto nosideret;
      type = check_typedef (VALUE_TYPE (arg1));
      if (noside == EVAL_AVOID_SIDE_EFFECTS)
	{
	  if (ada_is_array_descriptor (type))
	    /* GDB allows dereferencing GNAT array descriptors. */
	    {
	      struct type *arrType = ada_type_of_array (arg1, 0);
	      if (arrType == NULL)
		error ("Attempt to dereference null array pointer.");
	      return value_at_lazy (arrType, 0, NULL);
	    }
	  else if (TYPE_CODE (type) == TYPE_CODE_PTR
		   || TYPE_CODE (type) == TYPE_CODE_REF
		   /* In C you can dereference an array to get the 1st elt.  */
		   || TYPE_CODE (type) == TYPE_CODE_ARRAY)
	    return
	      value_zero
	      (to_static_fixed_type
	       (ada_aligned_type (check_typedef (TYPE_TARGET_TYPE (type)))),
	       lval_memory);
	  else if (TYPE_CODE (type) == TYPE_CODE_INT)
	    /* GDB allows dereferencing an int.  */
	    return value_zero (builtin_type_int, lval_memory);
	  else
	    error ("Attempt to take contents of a non-pointer value.");
	}
      arg1 = ada_coerce_ref (arg1);
      type = check_typedef (VALUE_TYPE (arg1));

      if (ada_is_array_descriptor (type))
	/* GDB allows dereferencing GNAT array descriptors. */
	return ada_coerce_to_simple_array (arg1);
      else
	return ada_value_ind (arg1);

    case STRUCTOP_STRUCT:
      tem = longest_to_int (exp->elts[pc + 1].longconst);
      (*pos) += 3 + BYTES_TO_EXP_ELEM (tem + 1);
      arg1 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
      if (noside == EVAL_SKIP)
	goto nosideret;
      if (noside == EVAL_AVOID_SIDE_EFFECTS)
	return value_zero (ada_aligned_type
			   (ada_lookup_struct_elt_type (VALUE_TYPE (arg1),
							&exp->elts[pc +
								   2].string,
							0, NULL)),
			   lval_memory);
      else
	return unwrap_value (ada_value_struct_elt (arg1,
						   &exp->elts[pc + 2].string,
						   "record"));
    case OP_TYPE:
      /* The value is not supposed to be used. This is here to make it
         easier to accommodate expressions that contain types. */
      (*pos) += 2;
      if (noside == EVAL_SKIP)
	goto nosideret;
      else if (noside == EVAL_AVOID_SIDE_EFFECTS)
	return allocate_value (builtin_type_void);
      else
	error ("Attempt to use a type name as an expression");

    case STRUCTOP_PTR:
      tem = longest_to_int (exp->elts[pc + 1].longconst);
      (*pos) += 3 + BYTES_TO_EXP_ELEM (tem + 1);
      arg1 = evaluate_subexp (NULL_TYPE, exp, pos, noside);
      if (noside == EVAL_SKIP)
	goto nosideret;
      if (noside == EVAL_AVOID_SIDE_EFFECTS)
	return value_zero (ada_aligned_type
			   (ada_lookup_struct_elt_type (VALUE_TYPE (arg1),
							&exp->elts[pc +
								   2].string,
							0, NULL)),
			   lval_memory);
      else
	return unwrap_value (ada_value_struct_elt (arg1,
						   &exp->elts[pc + 2].string,
						   "record access"));
    }

nosideret:
  return value_from_longest (builtin_type_long, (LONGEST) 1);
}