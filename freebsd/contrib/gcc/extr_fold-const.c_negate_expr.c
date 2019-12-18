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

/* Variables and functions */
 int /*<<< orphan*/  NEGATE_EXPR ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  STRIP_SIGN_NOPS (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ build1 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_convert (scalar_t__,scalar_t__) ; 
 scalar_t__ fold_negate_expr (scalar_t__) ; 

__attribute__((used)) static tree
negate_expr (tree t)
{
  tree type, tem;

  if (t == NULL_TREE)
    return NULL_TREE;

  type = TREE_TYPE (t);
  STRIP_SIGN_NOPS (t);

  tem = fold_negate_expr (t);
  if (!tem)
    tem = build1 (NEGATE_EXPR, TREE_TYPE (t), t);
  return fold_convert (type, tem);
}