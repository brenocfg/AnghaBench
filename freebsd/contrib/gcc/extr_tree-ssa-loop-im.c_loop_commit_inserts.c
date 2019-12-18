#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_4__ {int /*<<< orphan*/  loop_father; } ;
struct TYPE_3__ {int /*<<< orphan*/  loop_father; } ;

/* Variables and functions */
 int /*<<< orphan*/  BASIC_BLOCK (unsigned int) ; 
 int /*<<< orphan*/  add_bb_to_loop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_commit_edge_inserts () ; 
 int /*<<< orphan*/  find_common_loop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int last_basic_block ; 
 TYPE_2__* single_pred (int /*<<< orphan*/ ) ; 
 TYPE_1__* single_succ (int /*<<< orphan*/ ) ; 

void
loop_commit_inserts (void)
{
  unsigned old_last_basic_block, i;
  basic_block bb;

  old_last_basic_block = last_basic_block;
  bsi_commit_edge_inserts ();
  for (i = old_last_basic_block; i < (unsigned) last_basic_block; i++)
    {
      bb = BASIC_BLOCK (i);
      add_bb_to_loop (bb,
		      find_common_loop (single_pred (bb)->loop_father,
					single_succ (bb)->loop_father));
    }
}