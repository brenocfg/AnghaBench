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
typedef  int /*<<< orphan*/  tsubst_flags_t ;
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 scalar_t__ SCOPE_REF ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsubst_copy_and_build (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  tsubst_qualified_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static tree
tsubst_non_call_postfix_expression (tree t, tree args,
				    tsubst_flags_t complain,
				    tree in_decl)
{
  if (TREE_CODE (t) == SCOPE_REF)
    t = tsubst_qualified_id (t, args, complain, in_decl,
			     /*done=*/false, /*address_p=*/false);
  else
    t = tsubst_copy_and_build (t, args, complain, in_decl,
			       /*function_p=*/false,
			       /*integral_constant_expression_p=*/false);

  return t;
}