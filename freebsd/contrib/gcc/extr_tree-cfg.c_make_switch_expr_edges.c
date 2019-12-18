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
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  CASE_LABEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWITCH_LABELS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VEC_ELT (int /*<<< orphan*/ ,size_t) ; 
 size_t TREE_VEC_LENGTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  label_to_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  last_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_edge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
make_switch_expr_edges (basic_block bb)
{
  tree entry = last_stmt (bb);
  size_t i, n;
  tree vec;

  vec = SWITCH_LABELS (entry);
  n = TREE_VEC_LENGTH (vec);

  for (i = 0; i < n; ++i)
    {
      tree lab = CASE_LABEL (TREE_VEC_ELT (vec, i));
      basic_block label_bb = label_to_block (lab);
      make_edge (bb, label_bb, 0);
    }
}