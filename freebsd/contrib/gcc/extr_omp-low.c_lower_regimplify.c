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
typedef  int /*<<< orphan*/ * tree ;
struct walk_stmt_info {int /*<<< orphan*/  tsi; scalar_t__ val_only; scalar_t__ is_lhs; } ;
typedef  enum gimplify_status { ____Placeholder_gimplify_status } gimplify_status ;

/* Variables and functions */
 int GS_ALL_DONE ; 
 int /*<<< orphan*/  TSI_SAME_STMT ; 
 int /*<<< orphan*/  fb_lvalue ; 
 int /*<<< orphan*/  fb_rvalue ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int gimplify_expr (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_gimple_formal_tmp_var ; 
 int /*<<< orphan*/  is_gimple_lvalue ; 
 int /*<<< orphan*/  is_gimple_val ; 
 int /*<<< orphan*/  tsi_link_before (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lower_regimplify (tree *tp, struct walk_stmt_info *wi)
{
  enum gimplify_status gs;
  tree pre = NULL;

  if (wi->is_lhs)
    gs = gimplify_expr (tp, &pre, NULL, is_gimple_lvalue, fb_lvalue);
  else if (wi->val_only)
    gs = gimplify_expr (tp, &pre, NULL, is_gimple_val, fb_rvalue);
  else
    gs = gimplify_expr (tp, &pre, NULL, is_gimple_formal_tmp_var, fb_rvalue);
  gcc_assert (gs == GS_ALL_DONE);

  if (pre)
    tsi_link_before (&wi->tsi, pre, TSI_SAME_STMT);
}