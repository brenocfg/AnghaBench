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
 int /*<<< orphan*/  CASE_LABEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_case_label_for_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_edge (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  label_to_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  last_stmt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static edge
find_taken_edge_switch_expr (basic_block bb, tree val)
{
  tree switch_expr, taken_case;
  basic_block dest_bb;
  edge e;

  switch_expr = last_stmt (bb);
  taken_case = find_case_label_for_value (switch_expr, val);
  dest_bb = label_to_block (CASE_LABEL (taken_case));

  e = find_edge (bb, dest_bb);
  gcc_assert (e);
  return e;
}