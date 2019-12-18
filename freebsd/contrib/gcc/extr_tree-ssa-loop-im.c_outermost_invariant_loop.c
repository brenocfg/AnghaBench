#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct loop {int depth; } ;
typedef  TYPE_2__* basic_block ;
struct TYPE_7__ {TYPE_1__* max_loop; } ;
struct TYPE_6__ {int /*<<< orphan*/  loop_father; } ;
struct TYPE_5__ {int /*<<< orphan*/  outer; } ;

/* Variables and functions */
 TYPE_4__* LIM_DATA (int /*<<< orphan*/ ) ; 
 scalar_t__ SSA_NAME ; 
 int /*<<< orphan*/  SSA_NAME_DEF_STMT (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 TYPE_2__* bb_for_stmt (int /*<<< orphan*/ ) ; 
 struct loop* find_common_loop (struct loop*,int /*<<< orphan*/ ) ; 
 struct loop* superloop_at_depth (struct loop*,int) ; 

__attribute__((used)) static struct loop *
outermost_invariant_loop (tree def, struct loop *loop)
{
  tree def_stmt;
  basic_block def_bb;
  struct loop *max_loop;

  if (TREE_CODE (def) != SSA_NAME)
    return superloop_at_depth (loop, 1);

  def_stmt = SSA_NAME_DEF_STMT (def);
  def_bb = bb_for_stmt (def_stmt);
  if (!def_bb)
    return superloop_at_depth (loop, 1);

  max_loop = find_common_loop (loop, def_bb->loop_father);

  if (LIM_DATA (def_stmt) && LIM_DATA (def_stmt)->max_loop)
    max_loop = find_common_loop (max_loop,
				 LIM_DATA (def_stmt)->max_loop->outer);
  if (max_loop == loop)
    return NULL;
  max_loop = superloop_at_depth (loop, max_loop->depth + 1);

  return max_loop;
}