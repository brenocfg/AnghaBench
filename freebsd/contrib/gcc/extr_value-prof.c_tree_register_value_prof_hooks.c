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
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ir_type () ; 
 int /*<<< orphan*/  tree_value_prof_hooks ; 
 int /*<<< orphan*/ * value_prof_hooks ; 

void
tree_register_value_prof_hooks (void)
{
  value_prof_hooks = &tree_value_prof_hooks;
  gcc_assert (ir_type ());
}