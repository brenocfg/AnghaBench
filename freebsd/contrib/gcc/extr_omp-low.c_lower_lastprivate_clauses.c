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
typedef  int /*<<< orphan*/ * tree ;
struct TYPE_9__ {int /*<<< orphan*/  stmt; struct TYPE_9__* outer; } ;
typedef  TYPE_2__ omp_context ;
struct TYPE_8__ {int /*<<< orphan*/ * (* omp_clause_assign_op ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_10__ {TYPE_1__ decls; } ;

/* Variables and functions */
 int /*<<< orphan*/  COND_EXPR ; 
 int /*<<< orphan*/ * OMP_CLAUSE_CHAIN (int /*<<< orphan*/ *) ; 
 scalar_t__ OMP_CLAUSE_CODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OMP_CLAUSE_DECL (int /*<<< orphan*/ *) ; 
 scalar_t__ OMP_CLAUSE_LASTPRIVATE ; 
 int /*<<< orphan*/ * OMP_PARALLEL_CLAUSES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * alloc_stmt_list () ; 
 int /*<<< orphan*/  append_to_statement_list (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * build3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build_fold_indirect_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build_outer_var_ref (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * find_omp_clause (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  gimplify_and_add (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ is_parallel_ctx (TYPE_2__*) ; 
 scalar_t__ is_reference (int /*<<< orphan*/ *) ; 
 TYPE_5__ lang_hooks ; 
 int /*<<< orphan*/ * lookup_decl (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static void
lower_lastprivate_clauses (tree clauses, tree predicate, tree *stmt_list,
			    omp_context *ctx)
{
  tree sub_list, x, c;

  /* Early exit if there are no lastprivate clauses.  */
  clauses = find_omp_clause (clauses, OMP_CLAUSE_LASTPRIVATE);
  if (clauses == NULL)
    {
      /* If this was a workshare clause, see if it had been combined
	 with its parallel.  In that case, look for the clauses on the
	 parallel statement itself.  */
      if (is_parallel_ctx (ctx))
	return;

      ctx = ctx->outer;
      if (ctx == NULL || !is_parallel_ctx (ctx))
	return;

      clauses = find_omp_clause (OMP_PARALLEL_CLAUSES (ctx->stmt),
				 OMP_CLAUSE_LASTPRIVATE);
      if (clauses == NULL)
	return;
    }

  sub_list = alloc_stmt_list ();

  for (c = clauses; c ; c = OMP_CLAUSE_CHAIN (c))
    {
      tree var, new_var;

      if (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_LASTPRIVATE)
	continue;

      var = OMP_CLAUSE_DECL (c);
      new_var = lookup_decl (var, ctx);

      x = build_outer_var_ref (var, ctx);
      if (is_reference (var))
	new_var = build_fold_indirect_ref (new_var);
      x = lang_hooks.decls.omp_clause_assign_op (c, x, new_var);
      append_to_statement_list (x, &sub_list);
    }

  if (predicate)
    x = build3 (COND_EXPR, void_type_node, predicate, sub_list, NULL);
  else
    x = sub_list;

  gimplify_and_add (x, stmt_list);
}