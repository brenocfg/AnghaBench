#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_9__ {scalar_t__ is_nested; } ;
typedef  TYPE_2__ omp_context ;
struct TYPE_8__ {scalar_t__ (* omp_clause_assign_op ) (scalar_t__,scalar_t__,scalar_t__) ;} ;
struct TYPE_10__ {TYPE_1__ decls; } ;

/* Variables and functions */
 int /*<<< orphan*/  MODIFY_EXPR ; 
 scalar_t__ OMP_CLAUSE_CHAIN (scalar_t__) ; 
 scalar_t__ OMP_CLAUSE_CODE (scalar_t__) ; 
 scalar_t__ OMP_CLAUSE_COPYPRIVATE ; 
 scalar_t__ OMP_CLAUSE_DECL (scalar_t__) ; 
 scalar_t__ build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ build_fold_addr_expr (scalar_t__) ; 
 scalar_t__ build_fold_indirect_ref (scalar_t__) ; 
 scalar_t__ build_receiver_ref (scalar_t__,int,TYPE_2__*) ; 
 scalar_t__ build_sender_ref (scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  gimplify_and_add (scalar_t__,scalar_t__*) ; 
 scalar_t__ is_reference (scalar_t__) ; 
 TYPE_5__ lang_hooks ; 
 scalar_t__ lookup_decl_in_outer_ctx (scalar_t__,TYPE_2__*) ; 
 scalar_t__ stub1 (scalar_t__,scalar_t__,scalar_t__) ; 
 int use_pointer_for_field (scalar_t__,int) ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static void
lower_copyprivate_clauses (tree clauses, tree *slist, tree *rlist,
			    omp_context *ctx)
{
  tree c;

  for (c = clauses; c ; c = OMP_CLAUSE_CHAIN (c))
    {
      tree var, ref, x;
      bool by_ref;

      if (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_COPYPRIVATE)
	continue;

      var = OMP_CLAUSE_DECL (c);
      by_ref = use_pointer_for_field (var, false);

      ref = build_sender_ref (var, ctx);
      x = (ctx->is_nested) ? lookup_decl_in_outer_ctx (var, ctx) : var;
      x = by_ref ? build_fold_addr_expr (x) : x;
      x = build2 (MODIFY_EXPR, void_type_node, ref, x);
      gimplify_and_add (x, slist);

      ref = build_receiver_ref (var, by_ref, ctx);
      if (is_reference (var))
	{
	  ref = build_fold_indirect_ref (ref);
	  var = build_fold_indirect_ref (var);
	}
      x = lang_hooks.decls.omp_clause_assign_op (c, var, ref);
      gimplify_and_add (x, rlist);
    }
}