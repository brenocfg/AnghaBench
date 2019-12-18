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

/* Variables and functions */
 int /*<<< orphan*/  END_FOLD_INIT ; 
 int /*<<< orphan*/  START_FOLD_INIT ; 
 int /*<<< orphan*/  fold_build3 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tree
fold_build3_initializer (enum tree_code code, tree type, tree op0, tree op1,
			 tree op2)
{
  tree result;
  START_FOLD_INIT;

  result = fold_build3 (code, type, op0, op1, op2);

  END_FOLD_INIT;
  return result;
}