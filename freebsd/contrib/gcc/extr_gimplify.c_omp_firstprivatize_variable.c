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
typedef  int /*<<< orphan*/ * tree ;
struct gimplify_omp_ctx {struct gimplify_omp_ctx* outer_context; scalar_t__ is_parallel; int /*<<< orphan*/  variables; } ;
typedef  TYPE_1__* splay_tree_node ;
typedef  int /*<<< orphan*/  splay_tree_key ;
struct TYPE_3__ {int value; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_P (int /*<<< orphan*/ *) ; 
 int GOVD_FIRSTPRIVATE ; 
 int GOVD_SEEN ; 
 int GOVD_SHARED ; 
 int /*<<< orphan*/  omp_add_variable (struct gimplify_omp_ctx*,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* splay_tree_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
omp_firstprivatize_variable (struct gimplify_omp_ctx *ctx, tree decl)
{
  splay_tree_node n;

  if (decl == NULL || !DECL_P (decl))
    return;

  do
    {
      n = splay_tree_lookup (ctx->variables, (splay_tree_key)decl);
      if (n != NULL)
	{
	  if (n->value & GOVD_SHARED)
	    n->value = GOVD_FIRSTPRIVATE | (n->value & GOVD_SEEN);
	  else
	    return;
	}
      else if (ctx->is_parallel)
	omp_add_variable (ctx, decl, GOVD_FIRSTPRIVATE);

      ctx = ctx->outer_context;
    }
  while (ctx);
}