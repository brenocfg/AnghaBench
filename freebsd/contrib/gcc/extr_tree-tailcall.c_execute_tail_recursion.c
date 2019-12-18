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
 int /*<<< orphan*/  tree_optimize_tail_calls_1 (int) ; 

__attribute__((used)) static unsigned int
execute_tail_recursion (void)
{
  tree_optimize_tail_calls_1 (false);
  return 0;
}