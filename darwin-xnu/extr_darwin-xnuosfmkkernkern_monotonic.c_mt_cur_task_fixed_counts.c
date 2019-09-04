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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  task_t ;

/* Variables and functions */
 int /*<<< orphan*/  current_task () ; 
 int /*<<< orphan*/  mt_fixed_task_counts (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
mt_cur_task_fixed_counts(uint64_t *counts)
{
	task_t curtask = current_task();

	mt_fixed_task_counts(curtask, counts);
}