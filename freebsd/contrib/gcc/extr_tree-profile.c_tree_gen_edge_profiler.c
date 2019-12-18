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
typedef  int /*<<< orphan*/  edge ;

/* Variables and functions */
 int /*<<< orphan*/  GCOV_COUNTER_ARCS ; 
 int /*<<< orphan*/  MODIFY_EXPR ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 int /*<<< orphan*/  bsi_insert_on_edge (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_tmp_var (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gcov_type_node ; 
 int /*<<< orphan*/  integer_one_node ; 
 int /*<<< orphan*/  tree_coverage_counter_ref (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
tree_gen_edge_profiler (int edgeno, edge e)
{
  tree tmp1 = create_tmp_var (gcov_type_node, "PROF");
  tree tmp2 = create_tmp_var (gcov_type_node, "PROF");
  tree ref = tree_coverage_counter_ref (GCOV_COUNTER_ARCS, edgeno);
  tree stmt1 = build2 (MODIFY_EXPR, gcov_type_node, tmp1, ref);
  tree stmt2 = build2 (MODIFY_EXPR, gcov_type_node, tmp2,
		       build2 (PLUS_EXPR, gcov_type_node, 
			      tmp1, integer_one_node));
  tree stmt3 = build2 (MODIFY_EXPR, gcov_type_node, ref, tmp2);
  bsi_insert_on_edge (e, stmt1);
  bsi_insert_on_edge (e, stmt2);
  bsi_insert_on_edge (e, stmt3);
}