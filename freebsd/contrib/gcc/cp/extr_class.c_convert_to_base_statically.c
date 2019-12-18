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
 int /*<<< orphan*/  ADDR_EXPR ; 
 int /*<<< orphan*/  BINFO_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BINFO_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INDIRECT_REF ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 int /*<<< orphan*/  SAME_BINFO_TYPE_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_nop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_pointer_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_unary_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  integer_zerop (int /*<<< orphan*/ ) ; 

tree
convert_to_base_statically (tree expr, tree base)
{
  tree expr_type;

  expr_type = TREE_TYPE (expr);
  if (!SAME_BINFO_TYPE_P (BINFO_TYPE (base), expr_type))
    {
      tree pointer_type;

      pointer_type = build_pointer_type (expr_type);
      expr = build_unary_op (ADDR_EXPR, expr, /*noconvert=*/1);
      if (!integer_zerop (BINFO_OFFSET (base)))
	  expr = build2 (PLUS_EXPR, pointer_type, expr,
			 build_nop (pointer_type, BINFO_OFFSET (base)));
      expr = build_nop (build_pointer_type (BINFO_TYPE (base)), expr);
      expr = build1 (INDIRECT_REF, BINFO_TYPE (base), expr);
    }

  return expr;
}