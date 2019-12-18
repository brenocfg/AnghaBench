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

/* Variables and functions */
 scalar_t__ COMPONENT_REF ; 
 scalar_t__ CONVERT_EXPR ; 
 int /*<<< orphan*/  DECL_ALIGN_UNIT (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_C_BIT_FIELD (int /*<<< orphan*/ ) ; 
 scalar_t__ FIELD_DECL ; 
 scalar_t__ INDIRECT_REF ; 
 scalar_t__ NOP_EXPR ; 
 scalar_t__ POINTER_TYPE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int TYPE_ALIGN (int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_OR_FUNCTION_DECL_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_alignof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size_one_node ; 
 int /*<<< orphan*/  size_type_node ; 

tree
c_alignof_expr (tree expr)
{
  tree t;

  if (VAR_OR_FUNCTION_DECL_P (expr))
    t = size_int (DECL_ALIGN_UNIT (expr));

  else if (TREE_CODE (expr) == COMPONENT_REF
	   && DECL_C_BIT_FIELD (TREE_OPERAND (expr, 1)))
    {
      error ("%<__alignof%> applied to a bit-field");
      t = size_one_node;
    }
  else if (TREE_CODE (expr) == COMPONENT_REF
	   && TREE_CODE (TREE_OPERAND (expr, 1)) == FIELD_DECL)
    t = size_int (DECL_ALIGN_UNIT (TREE_OPERAND (expr, 1)));

  else if (TREE_CODE (expr) == INDIRECT_REF)
    {
      tree t = TREE_OPERAND (expr, 0);
      tree best = t;
      int bestalign = TYPE_ALIGN (TREE_TYPE (TREE_TYPE (t)));

      while ((TREE_CODE (t) == NOP_EXPR || TREE_CODE (t) == CONVERT_EXPR)
	     && TREE_CODE (TREE_TYPE (TREE_OPERAND (t, 0))) == POINTER_TYPE)
	{
	  int thisalign;

	  t = TREE_OPERAND (t, 0);
	  thisalign = TYPE_ALIGN (TREE_TYPE (TREE_TYPE (t)));
	  if (thisalign > bestalign)
	    best = t, bestalign = thisalign;
	}
      return c_alignof (TREE_TYPE (TREE_TYPE (best)));
    }
  else
    return c_alignof (TREE_TYPE (expr));

  return fold_convert (size_type_node, t);
}