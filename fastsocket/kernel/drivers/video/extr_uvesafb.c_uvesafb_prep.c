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
struct uvesafb_ktask {void* done; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct uvesafb_ktask*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct uvesafb_ktask *uvesafb_prep(void)
{
	struct uvesafb_ktask *task;

	task = kzalloc(sizeof(*task), GFP_KERNEL);
	if (task) {
		task->done = kzalloc(sizeof(*task->done), GFP_KERNEL);
		if (!task->done) {
			kfree(task);
			task = NULL;
		}
	}
	return task;
}