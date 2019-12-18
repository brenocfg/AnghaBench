#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_6__ {scalar_t__ outer; } ;
typedef  TYPE_1__ omp_context ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_VALUE_EXPR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_fold_indirect_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_receiver_ref (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ is_global_var (int /*<<< orphan*/ ) ; 
 scalar_t__ is_parallel_ctx (TYPE_1__*) ; 
 scalar_t__ is_reference (int /*<<< orphan*/ ) ; 
 scalar_t__ is_variable_sized (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lookup_decl (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  maybe_lookup_decl_in_outer_ctx (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int use_pointer_for_field (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static tree
build_outer_var_ref (tree var, omp_context *ctx)
{
  tree x;

  if (is_global_var (maybe_lookup_decl_in_outer_ctx (var, ctx)))
    x = var;
  else if (is_variable_sized (var))
    {
      x = TREE_OPERAND (DECL_VALUE_EXPR (var), 0);
      x = build_outer_var_ref (x, ctx);
      x = build_fold_indirect_ref (x);
    }
  else if (is_parallel_ctx (ctx))
    {
      bool by_ref = use_pointer_for_field (var, false);
      x = build_receiver_ref (var, by_ref, ctx);
    }
  else if (ctx->outer)
    x = lookup_decl (var, ctx->outer);
  else if (is_reference (var))
    /* This can happen with orphaned constructs.  If var is reference, it is
       possible it is shared and as such valid.  */
    x = var;
  else
    gcc_unreachable ();

  if (is_reference (var))
    x = build_fold_indirect_ref (x);

  return x;
}