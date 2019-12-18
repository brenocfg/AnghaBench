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
struct ucb1x00_ts {int /*<<< orphan*/  irq_wait; int /*<<< orphan*/  ucb; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCB_FALLING ; 
 int /*<<< orphan*/  UCB_IRQ_TSPX ; 
 int /*<<< orphan*/  ucb1x00_disable_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ucb1x00_ts_irq(int idx, void *id)
{
	struct ucb1x00_ts *ts = id;

	ucb1x00_disable_irq(ts->ucb, UCB_IRQ_TSPX, UCB_FALLING);
	wake_up(&ts->irq_wait);
}