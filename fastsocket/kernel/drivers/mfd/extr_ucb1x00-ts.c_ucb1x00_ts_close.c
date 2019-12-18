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
struct ucb1x00_ts {int /*<<< orphan*/  ucb; scalar_t__ rtask; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCB_IRQ_TSPX ; 
 int /*<<< orphan*/  UCB_TS_CR ; 
 struct ucb1x00_ts* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  kthread_stop (scalar_t__) ; 
 int /*<<< orphan*/  ucb1x00_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucb1x00_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucb1x00_free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ucb1x00_ts*) ; 
 int /*<<< orphan*/  ucb1x00_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ucb1x00_ts_close(struct input_dev *idev)
{
	struct ucb1x00_ts *ts = input_get_drvdata(idev);

	if (ts->rtask)
		kthread_stop(ts->rtask);

	ucb1x00_enable(ts->ucb);
	ucb1x00_free_irq(ts->ucb, UCB_IRQ_TSPX, ts);
	ucb1x00_reg_write(ts->ucb, UCB_TS_CR, 0);
	ucb1x00_disable(ts->ucb);
}