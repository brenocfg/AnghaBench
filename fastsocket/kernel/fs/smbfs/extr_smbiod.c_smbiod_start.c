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
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int PTR_ERR (struct task_struct*) ; 
 scalar_t__ SMBIOD_DEAD ; 
 scalar_t__ SMBIOD_RUNNING ; 
 scalar_t__ SMBIOD_STARTING ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 struct task_struct* kthread_run (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  servers_lock ; 
 int /*<<< orphan*/  smbiod ; 
 scalar_t__ smbiod_state ; 
 struct task_struct* smbiod_thread ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smbiod_start(void)
{
	struct task_struct *tsk;
	int err = 0;

	if (smbiod_state != SMBIOD_DEAD)
		return 0;
	smbiod_state = SMBIOD_STARTING;
	__module_get(THIS_MODULE);
	spin_unlock(&servers_lock);
	tsk = kthread_run(smbiod, NULL, "smbiod");
	if (IS_ERR(tsk)) {
		err = PTR_ERR(tsk);
		module_put(THIS_MODULE);
	}

	spin_lock(&servers_lock);
	if (err < 0) {
		smbiod_state = SMBIOD_DEAD;
		smbiod_thread = NULL;
	} else {
		smbiod_state = SMBIOD_RUNNING;
		smbiod_thread = tsk;
	}
	return err;
}