#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct loop {TYPE_1__* single_exit; } ;
struct TYPE_2__ {scalar_t__ dest; } ;

/* Variables and functions */
 scalar_t__ PHI_NODE ; 
 int PHI_NUM_ARGS (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ bb_for_stmt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
exit_phi_for_loop_p (struct loop *loop, tree stmt)
{
  
  if (TREE_CODE (stmt) != PHI_NODE
      || PHI_NUM_ARGS (stmt) != 1
      || bb_for_stmt (stmt) != loop->single_exit->dest)
    return false;
  
  return true;
}