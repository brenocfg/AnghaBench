#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * j_task; int /*<<< orphan*/  j_wait_done_commit; } ;
typedef  TYPE_1__ journal_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int PTR_ERR (struct task_struct*) ; 
 int /*<<< orphan*/  kjournald ; 
 struct task_struct* kthread_run (int /*<<< orphan*/ ,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int journal_start_thread(journal_t *journal)
{
	struct task_struct *t;

	t = kthread_run(kjournald, journal, "kjournald");
	if (IS_ERR(t))
		return PTR_ERR(t);

	wait_event(journal->j_wait_done_commit, journal->j_task != NULL);
	return 0;
}