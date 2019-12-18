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
 int /*<<< orphan*/  STRIP_NOPS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_build1 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gimplify_val (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tree
gimplify_build1 (block_stmt_iterator *bsi, enum tree_code code, tree type,
		 tree a)
{
  tree ret;

  ret = fold_build1 (code, type, a);
  STRIP_NOPS (ret);

  return gimplify_val (bsi, type, ret);
}