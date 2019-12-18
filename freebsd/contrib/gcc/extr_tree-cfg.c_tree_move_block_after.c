#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* basic_block ;
struct TYPE_7__ {struct TYPE_7__* prev_bb; } ;

/* Variables and functions */
 int /*<<< orphan*/  link_block (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  unlink_block (TYPE_1__*) ; 

__attribute__((used)) static bool
tree_move_block_after (basic_block bb, basic_block after)
{
  if (bb->prev_bb == after)
    return true;

  unlink_block (bb);
  link_block (bb, after);

  return true;
}