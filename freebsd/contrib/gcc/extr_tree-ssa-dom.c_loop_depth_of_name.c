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
typedef  TYPE_1__* basic_block ;
struct TYPE_3__ {int loop_depth; } ;

/* Variables and functions */
 scalar_t__ SSA_NAME ; 
 int /*<<< orphan*/  SSA_NAME_DEF_STMT (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 TYPE_1__* bb_for_stmt (int /*<<< orphan*/ ) ; 

int
loop_depth_of_name (tree x)
{
  tree defstmt;
  basic_block defbb;

  /* If it's not an SSA_NAME, we have no clue where the definition is.  */
  if (TREE_CODE (x) != SSA_NAME)
    return 0;

  /* Otherwise return the loop depth of the defining statement's bb.
     Note that there may not actually be a bb for this statement, if the
     ssa_name is live on entry.  */
  defstmt = SSA_NAME_DEF_STMT (x);
  defbb = bb_for_stmt (defstmt);
  if (!defbb)
    return 0;

  return defbb->loop_depth;
}