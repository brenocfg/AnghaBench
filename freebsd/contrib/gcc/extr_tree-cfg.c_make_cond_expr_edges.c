#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int tree ;
typedef  TYPE_1__* edge ;
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_3__ {void* goto_locus; } ;

/* Variables and functions */
 scalar_t__ COND_EXPR ; 
 int /*<<< orphan*/  COND_EXPR_ELSE (int) ; 
 int /*<<< orphan*/  COND_EXPR_THEN (int) ; 
 int /*<<< orphan*/  EDGE_FALSE_VALUE ; 
 int /*<<< orphan*/  EDGE_TRUE_VALUE ; 
 void* EXPR_LOCATION (int /*<<< orphan*/ ) ; 
 void* EXPR_LOCUS (int /*<<< orphan*/ ) ; 
 int GOTO_DESTINATION (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  label_to_block (int) ; 
 int last_stmt (int /*<<< orphan*/ ) ; 
 TYPE_1__* make_edge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
make_cond_expr_edges (basic_block bb)
{
  tree entry = last_stmt (bb);
  basic_block then_bb, else_bb;
  tree then_label, else_label;
  edge e;

  gcc_assert (entry);
  gcc_assert (TREE_CODE (entry) == COND_EXPR);

  /* Entry basic blocks for each component.  */
  then_label = GOTO_DESTINATION (COND_EXPR_THEN (entry));
  else_label = GOTO_DESTINATION (COND_EXPR_ELSE (entry));
  then_bb = label_to_block (then_label);
  else_bb = label_to_block (else_label);

  e = make_edge (bb, then_bb, EDGE_TRUE_VALUE);
#ifdef USE_MAPPED_LOCATION
  e->goto_locus = EXPR_LOCATION (COND_EXPR_THEN (entry));
#else
  e->goto_locus = EXPR_LOCUS (COND_EXPR_THEN (entry));
#endif
  e = make_edge (bb, else_bb, EDGE_FALSE_VALUE);
  if (e)
    {
#ifdef USE_MAPPED_LOCATION
      e->goto_locus = EXPR_LOCATION (COND_EXPR_ELSE (entry));
#else
      e->goto_locus = EXPR_LOCUS (COND_EXPR_ELSE (entry));
#endif
    }
}