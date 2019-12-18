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
 int /*<<< orphan*/ * profile_hooks ; 
 int /*<<< orphan*/  tree_profile_hooks ; 

void
tree_register_profile_hooks (void)
{
  gcc_assert (ir_type ());
  profile_hooks = &tree_profile_hooks;
}