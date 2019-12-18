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
 int /*<<< orphan*/  PLUS_EXPR ; 
 scalar_t__ PTRMEM_CST ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PTRMEMFUNC_FN_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PTRMEM_CLASS_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_PTRMEM_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_nop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_ptrmemfunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cp_build_binary_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cplus_expand_constant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_delta_difference (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  integer_zerop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptrdiff_type_node ; 

tree
convert_ptrmem (tree type, tree expr, bool allow_inverse_p,
		bool c_cast_p)
{
  if (TYPE_PTRMEM_P (type))
    {
      tree delta;

      if (TREE_CODE (expr) == PTRMEM_CST)
	expr = cplus_expand_constant (expr);
      delta = get_delta_difference (TYPE_PTRMEM_CLASS_TYPE (TREE_TYPE (expr)),
				    TYPE_PTRMEM_CLASS_TYPE (type),
				    allow_inverse_p,
				    c_cast_p);
      if (!integer_zerop (delta))
	expr = cp_build_binary_op (PLUS_EXPR,
				   build_nop (ptrdiff_type_node, expr),
				   delta);
      return build_nop (type, expr);
    }
  else
    return build_ptrmemfunc (TYPE_PTRMEMFUNC_FN_TYPE (type), expr,
			     allow_inverse_p, c_cast_p);
}