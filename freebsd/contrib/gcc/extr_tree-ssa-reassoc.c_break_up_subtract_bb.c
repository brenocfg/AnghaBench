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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  scalar_t__ basic_block ;
typedef  int /*<<< orphan*/  TREE_VISITED ;

/* Variables and functions */
 int /*<<< orphan*/  CDI_DOMINATORS ; 
 int /*<<< orphan*/  INTEGRAL_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ MINUS_EXPR ; 
 scalar_t__ MODIFY_EXPR ; 
 int /*<<< orphan*/  SCALAR_FLOAT_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  break_up_subtract (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bsi_start (scalar_t__) ; 
 int /*<<< orphan*/  bsi_stmt (int /*<<< orphan*/ ) ; 
 scalar_t__ first_dom_son (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  flag_unsafe_math_optimizations ; 
 scalar_t__ next_dom_son (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ should_break_up_subtract (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
break_up_subtract_bb (basic_block bb)
{
  block_stmt_iterator bsi;
  basic_block son;

  for (bsi = bsi_start (bb); !bsi_end_p (bsi); bsi_next (&bsi))
    {
      tree stmt = bsi_stmt (bsi);

      if (TREE_CODE (stmt) == MODIFY_EXPR)
	{
	  tree lhs = TREE_OPERAND (stmt, 0);
	  tree rhs = TREE_OPERAND (stmt, 1);

	  TREE_VISITED (stmt) = 0;
	  /* If unsafe math optimizations we can do reassociation for
	     non-integral types.  */
	  if ((!INTEGRAL_TYPE_P (TREE_TYPE (lhs))
	       || !INTEGRAL_TYPE_P (TREE_TYPE (rhs)))
	      && (!SCALAR_FLOAT_TYPE_P (TREE_TYPE (rhs))
		  || !SCALAR_FLOAT_TYPE_P (TREE_TYPE(lhs))
		  || !flag_unsafe_math_optimizations))
	    continue;

	  /* Check for a subtract used only in an addition.  If this
	     is the case, transform it into add of a negate for better
	     reassociation.  IE transform C = A-B into C = A + -B if C
	     is only used in an addition.  */
	  if (TREE_CODE (rhs) == MINUS_EXPR)
	    if (should_break_up_subtract (stmt))
	      break_up_subtract (stmt, &bsi);
	}
    }
  for (son = first_dom_son (CDI_DOMINATORS, bb);
       son;
       son = next_dom_son (CDI_DOMINATORS, son))
    break_up_subtract_bb (son);
}