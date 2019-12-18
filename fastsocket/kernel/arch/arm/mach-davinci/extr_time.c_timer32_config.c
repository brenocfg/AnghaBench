#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct timer_s {int period; int enamode_shift; int opts; scalar_t__ base; scalar_t__ prd_off; scalar_t__ tim_off; } ;
struct davinci_timer_instance {scalar_t__ cmp_off; } ;
struct davinci_soc_info {TYPE_1__* timer_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_3__ {struct davinci_timer_instance* timers; } ;

/* Variables and functions */
 int ID_TO_TIMER (int /*<<< orphan*/ ) ; 
 scalar_t__ TCR ; 
 int TCR_ENAMODE_MASK ; 
 int TCR_ENAMODE_ONESHOT ; 
 int TCR_ENAMODE_PERIODIC ; 
 size_t TID_CLOCKEVENT ; 
 int TIMER_OPTS_ONESHOT ; 
 int TIMER_OPTS_PERIODIC ; 
 scalar_t__ USING_COMPARE (struct timer_s*) ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 struct davinci_soc_info davinci_soc_info ; 
 TYPE_2__* timers ; 

__attribute__((used)) static int timer32_config(struct timer_s *t)
{
	u32 tcr;
	struct davinci_soc_info *soc_info = &davinci_soc_info;

	if (USING_COMPARE(t)) {
		struct davinci_timer_instance *dtip =
				soc_info->timer_info->timers;
		int event_timer = ID_TO_TIMER(timers[TID_CLOCKEVENT].id);

		/*
		 * Next interrupt should be the current time reg value plus
		 * the new period (using 32-bit unsigned addition/wrapping
		 * to 0 on overflow).  This assumes that the clocksource
		 * is setup to count to 2^32-1 before wrapping around to 0.
		 */
		__raw_writel(__raw_readl(t->base + t->tim_off) + t->period,
			t->base + dtip[event_timer].cmp_off);
	} else {
		tcr = __raw_readl(t->base + TCR);

		/* disable timer */
		tcr &= ~(TCR_ENAMODE_MASK << t->enamode_shift);
		__raw_writel(tcr, t->base + TCR);

		/* reset counter to zero, set new period */
		__raw_writel(0, t->base + t->tim_off);
		__raw_writel(t->period, t->base + t->prd_off);

		/* Set enable mode */
		if (t->opts & TIMER_OPTS_ONESHOT)
			tcr |= TCR_ENAMODE_ONESHOT << t->enamode_shift;
		else if (t->opts & TIMER_OPTS_PERIODIC)
			tcr |= TCR_ENAMODE_PERIODIC << t->enamode_shift;

		__raw_writel(tcr, t->base + TCR);
	}
	return 0;
}