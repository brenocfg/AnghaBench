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

/* Variables and functions */
 int /*<<< orphan*/  current_loops ; 
 int /*<<< orphan*/  tree_ssa_iv_optimize (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
tree_ssa_loop_ivopts (void)
{
  if (!current_loops)
    return 0;

  tree_ssa_iv_optimize (current_loops);
  return 0;
}