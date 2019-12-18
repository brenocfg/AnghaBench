#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct loop {TYPE_1__* header; } ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  TYPE_1__* basic_block ;
struct TYPE_10__ {int /*<<< orphan*/  dest; } ;
struct TYPE_9__ {int /*<<< orphan*/  succs; scalar_t__ aux; } ;

/* Variables and functions */
 scalar_t__ COND_EXPR ; 
 scalar_t__ EDGE_COUNT (int /*<<< orphan*/ ) ; 
 TYPE_7__* EDGE_SUCC (TYPE_1__*,int) ; 
 scalar_t__ LABEL_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bsi_start (TYPE_1__*) ; 
 int /*<<< orphan*/  bsi_stmt (int /*<<< orphan*/ ) ; 
 scalar_t__ estimate_num_insns (int /*<<< orphan*/ ) ; 
 scalar_t__ flow_bb_inside_loop_p (struct loop*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ get_call_expr_in (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  last_stmt (TYPE_1__*) ; 
 int /*<<< orphan*/  single_pred_p (TYPE_1__*) ; 
 scalar_t__ single_succ_p (TYPE_1__*) ; 

__attribute__((used)) static bool
should_duplicate_loop_header_p (basic_block header, struct loop *loop,
				int *limit)
{
  block_stmt_iterator bsi;
  tree last;

  /* Do not copy one block more than once (we do not really want to do
     loop peeling here).  */
  if (header->aux)
    return false;

  gcc_assert (EDGE_COUNT (header->succs) > 0);
  if (single_succ_p (header))
    return false;
  if (flow_bb_inside_loop_p (loop, EDGE_SUCC (header, 0)->dest)
      && flow_bb_inside_loop_p (loop, EDGE_SUCC (header, 1)->dest))
    return false;

  /* If this is not the original loop header, we want it to have just
     one predecessor in order to match the && pattern.  */
  if (header != loop->header && !single_pred_p (header))
    return false;

  last = last_stmt (header);
  if (TREE_CODE (last) != COND_EXPR)
    return false;

  /* Approximately copy the conditions that used to be used in jump.c --
     at most 20 insns and no calls.  */
  for (bsi = bsi_start (header); !bsi_end_p (bsi); bsi_next (&bsi))
    {
      last = bsi_stmt (bsi);

      if (TREE_CODE (last) == LABEL_EXPR)
	continue;

      if (get_call_expr_in (last))
	return false;

      *limit -= estimate_num_insns (last);
      if (*limit < 0)
	return false;
    }

  return true;
}