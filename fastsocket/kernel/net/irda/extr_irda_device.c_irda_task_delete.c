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
struct irda_task {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __irda_task_delete (struct irda_task*) ; 
 int /*<<< orphan*/  hashbin_remove (int /*<<< orphan*/ ,long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasks ; 

__attribute__((used)) static void irda_task_delete(struct irda_task *task)
{
	/* Unregister task */
	hashbin_remove(tasks, (long) task, NULL);

	__irda_task_delete(task);
}