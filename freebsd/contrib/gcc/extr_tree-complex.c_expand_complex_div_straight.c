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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;

/* Variables and functions */
 int MINUS_EXPR ; 
 int MULT_EXPR ; 
 int PLUS_EXPR ; 
 int /*<<< orphan*/  gimplify_build2 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_complex_assignment (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
expand_complex_div_straight (block_stmt_iterator *bsi, tree inner_type,
			     tree ar, tree ai, tree br, tree bi,
			     enum tree_code code)
{
  tree rr, ri, div, t1, t2, t3;

  t1 = gimplify_build2 (bsi, MULT_EXPR, inner_type, br, br);
  t2 = gimplify_build2 (bsi, MULT_EXPR, inner_type, bi, bi);
  div = gimplify_build2 (bsi, PLUS_EXPR, inner_type, t1, t2);

  t1 = gimplify_build2 (bsi, MULT_EXPR, inner_type, ar, br);
  t2 = gimplify_build2 (bsi, MULT_EXPR, inner_type, ai, bi);
  t3 = gimplify_build2 (bsi, PLUS_EXPR, inner_type, t1, t2);
  rr = gimplify_build2 (bsi, code, inner_type, t3, div);

  t1 = gimplify_build2 (bsi, MULT_EXPR, inner_type, ai, br);
  t2 = gimplify_build2 (bsi, MULT_EXPR, inner_type, ar, bi);
  t3 = gimplify_build2 (bsi, MINUS_EXPR, inner_type, t1, t2);
  ri = gimplify_build2 (bsi, code, inner_type, t3, div);

  update_complex_assignment (bsi, rr, ri);
}