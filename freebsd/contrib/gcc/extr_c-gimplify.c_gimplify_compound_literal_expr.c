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
typedef  enum gimplify_status { ____Placeholder_gimplify_status } gimplify_status ;

/* Variables and functions */
 int /*<<< orphan*/  COMPOUND_LITERAL_EXPR_DECL_STMT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_EXPR_DECL (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_SEEN_IN_BIND_EXPR_P (int /*<<< orphan*/ ) ; 
 int GS_OK ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  gimple_add_tmp_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gimplify_and_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum gimplify_status
gimplify_compound_literal_expr (tree *expr_p, tree *pre_p)
{
  tree decl_s = COMPOUND_LITERAL_EXPR_DECL_STMT (*expr_p);
  tree decl = DECL_EXPR_DECL (decl_s);

  /* This decl isn't mentioned in the enclosing block, so add it to the
     list of temps.  FIXME it seems a bit of a kludge to say that
     anonymous artificial vars aren't pushed, but everything else is.  */
  if (DECL_NAME (decl) == NULL_TREE && !DECL_SEEN_IN_BIND_EXPR_P (decl))
    gimple_add_tmp_var (decl);

  gimplify_and_add (decl_s, pre_p);
  *expr_p = decl;
  return GS_OK;
}