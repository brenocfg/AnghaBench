#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  enum gimplify_status { ____Placeholder_gimplify_status } gimplify_status ;
struct TYPE_3__ {int /*<<< orphan*/  (* type_for_mode ) (int /*<<< orphan*/ ,int) ;} ;
struct TYPE_4__ {TYPE_1__ types; } ;

/* Variables and functions */
 int GS_OK ; 
 int /*<<< orphan*/  TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIEW_CONVERT_EXPR ; 
 int /*<<< orphan*/  fold_build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ lang_hooks ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static enum gimplify_status
gimplify_scalar_mode_aggregate_compare (tree *expr_p)
{
  tree op0 = TREE_OPERAND (*expr_p, 0);
  tree op1 = TREE_OPERAND (*expr_p, 1);

  tree type = TREE_TYPE (op0);
  tree scalar_type = lang_hooks.types.type_for_mode (TYPE_MODE (type), 1);

  op0 = fold_build1 (VIEW_CONVERT_EXPR, scalar_type, op0);
  op1 = fold_build1 (VIEW_CONVERT_EXPR, scalar_type, op1);

  *expr_p
    = fold_build2 (TREE_CODE (*expr_p), TREE_TYPE (*expr_p), op0, op1);

  return GS_OK;
}