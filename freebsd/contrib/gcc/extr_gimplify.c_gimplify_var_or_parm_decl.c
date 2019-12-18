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
 int /*<<< orphan*/  DECL_EXTERNAL (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_HAS_VALUE_EXPR_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_SEEN_IN_BIND_EXPR_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_VALUE_EXPR (int /*<<< orphan*/ ) ; 
 int GS_ALL_DONE ; 
 int GS_ERROR ; 
 int GS_OK ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_STATIC (int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_DECL ; 
 scalar_t__ current_function_decl ; 
 scalar_t__ decl_function_context (int /*<<< orphan*/ ) ; 
 scalar_t__ errorcount ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ gimplify_omp_ctxp ; 
 scalar_t__ omp_notice_variable (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sorrycount ; 
 int /*<<< orphan*/  unshare_expr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum gimplify_status
gimplify_var_or_parm_decl (tree *expr_p)
{
  tree decl = *expr_p;

  /* ??? If this is a local variable, and it has not been seen in any
     outer BIND_EXPR, then it's probably the result of a duplicate
     declaration, for which we've already issued an error.  It would
     be really nice if the front end wouldn't leak these at all.
     Currently the only known culprit is C++ destructors, as seen
     in g++.old-deja/g++.jason/binding.C.  */
  if (TREE_CODE (decl) == VAR_DECL
      && !DECL_SEEN_IN_BIND_EXPR_P (decl)
      && !TREE_STATIC (decl) && !DECL_EXTERNAL (decl)
      && decl_function_context (decl) == current_function_decl)
    {
      gcc_assert (errorcount || sorrycount);
      return GS_ERROR;
    }

  /* When within an OpenMP context, notice uses of variables.  */
  if (gimplify_omp_ctxp && omp_notice_variable (gimplify_omp_ctxp, decl, true))
    return GS_ALL_DONE;

  /* If the decl is an alias for another expression, substitute it now.  */
  if (DECL_HAS_VALUE_EXPR_P (decl))
    {
      *expr_p = unshare_expr (DECL_VALUE_EXPR (decl));
      return GS_OK;
    }

  return GS_ALL_DONE;
}