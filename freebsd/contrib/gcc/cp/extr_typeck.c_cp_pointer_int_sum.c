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
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_if_not_in_template (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pointer_int_sum (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
cp_pointer_int_sum (enum tree_code resultcode, tree ptrop, tree intop)
{
  tree res_type = TREE_TYPE (ptrop);

  /* pointer_int_sum() uses size_in_bytes() on the TREE_TYPE(res_type)
     in certain circumstance (when it's valid to do so).  So we need
     to make sure it's complete.  We don't need to check here, if we
     can actually complete it at all, as those checks will be done in
     pointer_int_sum() anyway.  */
  complete_type (TREE_TYPE (res_type));

  return pointer_int_sum (resultcode, ptrop,
			  fold_if_not_in_template (intop));
}