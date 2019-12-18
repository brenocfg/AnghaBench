#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  value_set_t ;
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  ANTIC_SAFE_LOADS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARRAY_REF ; 
 int /*<<< orphan*/  CALL_EXPR ; 
 int /*<<< orphan*/  COMPONENT_REF ; 
 int /*<<< orphan*/  INDIRECT_REF ; 
 int /*<<< orphan*/  SSA_NAME ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_CODE (int /*<<< orphan*/ ) ; 
 int TREE_CODE_CLASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALUE_HANDLE ; 
 int /*<<< orphan*/  VALUE_HANDLE_VUSES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  get_value_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_gimple_min_invariant (int /*<<< orphan*/ ) ; 
 int set_contains_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  tcc_binary 134 
#define  tcc_comparison 133 
#define  tcc_declaration 132 
#define  tcc_exceptional 131 
#define  tcc_expression 130 
#define  tcc_reference 129 
#define  tcc_unary 128 
 int /*<<< orphan*/  vuses_dies_in_block_x (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
valid_in_set (value_set_t set, tree expr, basic_block block)
{
 tree vh = get_value_handle (expr);
 switch (TREE_CODE_CLASS (TREE_CODE (expr)))
    {
    case tcc_binary:
    case tcc_comparison:
      {
	tree op1 = TREE_OPERAND (expr, 0);
	tree op2 = TREE_OPERAND (expr, 1);
	return set_contains_value (set, op1) && set_contains_value (set, op2);
      }

    case tcc_unary:
      {
	tree op1 = TREE_OPERAND (expr, 0);
	return set_contains_value (set, op1);
      }

    case tcc_expression:
      {
	if (TREE_CODE (expr) == CALL_EXPR)
	  {
	    tree op0 = TREE_OPERAND (expr, 0);
	    tree arglist = TREE_OPERAND (expr, 1);
	    tree op2 = TREE_OPERAND (expr, 2);

	    /* Check the non-list operands first.  */
	    if (!set_contains_value (set, op0)
		|| (op2 && !set_contains_value (set, op2)))
	      return false;

	    /* Now check the operands.  */
	    for (; arglist; arglist = TREE_CHAIN (arglist))
	      {
		if (!set_contains_value (set, TREE_VALUE (arglist)))
		  return false;
	      }
	    return !vuses_dies_in_block_x (VALUE_HANDLE_VUSES (vh), block);
	  }
	return false;
      }

    case tcc_reference:
      {
	if (TREE_CODE (expr) == INDIRECT_REF
	    || TREE_CODE (expr) == COMPONENT_REF
            || TREE_CODE (expr) == ARRAY_REF)
	  {
	    tree op0 = TREE_OPERAND (expr, 0);
	    gcc_assert (is_gimple_min_invariant (op0)
			|| TREE_CODE (op0) == VALUE_HANDLE);
	    if (!set_contains_value (set, op0))
	      return false;
	    if (TREE_CODE (expr) == ARRAY_REF)
	      {
		tree op1 = TREE_OPERAND (expr, 1);
		tree op2 = TREE_OPERAND (expr, 2);
		tree op3 = TREE_OPERAND (expr, 3);
		gcc_assert (is_gimple_min_invariant (op1)
		            || TREE_CODE (op1) == VALUE_HANDLE);
		if (!set_contains_value (set, op1))
		  return false;
		gcc_assert (!op2 || is_gimple_min_invariant (op2)
		            || TREE_CODE (op2) == VALUE_HANDLE);
		if (op2
		    && !set_contains_value (set, op2))
		  return false;
		gcc_assert (!op3 || is_gimple_min_invariant (op3)
		            || TREE_CODE (op3) == VALUE_HANDLE);
		if (op3
		    && !set_contains_value (set, op3))
		  return false;
	    }
	  return set_contains_value (ANTIC_SAFE_LOADS (block),
				     vh)
	    || !vuses_dies_in_block_x (VALUE_HANDLE_VUSES (vh),
				       block);
	  }
      }
      return false;

    case tcc_exceptional:
      gcc_assert (TREE_CODE (expr) == SSA_NAME);
      return true;

    case tcc_declaration:
      return !vuses_dies_in_block_x (VALUE_HANDLE_VUSES (vh), block);

    default:
      /* No other cases should be encountered.  */
      gcc_unreachable ();
   }
}