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
typedef  scalar_t__ tree ;
struct iv_cand {scalar_t__ incremented_at; } ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  scalar_t__ basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  CDI_DOMINATORS ; 
 scalar_t__ bb_for_stmt (scalar_t__) ; 
 int /*<<< orphan*/  bsi_last (scalar_t__) ; 
 int /*<<< orphan*/  bsi_prev (int /*<<< orphan*/ *) ; 
 scalar_t__ bsi_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dominated_by_p (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool
stmt_after_ip_original_pos (struct iv_cand *cand, tree stmt)
{
  basic_block cand_bb = bb_for_stmt (cand->incremented_at);
  basic_block stmt_bb = bb_for_stmt (stmt);
  block_stmt_iterator bsi;

  if (!dominated_by_p (CDI_DOMINATORS, stmt_bb, cand_bb))
    return false;

  if (stmt_bb != cand_bb)
    return true;

  /* Scan the block from the end, since the original ivs are usually
     incremented at the end of the loop body.  */
  for (bsi = bsi_last (stmt_bb); ; bsi_prev (&bsi))
    {
      if (bsi_stmt (bsi) == cand->incremented_at)
	return false;
      if (bsi_stmt (bsi) == stmt)
	return true;
    }
}