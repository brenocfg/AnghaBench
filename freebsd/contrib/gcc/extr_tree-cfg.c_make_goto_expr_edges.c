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
typedef  int /*<<< orphan*/  tree ;
typedef  TYPE_1__* edge ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_3__ {int /*<<< orphan*/  goto_locus; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDGE_FALLTHRU ; 
 int /*<<< orphan*/  EXPR_LOCATION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXPR_LOCUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GOTO_DESTINATION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_last (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bsi_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  label_to_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_abnormal_goto_edges (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* make_edge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ simple_goto_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
make_goto_expr_edges (basic_block bb)
{
  block_stmt_iterator last = bsi_last (bb);
  tree goto_t = bsi_stmt (last);

  /* A simple GOTO creates normal edges.  */
  if (simple_goto_p (goto_t))
    {
      tree dest = GOTO_DESTINATION (goto_t);
      edge e = make_edge (bb, label_to_block (dest), EDGE_FALLTHRU);
#ifdef USE_MAPPED_LOCATION
      e->goto_locus = EXPR_LOCATION (goto_t);
#else
      e->goto_locus = EXPR_LOCUS (goto_t);
#endif
      bsi_remove (&last, true);
      return;
    }

  /* A computed GOTO creates abnormal edges.  */
  make_abnormal_goto_edges (bb, false);
}