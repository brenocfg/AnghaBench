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
struct redirection_data {TYPE_1__* dup_block; } ;
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_3__ {scalar_t__ count; scalar_t__ frequency; } ;

/* Variables and functions */
 TYPE_1__* duplicate_block (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_ctrl_stmt_and_useless_edges (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
create_block_for_threading (basic_block bb, struct redirection_data *rd)
{
  /* We can use the generic block duplication code and simply remove
     the stuff we do not need.  */
  rd->dup_block = duplicate_block (bb, NULL, NULL);

  /* Zero out the profile, since the block is unreachable for now.  */
  rd->dup_block->frequency = 0;
  rd->dup_block->count = 0;

  /* The call to duplicate_block will copy everything, including the
     useless COND_EXPR or SWITCH_EXPR at the end of BB.  We just remove
     the useless COND_EXPR or SWITCH_EXPR here rather than having a
     specialized block copier.  We also remove all outgoing edges
     from the duplicate block.  The appropriate edge will be created
     later.  */
  remove_ctrl_stmt_and_useless_edges (rd->dup_block, NULL);
}