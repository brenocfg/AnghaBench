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
struct w90p910_ts {int /*<<< orphan*/  clk; int /*<<< orphan*/  timer; int /*<<< orphan*/  lock; int /*<<< orphan*/  ts_reg; int /*<<< orphan*/  state; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 unsigned long ADC_DIV ; 
 unsigned long ADC_EN ; 
 unsigned long ADC_INT_EN ; 
 unsigned long ADC_WAITTRIG ; 
 int /*<<< orphan*/  TS_IDLE ; 
 unsigned long WT_INT_EN ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct w90p910_ts* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void w90p910_close(struct input_dev *dev)
{
	struct w90p910_ts *w90p910_ts = input_get_drvdata(dev);
	unsigned long val;

	/* disable trigger mode */

	spin_lock_irq(&w90p910_ts->lock);

	w90p910_ts->state = TS_IDLE;

	val = __raw_readl(w90p910_ts->ts_reg);
	val &= ~(ADC_WAITTRIG | ADC_DIV | ADC_EN | WT_INT_EN | ADC_INT_EN);
	__raw_writel(val, w90p910_ts->ts_reg);

	spin_unlock_irq(&w90p910_ts->lock);

	/* Now that interrupts are shut off we can safely delete timer */
	del_timer_sync(&w90p910_ts->timer);

	/* stop the ADC clock */
	clk_disable(w90p910_ts->clk);
}