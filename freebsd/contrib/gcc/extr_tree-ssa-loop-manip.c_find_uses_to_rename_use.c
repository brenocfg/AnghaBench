#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct loop {int /*<<< orphan*/  outer; } ;
typedef  scalar_t__ bitmap ;
typedef  TYPE_1__* basic_block ;
struct TYPE_4__ {unsigned int index; struct loop* loop_father; } ;

/* Variables and functions */
 scalar_t__ BITMAP_ALLOC (int /*<<< orphan*/ *) ; 
 scalar_t__ SSA_NAME ; 
 int /*<<< orphan*/  SSA_NAME_DEF_STMT (int /*<<< orphan*/ ) ; 
 unsigned int SSA_NAME_VERSION (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 TYPE_1__* bb_for_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_set_bit (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  is_gimple_reg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
find_uses_to_rename_use (basic_block bb, tree use, bitmap *use_blocks,
			 bitmap need_phis)
{
  unsigned ver;
  basic_block def_bb;
  struct loop *def_loop;

  if (TREE_CODE (use) != SSA_NAME)
    return;

  /* We don't need to keep virtual operands in loop-closed form.  */
  if (!is_gimple_reg (use))
    return;

  ver = SSA_NAME_VERSION (use);
  def_bb = bb_for_stmt (SSA_NAME_DEF_STMT (use));
  if (!def_bb)
    return;
  def_loop = def_bb->loop_father;

  /* If the definition is not inside loop, it is not interesting.  */
  if (!def_loop->outer)
    return;

  if (!use_blocks[ver])
    use_blocks[ver] = BITMAP_ALLOC (NULL);
  bitmap_set_bit (use_blocks[ver], bb->index);

  bitmap_set_bit (need_phis, ver);
}