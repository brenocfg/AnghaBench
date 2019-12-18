#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_5__ {scalar_t__ is_nested; } ;
typedef  TYPE_1__ omp_context ;

/* Variables and functions */
 int /*<<< orphan*/  MODIFY_EXPR ; 
 scalar_t__ OMP_CLAUSE_CHAIN (scalar_t__) ; 
 int OMP_CLAUSE_CODE (scalar_t__) ; 
#define  OMP_CLAUSE_COPYIN 131 
 scalar_t__ OMP_CLAUSE_DECL (scalar_t__) ; 
#define  OMP_CLAUSE_FIRSTPRIVATE 130 
#define  OMP_CLAUSE_LASTPRIVATE 129 
 int /*<<< orphan*/  OMP_CLAUSE_LASTPRIVATE_FIRSTPRIVATE (scalar_t__) ; 
#define  OMP_CLAUSE_REDUCTION 128 
 scalar_t__ build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ build_fold_addr_expr (scalar_t__) ; 
 scalar_t__ build_sender_ref (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  gimplify_and_add (scalar_t__,scalar_t__*) ; 
 scalar_t__ is_global_var (scalar_t__) ; 
 int /*<<< orphan*/  is_reference (scalar_t__) ; 
 scalar_t__ is_variable_sized (scalar_t__) ; 
 scalar_t__ lookup_decl_in_outer_ctx (scalar_t__,TYPE_1__*) ; 
 int use_pointer_for_field (scalar_t__,int) ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static void
lower_send_clauses (tree clauses, tree *ilist, tree *olist, omp_context *ctx)
{
  tree c;

  for (c = clauses; c ; c = OMP_CLAUSE_CHAIN (c))
    {
      tree val, ref, x, var;
      bool by_ref, do_in = false, do_out = false;

      switch (OMP_CLAUSE_CODE (c))
	{
	case OMP_CLAUSE_FIRSTPRIVATE:
	case OMP_CLAUSE_COPYIN:
	case OMP_CLAUSE_LASTPRIVATE:
	case OMP_CLAUSE_REDUCTION:
	  break;
	default:
	  continue;
	}

      var = val = OMP_CLAUSE_DECL (c);
      if (ctx->is_nested)
	var = lookup_decl_in_outer_ctx (val, ctx);

      if (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_COPYIN
	  && is_global_var (var))
	continue;
      if (is_variable_sized (val))
	continue;
      by_ref = use_pointer_for_field (val, false);

      switch (OMP_CLAUSE_CODE (c))
	{
	case OMP_CLAUSE_FIRSTPRIVATE:
	case OMP_CLAUSE_COPYIN:
	  do_in = true;
	  break;

	case OMP_CLAUSE_LASTPRIVATE:
	  if (by_ref || is_reference (val))
	    {
	      if (OMP_CLAUSE_LASTPRIVATE_FIRSTPRIVATE (c))
		continue;
	      do_in = true;
	    }
	  else
	    do_out = true;
	  break;

	case OMP_CLAUSE_REDUCTION:
	  do_in = true;
	  do_out = !(by_ref || is_reference (val));
	  break;

	default:
	  gcc_unreachable ();
	}

      if (do_in)
	{
	  ref = build_sender_ref (val, ctx);
	  x = by_ref ? build_fold_addr_expr (var) : var;
	  x = build2 (MODIFY_EXPR, void_type_node, ref, x);
	  gimplify_and_add (x, ilist);
	}

      if (do_out)
	{
	  ref = build_sender_ref (val, ctx);
	  x = build2 (MODIFY_EXPR, void_type_node, var, ref);
	  gimplify_and_add (x, olist);
	}
    }
}