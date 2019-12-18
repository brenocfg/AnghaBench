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
typedef  scalar_t__ tree ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
typedef  scalar_t__ TREE_NO_WARNING ;

/* Variables and functions */
 scalar_t__ COMPONENT_REF ; 
 int /*<<< orphan*/  COMPOUND_EXPR ; 
 scalar_t__ COPYABLE_BYREF_LOCAL_VAR (scalar_t__) ; 
 scalar_t__ INDIRECT_REF ; 
 int /*<<< orphan*/  LOOKUP_NORMAL ; 
 int /*<<< orphan*/  MODIFY_EXPR ; 
 int /*<<< orphan*/  MODOP_EXPR ; 
 int NOP_EXPR ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ VAR_DECL ; 
 scalar_t__ build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ build_min_nt (int,scalar_t__,scalar_t__,...) ; 
 scalar_t__ build_modify_expr (scalar_t__,int,scalar_t__) ; 
 scalar_t__ build_new_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_node (int) ; 
 scalar_t__ processing_template_decl ; 
 scalar_t__ save_expr (scalar_t__) ; 

tree
build_x_modify_expr (tree lhs, enum tree_code modifycode, tree rhs)
{
  /* APPLE LOCAL __block assign sequence point 6639533 */
  bool insert_sequence_point = false;

  if (processing_template_decl)
    return build_min_nt (MODOP_EXPR, lhs,
			 build_min_nt (modifycode, NULL_TREE, NULL_TREE), rhs);

  /* APPLE LOCAL begin __block assign sequence point 6639533 */
  /* For byref = x;, we have to transform this into ({ typeof(x) x' =
     x; byref = x`; )} to ensure there is a sequence point before the
     evaluation of the byref, inorder to ensure that the access
     expression for byref doesn't start running before x is evaluated,
     as it will access the __forwarding pointer and that must be done
     after x is evaluated.  */
  /* First we check to see if lhs is a byref...  byrefs look like:
	__Block_byref_X.__forwarding->x  */
  if (TREE_CODE (lhs) == COMPONENT_REF)
    {
      tree inner = TREE_OPERAND (lhs, 0);
      /* now check for -> */
      if (TREE_CODE (inner) == INDIRECT_REF)
	{
	  inner = TREE_OPERAND (inner, 0);
	  if (TREE_CODE (inner) == COMPONENT_REF)
	    {
	      inner = TREE_OPERAND (inner, 0);
	      if (TREE_CODE (inner) == VAR_DECL
		  && COPYABLE_BYREF_LOCAL_VAR (inner))
		{
		  tree old_rhs = rhs;
		  /* then we save the rhs.  */
		  rhs = save_expr (rhs);
		  if (rhs != old_rhs)
		    /* And arrange for the sequence point to be inserted.  */
		    insert_sequence_point = true;
		}
	    }
	}
    }
  /* APPLE LOCAL end __block assign sequence point 6639533 */

  if (modifycode != NOP_EXPR)
    {
      tree rval = build_new_op (MODIFY_EXPR, LOOKUP_NORMAL, lhs, rhs,
				make_node (modifycode),
				/*overloaded_p=*/NULL);
      if (rval)
	{
	  /* APPLE LOCAL begin __block assign sequence point 6639533 */
	  if (insert_sequence_point)
	    rval = build2 (COMPOUND_EXPR, TREE_TYPE (rval), rhs, rval);
	  /* APPLE LOCAL end __block assign sequence point 6639533 */
	  TREE_NO_WARNING (rval) = 1;
	  return rval;
	}
    }
  lhs = build_modify_expr (lhs, modifycode, rhs);
  /* APPLE LOCAL begin __block assign sequence point 6639533 */
  if (insert_sequence_point)
    lhs = build2 (COMPOUND_EXPR, TREE_TYPE (lhs), rhs, lhs);
  /* APPLE LOCAL end __block assign sequence point 6639533 */
  return lhs;
}