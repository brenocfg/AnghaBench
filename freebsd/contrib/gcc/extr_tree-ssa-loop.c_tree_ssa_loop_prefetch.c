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
 unsigned int tree_ssa_prefetch_arrays (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
tree_ssa_loop_prefetch (void)
{
  if (!current_loops)
    return 0;

  return tree_ssa_prefetch_arrays (current_loops);
}