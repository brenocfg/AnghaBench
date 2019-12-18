#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char* tree ;
struct z_candidate {TYPE_1__** convs; } ;
struct TYPE_4__ {scalar_t__ kind; int /*<<< orphan*/  bad_p; } ;
typedef  TYPE_1__ conversion ;

/* Variables and functions */
 scalar_t__ ARITHMETIC_TYPE_P (char*) ; 
 scalar_t__ BLOCK_POINTER_TYPE ; 
 scalar_t__ CLASS_TYPE_P (char*) ; 
 int /*<<< orphan*/  COND_EXPR ; 
 scalar_t__ ENUMERAL_TYPE ; 
 int /*<<< orphan*/  LOOKUP_NORMAL ; 
 int /*<<< orphan*/  NOP_EXPR ; 
 char* NULL_TREE ; 
 scalar_t__ THROW_EXPR ; 
 scalar_t__ TREE_CODE (char*) ; 
 char* TREE_TYPE (char*) ; 
 scalar_t__ TYPE_PTRMEMFUNC_P (char*) ; 
 scalar_t__ TYPE_PTRMEM_P (char*) ; 
 scalar_t__ TYPE_PTR_P (char*) ; 
 scalar_t__ TYPE_PTR_TO_MEMBER_P (char*) ; 
 int TYPE_QUALS (char*) ; 
 scalar_t__ VOID_TYPE_P (char*) ; 
 int /*<<< orphan*/  add_builtin_candidates (struct z_candidate**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ansi_opname (int /*<<< orphan*/ ) ; 
 char* boolean_type_node ; 
 int /*<<< orphan*/  build3 (int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 scalar_t__ ck_ambig ; 
 char* composite_pointer_type (char*,char*,char*,char*,char*) ; 
 TYPE_1__* conditional_conversion (char*,char*) ; 
 int /*<<< orphan*/  conversion_obstack ; 
 void* conversion_obstack_alloc (int /*<<< orphan*/ ) ; 
 char* convert_from_reference (char*) ; 
 char* convert_like (TYPE_1__*,char*) ; 
 char* cp_build_qualified_type (char*,int) ; 
 char* decay_conversion (char*) ; 
 int /*<<< orphan*/  error (char*,char*,...) ; 
 char* error_mark_node ; 
 scalar_t__ error_operand_p (char*) ; 
 scalar_t__ extra_warnings ; 
 char* fold_if_not_in_template (int /*<<< orphan*/ ) ; 
 char* force_rvalue (char*) ; 
 char* get_target_expr (char*) ; 
 scalar_t__ null_ptr_cst_p (char*) ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  op_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 scalar_t__ pedantic ; 
 int /*<<< orphan*/  pedwarn (char*) ; 
 char* perform_implicit_conversion (char*,char*) ; 
 int /*<<< orphan*/  print_z_candidates (struct z_candidate*) ; 
 scalar_t__ real_lvalue_p (char*) ; 
 char* rvalue (char*) ; 
 scalar_t__ same_type_p (char*,char*) ; 
 char* save_expr (char*) ; 
 struct z_candidate* splice_viable (struct z_candidate*,scalar_t__,int*) ; 
 char* stabilize_reference (char*) ; 
 struct z_candidate* tourney (struct z_candidate*) ; 
 char* type_after_usual_arithmetic_conversions (char*,char*) ; 
 char* type_promotes_to (char*) ; 
 char* unlowered_expr_type (char*) ; 
 char* void_type_node ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,...) ; 

tree
build_conditional_expr (tree arg1, tree arg2, tree arg3)
{
  tree arg2_type;
  tree arg3_type;
  tree result = NULL_TREE;
  tree result_type = NULL_TREE;
  bool lvalue_p = true;
  struct z_candidate *candidates = 0;
  struct z_candidate *cand;
  void *p;

  /* As a G++ extension, the second argument to the conditional can be
     omitted.  (So that `a ? : c' is roughly equivalent to `a ? a :
     c'.)  If the second operand is omitted, make sure it is
     calculated only once.  */
  if (!arg2)
    {
      if (pedantic)
	pedwarn ("ISO C++ forbids omitting the middle term of a ?: expression");

      /* Make sure that lvalues remain lvalues.  See g++.oliva/ext1.C.  */
      if (real_lvalue_p (arg1))
	arg2 = arg1 = stabilize_reference (arg1);
      else
	arg2 = arg1 = save_expr (arg1);
    }

  /* [expr.cond]

     The first expr ession is implicitly converted to bool (clause
     _conv_).  */
  arg1 = perform_implicit_conversion (boolean_type_node, arg1);

  /* If something has already gone wrong, just pass that fact up the
     tree.  */
  if (error_operand_p (arg1)
      || error_operand_p (arg2)
      || error_operand_p (arg3))
    return error_mark_node;

  /* [expr.cond]

     If either the second or the third operand has type (possibly
     cv-qualified) void, then the lvalue-to-rvalue (_conv.lval_),
     array-to-pointer (_conv.array_), and function-to-pointer
     (_conv.func_) standard conversions are performed on the second
     and third operands.  */
  arg2_type = unlowered_expr_type (arg2);
  arg3_type = unlowered_expr_type (arg3);
  if (VOID_TYPE_P (arg2_type) || VOID_TYPE_P (arg3_type))
    {
      /* Do the conversions.  We don't these for `void' type arguments
	 since it can't have any effect and since decay_conversion
	 does not handle that case gracefully.  */
      if (!VOID_TYPE_P (arg2_type))
	arg2 = decay_conversion (arg2);
      if (!VOID_TYPE_P (arg3_type))
	arg3 = decay_conversion (arg3);
      arg2_type = TREE_TYPE (arg2);
      arg3_type = TREE_TYPE (arg3);

      /* [expr.cond]

	 One of the following shall hold:

	 --The second or the third operand (but not both) is a
	   throw-expression (_except.throw_); the result is of the
	   type of the other and is an rvalue.

	 --Both the second and the third operands have type void; the
	   result is of type void and is an rvalue.

	 We must avoid calling force_rvalue for expressions of type
	 "void" because it will complain that their value is being
	 used.  */
      if (TREE_CODE (arg2) == THROW_EXPR
	  && TREE_CODE (arg3) != THROW_EXPR)
	{
	  if (!VOID_TYPE_P (arg3_type))
	    arg3 = force_rvalue (arg3);
	  arg3_type = TREE_TYPE (arg3);
	  result_type = arg3_type;
	}
      else if (TREE_CODE (arg2) != THROW_EXPR
	       && TREE_CODE (arg3) == THROW_EXPR)
	{
	  if (!VOID_TYPE_P (arg2_type))
	    arg2 = force_rvalue (arg2);
	  arg2_type = TREE_TYPE (arg2);
	  result_type = arg2_type;
	}
      else if (VOID_TYPE_P (arg2_type) && VOID_TYPE_P (arg3_type))
	result_type = void_type_node;
      else
	{
	  error ("%qE has type %<void%> and is not a throw-expression",
		    VOID_TYPE_P (arg2_type) ? arg2 : arg3);
	  return error_mark_node;
	}

      lvalue_p = false;
      goto valid_operands;
    }
  /* [expr.cond]

     Otherwise, if the second and third operand have different types,
     and either has (possibly cv-qualified) class type, an attempt is
     made to convert each of those operands to the type of the other.  */
  else if (!same_type_p (arg2_type, arg3_type)
	   && (CLASS_TYPE_P (arg2_type) || CLASS_TYPE_P (arg3_type)))
    {
      conversion *conv2;
      conversion *conv3;

      /* Get the high-water mark for the CONVERSION_OBSTACK.  */
      p = conversion_obstack_alloc (0);

      conv2 = conditional_conversion (arg2, arg3);
      conv3 = conditional_conversion (arg3, arg2);

      /* [expr.cond]

	 If both can be converted, or one can be converted but the
	 conversion is ambiguous, the program is ill-formed.  If
	 neither can be converted, the operands are left unchanged and
	 further checking is performed as described below.  If exactly
	 one conversion is possible, that conversion is applied to the
	 chosen operand and the converted operand is used in place of
	 the original operand for the remainder of this section.  */
      if ((conv2 && !conv2->bad_p
	   && conv3 && !conv3->bad_p)
	  || (conv2 && conv2->kind == ck_ambig)
	  || (conv3 && conv3->kind == ck_ambig))
	{
	  error ("operands to ?: have different types %qT and %qT",
		 arg2_type, arg3_type);
	  result = error_mark_node;
	}
      else if (conv2 && (!conv2->bad_p || !conv3))
	{
	  arg2 = convert_like (conv2, arg2);
	  arg2 = convert_from_reference (arg2);
	  arg2_type = TREE_TYPE (arg2);
	  /* Even if CONV2 is a valid conversion, the result of the
	     conversion may be invalid.  For example, if ARG3 has type
	     "volatile X", and X does not have a copy constructor
	     accepting a "volatile X&", then even if ARG2 can be
	     converted to X, the conversion will fail.  */
	  if (error_operand_p (arg2))
	    result = error_mark_node;
	}
      else if (conv3 && (!conv3->bad_p || !conv2))
	{
	  arg3 = convert_like (conv3, arg3);
	  arg3 = convert_from_reference (arg3);
	  arg3_type = TREE_TYPE (arg3);
	  if (error_operand_p (arg3))
	    result = error_mark_node;
	}

      /* Free all the conversions we allocated.  */
      obstack_free (&conversion_obstack, p);

      if (result)
	return result;

      /* If, after the conversion, both operands have class type,
	 treat the cv-qualification of both operands as if it were the
	 union of the cv-qualification of the operands.

	 The standard is not clear about what to do in this
	 circumstance.  For example, if the first operand has type
	 "const X" and the second operand has a user-defined
	 conversion to "volatile X", what is the type of the second
	 operand after this step?  Making it be "const X" (matching
	 the first operand) seems wrong, as that discards the
	 qualification without actually performing a copy.  Leaving it
	 as "volatile X" seems wrong as that will result in the
	 conditional expression failing altogether, even though,
	 according to this step, the one operand could be converted to
	 the type of the other.  */
      if ((conv2 || conv3)
	  && CLASS_TYPE_P (arg2_type)
	  && TYPE_QUALS (arg2_type) != TYPE_QUALS (arg3_type))
	arg2_type = arg3_type =
	  cp_build_qualified_type (arg2_type,
				   TYPE_QUALS (arg2_type)
				   | TYPE_QUALS (arg3_type));
    }

  /* [expr.cond]

     If the second and third operands are lvalues and have the same
     type, the result is of that type and is an lvalue.  */
  if (real_lvalue_p (arg2)
      && real_lvalue_p (arg3)
      && same_type_p (arg2_type, arg3_type))
    {
      result_type = arg2_type;
      goto valid_operands;
    }

  /* [expr.cond]

     Otherwise, the result is an rvalue.  If the second and third
     operand do not have the same type, and either has (possibly
     cv-qualified) class type, overload resolution is used to
     determine the conversions (if any) to be applied to the operands
     (_over.match.oper_, _over.built_).  */
  lvalue_p = false;
  if (!same_type_p (arg2_type, arg3_type)
      && (CLASS_TYPE_P (arg2_type) || CLASS_TYPE_P (arg3_type)))
    {
      tree args[3];
      conversion *conv;
      bool any_viable_p;

      /* Rearrange the arguments so that add_builtin_candidate only has
	 to know about two args.  In build_builtin_candidates, the
	 arguments are unscrambled.  */
      args[0] = arg2;
      args[1] = arg3;
      args[2] = arg1;
      add_builtin_candidates (&candidates,
			      COND_EXPR,
			      NOP_EXPR,
			      ansi_opname (COND_EXPR),
			      args,
			      LOOKUP_NORMAL);

      /* [expr.cond]

	 If the overload resolution fails, the program is
	 ill-formed.  */
      candidates = splice_viable (candidates, pedantic, &any_viable_p);
      if (!any_viable_p)
	{
	  op_error (COND_EXPR, NOP_EXPR, arg1, arg2, arg3, "no match");
	  print_z_candidates (candidates);
	  return error_mark_node;
	}
      cand = tourney (candidates);
      if (!cand)
	{
	  op_error (COND_EXPR, NOP_EXPR, arg1, arg2, arg3, "no match");
	  print_z_candidates (candidates);
	  return error_mark_node;
	}

      /* [expr.cond]

	 Otherwise, the conversions thus determined are applied, and
	 the converted operands are used in place of the original
	 operands for the remainder of this section.  */
      conv = cand->convs[0];
      arg1 = convert_like (conv, arg1);
      conv = cand->convs[1];
      arg2 = convert_like (conv, arg2);
      conv = cand->convs[2];
      arg3 = convert_like (conv, arg3);
    }

  /* [expr.cond]

     Lvalue-to-rvalue (_conv.lval_), array-to-pointer (_conv.array_),
     and function-to-pointer (_conv.func_) standard conversions are
     performed on the second and third operands.

     We need to force the lvalue-to-rvalue conversion here for class types,
     so we get TARGET_EXPRs; trying to deal with a COND_EXPR of class rvalues
     that isn't wrapped with a TARGET_EXPR plays havoc with exception
     regions.  */

  arg2 = force_rvalue (arg2);
  if (!CLASS_TYPE_P (arg2_type))
    arg2_type = TREE_TYPE (arg2);

  arg3 = force_rvalue (arg3);
  if (!CLASS_TYPE_P (arg2_type))
    arg3_type = TREE_TYPE (arg3);

  if (arg2 == error_mark_node || arg3 == error_mark_node)
    return error_mark_node;

  /* [expr.cond]

     After those conversions, one of the following shall hold:

     --The second and third operands have the same type; the result  is  of
       that type.  */
  if (same_type_p (arg2_type, arg3_type))
    result_type = arg2_type;
  /* [expr.cond]

     --The second and third operands have arithmetic or enumeration
       type; the usual arithmetic conversions are performed to bring
       them to a common type, and the result is of that type.  */
  else if ((ARITHMETIC_TYPE_P (arg2_type)
	    || TREE_CODE (arg2_type) == ENUMERAL_TYPE)
	   && (ARITHMETIC_TYPE_P (arg3_type)
	       || TREE_CODE (arg3_type) == ENUMERAL_TYPE))
    {
      /* In this case, there is always a common type.  */
      result_type = type_after_usual_arithmetic_conversions (arg2_type,
							     arg3_type);

      if (TREE_CODE (arg2_type) == ENUMERAL_TYPE
	  && TREE_CODE (arg3_type) == ENUMERAL_TYPE)
	 warning (0, "enumeral mismatch in conditional expression: %qT vs %qT",
		   arg2_type, arg3_type);
      else if (extra_warnings
	       && ((TREE_CODE (arg2_type) == ENUMERAL_TYPE
		    && !same_type_p (arg3_type, type_promotes_to (arg2_type)))
		   || (TREE_CODE (arg3_type) == ENUMERAL_TYPE
		       && !same_type_p (arg2_type, type_promotes_to (arg3_type)))))
	warning (0, "enumeral and non-enumeral type in conditional expression");

      arg2 = perform_implicit_conversion (result_type, arg2);
      arg3 = perform_implicit_conversion (result_type, arg3);
    }
  /* [expr.cond]

     --The second and third operands have pointer type, or one has
       pointer type and the other is a null pointer constant; pointer
       conversions (_conv.ptr_) and qualification conversions
       (_conv.qual_) are performed to bring them to their composite
       pointer type (_expr.rel_).  The result is of the composite
       pointer type.

     --The second and third operands have pointer to member type, or
       one has pointer to member type and the other is a null pointer
       constant; pointer to member conversions (_conv.mem_) and
       qualification conversions (_conv.qual_) are performed to bring
       them to a common type, whose cv-qualification shall match the
       cv-qualification of either the second or the third operand.
       The result is of the common type.  */
  else if ((null_ptr_cst_p (arg2)
	   /* APPLE LOCAL begin blocks 6040305 (co) */
	    && (TYPE_PTR_P (arg3_type) || TYPE_PTR_TO_MEMBER_P (arg3_type)
		|| TREE_CODE (arg3_type) == BLOCK_POINTER_TYPE))
	   /* APPLE LOCAL end blocks 6040305 (co) */
	   || (null_ptr_cst_p (arg3)
	   /* APPLE LOCAL begin blocks 6040305 (co) */
	       && (TYPE_PTR_P (arg2_type) || TYPE_PTR_TO_MEMBER_P (arg2_type)
		   || TREE_CODE (arg2_type) == BLOCK_POINTER_TYPE))
	   || ((TYPE_PTR_P (arg2_type)
		||  TREE_CODE (arg2_type) == BLOCK_POINTER_TYPE)
	       && (TYPE_PTR_P (arg3_type)
		   || TREE_CODE (arg3_type) == BLOCK_POINTER_TYPE))
	   /* APPLE LOCAL end blocks 6040305 (co) */
	   || (TYPE_PTRMEM_P (arg2_type) && TYPE_PTRMEM_P (arg3_type))
	   || (TYPE_PTRMEMFUNC_P (arg2_type) && TYPE_PTRMEMFUNC_P (arg3_type)))
    {
      result_type = composite_pointer_type (arg2_type, arg3_type, arg2,
					    arg3, "conditional expression");
      if (result_type == error_mark_node)
	return error_mark_node;
      arg2 = perform_implicit_conversion (result_type, arg2);
      arg3 = perform_implicit_conversion (result_type, arg3);
    }

  if (!result_type)
    {
      error ("operands to ?: have different types %qT and %qT",
	     arg2_type, arg3_type);
      return error_mark_node;
    }

 valid_operands:
  result = fold_if_not_in_template (build3 (COND_EXPR, result_type, arg1,
					    arg2, arg3));
  /* We can't use result_type below, as fold might have returned a
     throw_expr.  */

  if (!lvalue_p)
    {
      /* Expand both sides into the same slot, hopefully the target of
	 the ?: expression.  We used to check for TARGET_EXPRs here,
	 but now we sometimes wrap them in NOP_EXPRs so the test would
	 fail.  */
      if (CLASS_TYPE_P (TREE_TYPE (result)))
	result = get_target_expr (result);
      /* If this expression is an rvalue, but might be mistaken for an
	 lvalue, we must add a NON_LVALUE_EXPR.  */
      result = rvalue (result);
    }

  return result;
}