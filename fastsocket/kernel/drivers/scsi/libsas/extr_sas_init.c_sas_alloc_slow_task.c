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
struct sas_task_slow {int /*<<< orphan*/  completion; int /*<<< orphan*/  timer; } ;
struct sas_task {struct sas_task_slow* slow_task; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct sas_task_slow*) ; 
 struct sas_task_slow* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct sas_task*) ; 
 struct sas_task* sas_alloc_task (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_task_cache ; 

struct sas_task *sas_alloc_slow_task(gfp_t flags)
{
	struct sas_task *task = sas_alloc_task(flags);
	struct sas_task_slow *slow = kmalloc(sizeof(*slow), flags);

	if (!task || !slow) {
		if (task)
			kmem_cache_free(sas_task_cache, task);
		kfree(slow);
		return NULL;
	}

	task->slow_task = slow;
	init_timer(&slow->timer);
	init_completion(&slow->completion);

	return task;
}