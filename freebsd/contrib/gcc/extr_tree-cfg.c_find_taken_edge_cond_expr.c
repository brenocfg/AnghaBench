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
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 scalar_t__ INTEGER_CST ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extract_true_false_edges_from_block (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ zero_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static edge
find_taken_edge_cond_expr (basic_block bb, tree val)
{
  edge true_edge, false_edge;

  extract_true_false_edges_from_block (bb, &true_edge, &false_edge);

  gcc_assert (TREE_CODE (val) == INTEGER_CST);
  return (zero_p (val) ? false_edge : true_edge);
}