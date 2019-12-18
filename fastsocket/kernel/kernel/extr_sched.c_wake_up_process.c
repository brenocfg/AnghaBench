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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_ALL ; 
 int try_to_wake_up (struct task_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int wake_up_process(struct task_struct *p)
{
	return try_to_wake_up(p, TASK_ALL, 0);
}