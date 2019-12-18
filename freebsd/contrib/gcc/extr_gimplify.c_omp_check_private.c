#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct gimplify_omp_ctx {int /*<<< orphan*/  variables; struct gimplify_omp_ctx* outer_context; int /*<<< orphan*/  is_parallel; } ;
typedef  TYPE_2__* splay_tree_node ;
typedef  int /*<<< orphan*/  splay_tree_key ;
struct TYPE_5__ {scalar_t__ (* omp_privatize_by_reference ) (scalar_t__) ;} ;
struct TYPE_7__ {TYPE_1__ decls; } ;
struct TYPE_6__ {int value; } ;

/* Variables and functions */
 int GOVD_SHARED ; 
 scalar_t__ is_global_var (scalar_t__) ; 
 TYPE_4__ lang_hooks ; 
 TYPE_2__* splay_tree_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (scalar_t__) ; 

__attribute__((used)) static bool
omp_check_private (struct gimplify_omp_ctx *ctx, tree decl)
{
  splay_tree_node n;

  do
    {
      ctx = ctx->outer_context;
      if (ctx == NULL)
	return !(is_global_var (decl)
		 /* References might be private, but might be shared too.  */
		 || lang_hooks.decls.omp_privatize_by_reference (decl));

      n = splay_tree_lookup (ctx->variables, (splay_tree_key) decl);
      if (n != NULL)
	return (n->value & GOVD_SHARED) == 0;
    }
  while (!ctx->is_parallel);
  return false;
}