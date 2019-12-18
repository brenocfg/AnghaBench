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
struct task_struct {int /*<<< orphan*/  dirties; } ;

/* Variables and functions */
 int /*<<< orphan*/  prop_inc_single (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_dirties ; 

void task_dirty_inc(struct task_struct *tsk)
{
	prop_inc_single(&vm_dirties, &tsk->dirties);
}