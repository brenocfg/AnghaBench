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
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  mpol_fix_fork_child_flag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mpol_set_task_struct_flag(void)
{
	mpol_fix_fork_child_flag(current);
}