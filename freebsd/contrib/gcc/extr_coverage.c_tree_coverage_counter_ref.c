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

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_REF ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  build4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int* fn_b_ctrs ; 
 unsigned int* fn_n_ctrs ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  get_gcov_type () ; 
 unsigned int* prg_n_ctrs ; 
 int /*<<< orphan*/ * tree_ctr_tables ; 

tree
tree_coverage_counter_ref (unsigned counter, unsigned no)
{
  tree gcov_type_node = get_gcov_type ();

  gcc_assert (no < fn_n_ctrs[counter] - fn_b_ctrs[counter]);
  no += prg_n_ctrs[counter] + fn_b_ctrs[counter];

  /* "no" here is an array index, scaled to bytes later.  */
  return build4 (ARRAY_REF, gcov_type_node, tree_ctr_tables[counter],
		 build_int_cst (NULL_TREE, no), NULL, NULL);
}