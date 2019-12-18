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
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  bsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_last (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_move_after (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bsi_move_before (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bsi_stmt (int /*<<< orphan*/ ) ; 
 scalar_t__ is_ctrl_stmt (int /*<<< orphan*/ ) ; 

void
bsi_move_to_bb_end (block_stmt_iterator *from, basic_block bb)
{
  block_stmt_iterator last = bsi_last (bb);

  /* Have to check bsi_end_p because it could be an empty block.  */
  if (!bsi_end_p (last) && is_ctrl_stmt (bsi_stmt (last)))
    bsi_move_before (from, &last);
  else
    bsi_move_after (from, &last);
}