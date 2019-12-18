#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct mem_ref {unsigned int prefetch_mod; scalar_t__ write_p; TYPE_1__* group; int /*<<< orphan*/  mem; int /*<<< orphan*/  stmt; } ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
struct TYPE_2__ {unsigned int step; } ;
typedef  unsigned int HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  BSI_SAME_STMT ; 
 size_t BUILT_IN_PREFETCH ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 int TDF_DETAILS ; 
 int /*<<< orphan*/  bsi_for_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_insert_before (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_fold_addr_expr_with_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_function_call_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/ * built_in_decls ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/  fold_build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_gimple_operand_bsi (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,void*) ; 
 int /*<<< orphan*/  integer_one_node ; 
 int /*<<< orphan*/  integer_zero_node ; 
 int /*<<< orphan*/  ptr_type_node ; 
 int /*<<< orphan*/  tree_cons (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unshare_expr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
issue_prefetch_ref (struct mem_ref *ref, unsigned unroll_factor, unsigned ahead)
{
  HOST_WIDE_INT delta;
  tree addr, addr_base, prefetch, params, write_p;
  block_stmt_iterator bsi;
  unsigned n_prefetches, ap;

  if (dump_file && (dump_flags & TDF_DETAILS))
    fprintf (dump_file, "Issued prefetch for %p.\n", (void *) ref);

  bsi = bsi_for_stmt (ref->stmt);

  n_prefetches = ((unroll_factor + ref->prefetch_mod - 1)
		  / ref->prefetch_mod);
  addr_base = build_fold_addr_expr_with_type (ref->mem, ptr_type_node);
  addr_base = force_gimple_operand_bsi (&bsi, unshare_expr (addr_base), true, NULL);

  for (ap = 0; ap < n_prefetches; ap++)
    {
      /* Determine the address to prefetch.  */
      delta = (ahead + ap * ref->prefetch_mod) * ref->group->step;
      addr = fold_build2 (PLUS_EXPR, ptr_type_node,
			  addr_base, build_int_cst (ptr_type_node, delta));
      addr = force_gimple_operand_bsi (&bsi, unshare_expr (addr), true, NULL);

      /* Create the prefetch instruction.  */
      write_p = ref->write_p ? integer_one_node : integer_zero_node;
      params = tree_cons (NULL_TREE, addr,
			  tree_cons (NULL_TREE, write_p, NULL_TREE));
				 
      prefetch = build_function_call_expr (built_in_decls[BUILT_IN_PREFETCH],
					   params);
      bsi_insert_before (&bsi, prefetch, BSI_SAME_STMT);
    }
}