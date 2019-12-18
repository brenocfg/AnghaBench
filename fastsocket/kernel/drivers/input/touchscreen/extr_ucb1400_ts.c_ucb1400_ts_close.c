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
struct ucb1400_ts {int /*<<< orphan*/  ac97; scalar_t__ ts_task; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCB_TS_CR ; 
 struct ucb1400_ts* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  kthread_stop (scalar_t__) ; 
 int /*<<< orphan*/  ucb1400_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucb1400_ts_irq_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ucb1400_ts_close(struct input_dev *idev)
{
	struct ucb1400_ts *ucb = input_get_drvdata(idev);

	if (ucb->ts_task)
		kthread_stop(ucb->ts_task);

	ucb1400_ts_irq_disable(ucb->ac97);
	ucb1400_reg_write(ucb->ac97, UCB_TS_CR, 0);
}