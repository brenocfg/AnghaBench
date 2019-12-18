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
struct se_lun {int /*<<< orphan*/  lun_shutdown_comp; int /*<<< orphan*/  unpacked_lun; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int PTR_ERR (struct task_struct*) ; 
 struct task_struct* kthread_run (int /*<<< orphan*/ ,struct se_lun*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  transport_clear_lun_thread ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int transport_clear_lun_from_sessions(struct se_lun *lun)
{
	struct task_struct *kt;

	kt = kthread_run(transport_clear_lun_thread, lun,
			"tcm_cl_%u", lun->unpacked_lun);
	if (IS_ERR(kt)) {
		pr_err("Unable to start clear_lun thread\n");
		return PTR_ERR(kt);
	}
	wait_for_completion(&lun->lun_shutdown_comp);

	return 0;
}