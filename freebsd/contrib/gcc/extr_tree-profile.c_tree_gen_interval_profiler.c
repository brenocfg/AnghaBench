#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  TYPE_4__* histogram_value ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
struct TYPE_8__ {int /*<<< orphan*/  steps; int /*<<< orphan*/  int_start; } ;
struct TYPE_9__ {TYPE_2__ intvl; } ;
struct TYPE_7__ {int /*<<< orphan*/  stmt; } ;
struct TYPE_10__ {TYPE_3__ hdata; TYPE_1__ hvalue; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSI_SAME_STMT ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  bsi_for_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_insert_before (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_function_call_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_int_cst_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  force_gimple_operand_bsi (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_type_node ; 
 int /*<<< orphan*/  prepare_instrumented_value (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  tree_cons (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_coverage_counter_ref (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  tree_interval_profiler_fn ; 
 int /*<<< orphan*/  unsigned_type_node ; 

__attribute__((used)) static void
tree_gen_interval_profiler (histogram_value value, unsigned tag, unsigned base)
{
  tree stmt = value->hvalue.stmt;
  block_stmt_iterator bsi = bsi_for_stmt (stmt);
  tree ref = tree_coverage_counter_ref (tag, base), ref_ptr;
  tree args, call, val;
  tree start = build_int_cst_type (integer_type_node, value->hdata.intvl.int_start);
  tree steps = build_int_cst_type (unsigned_type_node, value->hdata.intvl.steps);
  
  ref_ptr = force_gimple_operand_bsi (&bsi,
				      build_addr (ref, current_function_decl),
				      true, NULL_TREE);
  val = prepare_instrumented_value (&bsi, value);
  args = tree_cons (NULL_TREE, ref_ptr,
		    tree_cons (NULL_TREE, val,
			       tree_cons (NULL_TREE, start,
					  tree_cons (NULL_TREE, steps,
						     NULL_TREE))));
  call = build_function_call_expr (tree_interval_profiler_fn, args);
  bsi_insert_before (&bsi, call, BSI_SAME_STMT);
}