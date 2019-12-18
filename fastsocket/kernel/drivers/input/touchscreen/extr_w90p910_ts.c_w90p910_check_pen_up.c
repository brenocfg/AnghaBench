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
struct w90p910_ts {scalar_t__ state; int /*<<< orphan*/  lock; scalar_t__ ts_reg; } ;

/* Variables and functions */
 int ADC_DOWN ; 
 scalar_t__ TS_WAIT_NEW_PACKET ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  w90p910_report_event (struct w90p910_ts*,int) ; 

__attribute__((used)) static void w90p910_check_pen_up(unsigned long data)
{
	struct w90p910_ts *w90p910_ts = (struct w90p910_ts *) data;
	unsigned long flags;

	spin_lock_irqsave(&w90p910_ts->lock, flags);

	if (w90p910_ts->state == TS_WAIT_NEW_PACKET &&
	    !(__raw_readl(w90p910_ts->ts_reg + 0x04) & ADC_DOWN)) {

		w90p910_report_event(w90p910_ts, false);
	}

	spin_unlock_irqrestore(&w90p910_ts->lock, flags);
}