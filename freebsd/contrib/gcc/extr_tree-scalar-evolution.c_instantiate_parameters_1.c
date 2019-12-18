#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct loop {int /*<<< orphan*/  depth; } ;
typedef  int /*<<< orphan*/  htab_t ;
typedef  TYPE_1__* basic_block ;
struct TYPE_6__ {int /*<<< orphan*/  depth; } ;
struct TYPE_5__ {int /*<<< orphan*/  loop_father; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHREC_LEFT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHREC_RIGHT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHREC_VARIABLE (int /*<<< orphan*/ ) ; 
#define  CONVERT_EXPR 137 
 int FOLD_CONVERSIONS ; 
 int INSERT_SUPERLOOP_CHRECS ; 
#define  MINUS_EXPR 136 
#define  MULT_EXPR 135 
#define  NON_LVALUE_EXPR 134 
#define  NOP_EXPR 133 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  PARAM_SCEV_MAX_EXPR_SIZE ; 
 int /*<<< orphan*/  PARAM_VALUE (int /*<<< orphan*/ ) ; 
#define  PLUS_EXPR 132 
#define  POLYNOMIAL_CHREC 131 
#define  SCEV_KNOWN 130 
#define  SCEV_NOT_KNOWN 129 
#define  SSA_NAME 128 
 int /*<<< orphan*/  SSA_NAME_DEF_STMT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSA_NAME_VERSION (int /*<<< orphan*/ ) ; 
 int const TREE_CODE (int /*<<< orphan*/ ) ; 
 int TREE_CODE_LENGTH (int const) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  already_instantiated ; 
 int /*<<< orphan*/  analyze_scalar_evolution (struct loop*,int /*<<< orphan*/ ) ; 
 scalar_t__ automatically_generated_chrec_p (int /*<<< orphan*/ ) ; 
 TYPE_1__* bb_for_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_bit_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_polynomial_chrec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_convert_aggressive (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_dont_know ; 
 int /*<<< orphan*/  chrec_fold_minus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_fold_multiply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_fold_plus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chrec_known ; 
 int /*<<< orphan*/  chrec_type (int /*<<< orphan*/ ) ; 
 struct loop* find_common_loop (struct loop*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flow_bb_inside_loop_p (struct loop*,TYPE_1__*) ; 
 int /*<<< orphan*/  fold_build1 (int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_build2 (int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_build3 (int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_instantiated_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_gimple_min_invariant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loop_closed_phi_def (int /*<<< orphan*/ ) ; 
 TYPE_2__* loop_containing_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_instantiated_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
instantiate_parameters_1 (struct loop *loop, tree chrec, int flags, htab_t cache,
			  int size_expr)
{
  tree res, op0, op1, op2;
  basic_block def_bb;
  struct loop *def_loop;
  tree type = chrec_type (chrec);

  /* Give up if the expression is larger than the MAX that we allow.  */
  if (size_expr++ > PARAM_VALUE (PARAM_SCEV_MAX_EXPR_SIZE))
    return chrec_dont_know;

  if (automatically_generated_chrec_p (chrec)
      || is_gimple_min_invariant (chrec))
    return chrec;

  switch (TREE_CODE (chrec))
    {
    case SSA_NAME:
      def_bb = bb_for_stmt (SSA_NAME_DEF_STMT (chrec));

      /* A parameter (or loop invariant and we do not want to include
	 evolutions in outer loops), nothing to do.  */
      if (!def_bb
	  || (!(flags & INSERT_SUPERLOOP_CHRECS)
	      && !flow_bb_inside_loop_p (loop, def_bb)))
	return chrec;

      /* We cache the value of instantiated variable to avoid exponential
	 time complexity due to reevaluations.  We also store the convenient
	 value in the cache in order to prevent infinite recursion -- we do
	 not want to instantiate the SSA_NAME if it is in a mixer
	 structure.  This is used for avoiding the instantiation of
	 recursively defined functions, such as: 

	 | a_2 -> {0, +, 1, +, a_2}_1  */

      res = get_instantiated_value (cache, chrec);
      if (res)
	return res;

      /* Store the convenient value for chrec in the structure.  If it
	 is defined outside of the loop, we may just leave it in symbolic
	 form, otherwise we need to admit that we do not know its behavior
	 inside the loop.  */
      res = !flow_bb_inside_loop_p (loop, def_bb) ? chrec : chrec_dont_know;
      set_instantiated_value (cache, chrec, res);

      /* To make things even more complicated, instantiate_parameters_1
	 calls analyze_scalar_evolution that may call # of iterations
	 analysis that may in turn call instantiate_parameters_1 again.
	 To prevent the infinite recursion, keep also the bitmap of
	 ssa names that are being instantiated globally.  */
      if (bitmap_bit_p (already_instantiated, SSA_NAME_VERSION (chrec)))
	return res;

      def_loop = find_common_loop (loop, def_bb->loop_father);

      /* If the analysis yields a parametric chrec, instantiate the
	 result again.  */
      bitmap_set_bit (already_instantiated, SSA_NAME_VERSION (chrec));
      res = analyze_scalar_evolution (def_loop, chrec);

      /* Don't instantiate loop-closed-ssa phi nodes.  */
      if (TREE_CODE (res) == SSA_NAME
	  && (loop_containing_stmt (SSA_NAME_DEF_STMT (res)) == NULL
	      || (loop_containing_stmt (SSA_NAME_DEF_STMT (res))->depth
		  > def_loop->depth)))
	{
	  if (res == chrec)
	    res = loop_closed_phi_def (chrec);
	  else
	    res = chrec;

	  if (res == NULL_TREE)
	    res = chrec_dont_know;
	}

      else if (res != chrec_dont_know)
	res = instantiate_parameters_1 (loop, res, flags, cache, size_expr);

      bitmap_clear_bit (already_instantiated, SSA_NAME_VERSION (chrec));

      /* Store the correct value to the cache.  */
      set_instantiated_value (cache, chrec, res);
      return res;

    case POLYNOMIAL_CHREC:
      op0 = instantiate_parameters_1 (loop, CHREC_LEFT (chrec),
				      flags, cache, size_expr);
      if (op0 == chrec_dont_know)
	return chrec_dont_know;

      op1 = instantiate_parameters_1 (loop, CHREC_RIGHT (chrec),
				      flags, cache, size_expr);
      if (op1 == chrec_dont_know)
	return chrec_dont_know;

      if (CHREC_LEFT (chrec) != op0
	  || CHREC_RIGHT (chrec) != op1)
	{
	  op1 = chrec_convert (chrec_type (op0), op1, NULL_TREE);
	  chrec = build_polynomial_chrec (CHREC_VARIABLE (chrec), op0, op1);
	}
      return chrec;

    case PLUS_EXPR:
      op0 = instantiate_parameters_1 (loop, TREE_OPERAND (chrec, 0),
				      flags, cache, size_expr);
      if (op0 == chrec_dont_know)
	return chrec_dont_know;

      op1 = instantiate_parameters_1 (loop, TREE_OPERAND (chrec, 1),
				      flags, cache, size_expr);
      if (op1 == chrec_dont_know)
	return chrec_dont_know;

      if (TREE_OPERAND (chrec, 0) != op0
	  || TREE_OPERAND (chrec, 1) != op1)
	{
	  op0 = chrec_convert (type, op0, NULL_TREE);
	  op1 = chrec_convert (type, op1, NULL_TREE);
	  chrec = chrec_fold_plus (type, op0, op1);
	}
      return chrec;

    case MINUS_EXPR:
      op0 = instantiate_parameters_1 (loop, TREE_OPERAND (chrec, 0),
				      flags, cache, size_expr);
      if (op0 == chrec_dont_know)
	return chrec_dont_know;

      op1 = instantiate_parameters_1 (loop, TREE_OPERAND (chrec, 1),
				      flags, cache, size_expr);
      if (op1 == chrec_dont_know)
	return chrec_dont_know;

      if (TREE_OPERAND (chrec, 0) != op0
	  || TREE_OPERAND (chrec, 1) != op1)
	{
	  op0 = chrec_convert (type, op0, NULL_TREE);
	  op1 = chrec_convert (type, op1, NULL_TREE);
	  chrec = chrec_fold_minus (type, op0, op1);
	}
      return chrec;

    case MULT_EXPR:
      op0 = instantiate_parameters_1 (loop, TREE_OPERAND (chrec, 0),
				      flags, cache, size_expr);
      if (op0 == chrec_dont_know)
	return chrec_dont_know;

      op1 = instantiate_parameters_1 (loop, TREE_OPERAND (chrec, 1),
				      flags, cache, size_expr);
      if (op1 == chrec_dont_know)
	return chrec_dont_know;

      if (TREE_OPERAND (chrec, 0) != op0
	  || TREE_OPERAND (chrec, 1) != op1)
	{
	  op0 = chrec_convert (type, op0, NULL_TREE);
	  op1 = chrec_convert (type, op1, NULL_TREE);
	  chrec = chrec_fold_multiply (type, op0, op1);
	}
      return chrec;

    case NOP_EXPR:
    case CONVERT_EXPR:
    case NON_LVALUE_EXPR:
      op0 = instantiate_parameters_1 (loop, TREE_OPERAND (chrec, 0),
				      flags, cache, size_expr);
      if (op0 == chrec_dont_know)
        return chrec_dont_know;

      if (flags & FOLD_CONVERSIONS)
	{
	  tree tmp = chrec_convert_aggressive (TREE_TYPE (chrec), op0);
	  if (tmp)
	    return tmp;
	}

      if (op0 == TREE_OPERAND (chrec, 0))
	return chrec;

      /* If we used chrec_convert_aggressive, we can no longer assume that
	 signed chrecs do not overflow, as chrec_convert does, so avoid
         calling it in that case.  */
      if (flags & FOLD_CONVERSIONS)
	return fold_convert (TREE_TYPE (chrec), op0);

      return chrec_convert (TREE_TYPE (chrec), op0, NULL_TREE);

    case SCEV_NOT_KNOWN:
      return chrec_dont_know;

    case SCEV_KNOWN:
      return chrec_known;
                                     
    default:
      break;
    }

  switch (TREE_CODE_LENGTH (TREE_CODE (chrec)))
    {
    case 3:
      op0 = instantiate_parameters_1 (loop, TREE_OPERAND (chrec, 0),
				      flags, cache, size_expr);
      if (op0 == chrec_dont_know)
	return chrec_dont_know;

      op1 = instantiate_parameters_1 (loop, TREE_OPERAND (chrec, 1),
				      flags, cache, size_expr);
      if (op1 == chrec_dont_know)
	return chrec_dont_know;

      op2 = instantiate_parameters_1 (loop, TREE_OPERAND (chrec, 2),
				      flags, cache, size_expr);
      if (op2 == chrec_dont_know)
        return chrec_dont_know;

      if (op0 == TREE_OPERAND (chrec, 0)
	  && op1 == TREE_OPERAND (chrec, 1)
	  && op2 == TREE_OPERAND (chrec, 2))
	return chrec;

      return fold_build3 (TREE_CODE (chrec),
			  TREE_TYPE (chrec), op0, op1, op2);

    case 2:
      op0 = instantiate_parameters_1 (loop, TREE_OPERAND (chrec, 0),
				      flags, cache, size_expr);
      if (op0 == chrec_dont_know)
	return chrec_dont_know;

      op1 = instantiate_parameters_1 (loop, TREE_OPERAND (chrec, 1),
				      flags, cache, size_expr);
      if (op1 == chrec_dont_know)
        return chrec_dont_know;

      if (op0 == TREE_OPERAND (chrec, 0)
	  && op1 == TREE_OPERAND (chrec, 1))
	return chrec;
      return fold_build2 (TREE_CODE (chrec), TREE_TYPE (chrec), op0, op1);
	    
    case 1:
      op0 = instantiate_parameters_1 (loop, TREE_OPERAND (chrec, 0),
				      flags, cache, size_expr);
      if (op0 == chrec_dont_know)
        return chrec_dont_know;
      if (op0 == TREE_OPERAND (chrec, 0))
	return chrec;
      return fold_build1 (TREE_CODE (chrec), TREE_TYPE (chrec), op0);

    case 0:
      return chrec;

    default:
      break;
    }

  /* Too complicated to handle.  */
  return chrec_dont_know;
}