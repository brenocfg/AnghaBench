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
struct ucb1400_ts {int /*<<< orphan*/ * ts_task; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 struct ucb1400_ts* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/ * kthread_run (int /*<<< orphan*/ ,struct ucb1400_ts*,char*) ; 
 int /*<<< orphan*/  ucb1400_ts_thread ; 

__attribute__((used)) static int ucb1400_ts_open(struct input_dev *idev)
{
	struct ucb1400_ts *ucb = input_get_drvdata(idev);
	int ret = 0;

	BUG_ON(ucb->ts_task);

	ucb->ts_task = kthread_run(ucb1400_ts_thread, ucb, "UCB1400_ts");
	if (IS_ERR(ucb->ts_task)) {
		ret = PTR_ERR(ucb->ts_task);
		ucb->ts_task = NULL;
	}

	return ret;
}