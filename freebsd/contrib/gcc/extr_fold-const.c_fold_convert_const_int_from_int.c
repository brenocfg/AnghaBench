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
 int /*<<< orphan*/  POINTER_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_CONSTANT_OVERFLOW (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_INT_CST_HIGH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_INT_CST_LOW (int /*<<< orphan*/ ) ; 
 int TREE_OVERFLOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_UNSIGNED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_int_cst_wide (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  force_fit_type (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
fold_convert_const_int_from_int (tree type, tree arg1)
{
  tree t;

  /* Given an integer constant, make new constant with new type,
     appropriately sign-extended or truncated.  */
  t = build_int_cst_wide (type, TREE_INT_CST_LOW (arg1),
			  TREE_INT_CST_HIGH (arg1));

  t = force_fit_type (t,
		      /* Don't set the overflow when
		      	 converting a pointer  */
		      !POINTER_TYPE_P (TREE_TYPE (arg1)),
		      (TREE_INT_CST_HIGH (arg1) < 0
		       && (TYPE_UNSIGNED (type)
			   < TYPE_UNSIGNED (TREE_TYPE (arg1))))
		      | TREE_OVERFLOW (arg1),
		      TREE_CONSTANT_OVERFLOW (arg1));

  return t;
}