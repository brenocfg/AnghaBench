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
typedef  scalar_t__ tree ;

/* Variables and functions */
 scalar_t__ TYPE_P (scalar_t__) ; 
 scalar_t__ fold_non_dependent_expr (scalar_t__) ; 
 scalar_t__ tsubst (scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ tsubst_expr (scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static tree
tsubst_template_arg (tree t, tree args, tsubst_flags_t complain, tree in_decl)
{
  tree r;

  if (!t)
    r = t;
  else if (TYPE_P (t))
    r = tsubst (t, args, complain, in_decl);
  else
    {
      r = tsubst_expr (t, args, complain, in_decl,
		       /*integral_constant_expression_p=*/true);
      r = fold_non_dependent_expr (r);
    }
  return r;
}