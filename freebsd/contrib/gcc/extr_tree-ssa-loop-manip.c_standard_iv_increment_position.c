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
struct loop {int dummy; } ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 scalar_t__ LABEL_EXPR ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  bsi_last (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_end_pos (struct loop*) ; 
 int /*<<< orphan*/  ip_normal_pos (struct loop*) ; 
 scalar_t__ last_stmt (int /*<<< orphan*/ ) ; 

void
standard_iv_increment_position (struct loop *loop, block_stmt_iterator *bsi,
				bool *insert_after)
{
  basic_block bb = ip_normal_pos (loop), latch = ip_end_pos (loop);
  tree last = last_stmt (latch);

  if (!bb
      || (last && TREE_CODE (last) != LABEL_EXPR))
    {
      *bsi = bsi_last (latch);
      *insert_after = true;
    }
  else
    {
      *bsi = bsi_last (bb);
      *insert_after = false;
    }
}