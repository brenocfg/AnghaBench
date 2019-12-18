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
typedef  scalar_t__ task_t ;

/* Variables and functions */
 scalar_t__ current_task () ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  user_ldt_set (int /*<<< orphan*/ ) ; 

void
user_ldt_set_action(
	void *arg)
{
	task_t		arg_task = (task_t)arg;

	if (arg_task == current_task())	{
	    user_ldt_set(current_thread());
	}
}