#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct gimplify_omp_ctx {struct gimplify_omp_ctx* outer_context; scalar_t__ is_parallel; scalar_t__ is_combined_parallel; int /*<<< orphan*/  variables; } ;
typedef  TYPE_1__* splay_tree_node ;
typedef  int /*<<< orphan*/  splay_tree_key ;
struct TYPE_3__ {int value; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_NAME (scalar_t__) ; 
 int GOVD_EXPLICIT ; 
 int GOVD_FIRSTPRIVATE ; 
 int GOVD_PRIVATE ; 
 int GOVD_REDUCTION ; 
 int GOVD_SHARED ; 
 int /*<<< orphan*/  IDENTIFIER_POINTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 struct gimplify_omp_ctx* gimplify_omp_ctxp ; 
 int /*<<< orphan*/  is_global_var (scalar_t__) ; 
 TYPE_1__* splay_tree_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
omp_is_private (struct gimplify_omp_ctx *ctx, tree decl)
{
  splay_tree_node n;

  n = splay_tree_lookup (ctx->variables, (splay_tree_key)decl);
  if (n != NULL)
    {
      if (n->value & GOVD_SHARED)
	{
	  if (ctx == gimplify_omp_ctxp)
	    {
	      error ("iteration variable %qs should be private",
		     IDENTIFIER_POINTER (DECL_NAME (decl)));
	      n->value = GOVD_PRIVATE;
	      return true;
	    }
	  else
	    return false;
	}
      else if ((n->value & GOVD_EXPLICIT) != 0
	       && (ctx == gimplify_omp_ctxp
		   || (ctx->is_combined_parallel
		       && gimplify_omp_ctxp->outer_context == ctx)))
	{
	  if ((n->value & GOVD_FIRSTPRIVATE) != 0)
	    error ("iteration variable %qs should not be firstprivate",
		   IDENTIFIER_POINTER (DECL_NAME (decl)));
	  else if ((n->value & GOVD_REDUCTION) != 0)
	    error ("iteration variable %qs should not be reduction",
		   IDENTIFIER_POINTER (DECL_NAME (decl)));
	}
      return true;
    }

  if (ctx->is_parallel)
    return false;
  else if (ctx->outer_context)
    return omp_is_private (ctx->outer_context, decl);
  else
    return !is_global_var (decl);
}