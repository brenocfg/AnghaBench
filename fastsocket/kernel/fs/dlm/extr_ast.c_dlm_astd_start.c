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
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int PTR_ERR (struct task_struct*) ; 
 int /*<<< orphan*/  ast_queue ; 
 int /*<<< orphan*/  ast_queue_lock ; 
 int /*<<< orphan*/  astd_running ; 
 struct task_struct* astd_task ; 
 int /*<<< orphan*/  dlm_astd ; 
 struct task_struct* kthread_run (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int dlm_astd_start(void)
{
	struct task_struct *p;
	int error = 0;

	INIT_LIST_HEAD(&ast_queue);
	spin_lock_init(&ast_queue_lock);
	mutex_init(&astd_running);

	p = kthread_run(dlm_astd, NULL, "dlm_astd");
	if (IS_ERR(p))
		error = PTR_ERR(p);
	else
		astd_task = p;
	return error;
}