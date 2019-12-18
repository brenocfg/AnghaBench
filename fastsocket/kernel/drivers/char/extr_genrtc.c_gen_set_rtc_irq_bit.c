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

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_rtc_irq_data ; 
 int /*<<< orphan*/  gen_rtc_lock ; 
 int /*<<< orphan*/  genrtc_task ; 
 int /*<<< orphan*/  genrtc_troutine ; 
 int /*<<< orphan*/  get_rtc_ss () ; 
 int /*<<< orphan*/  init_timer (int /*<<< orphan*/ *) ; 
 int irq_active ; 
 scalar_t__ lostint ; 
 int /*<<< orphan*/  oldsecs ; 
 scalar_t__ schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stask_active ; 
 scalar_t__ stop_rtc_timers ; 
 int /*<<< orphan*/  timer_task ; 

__attribute__((used)) static inline int gen_set_rtc_irq_bit(unsigned char bit)
{
#ifdef CONFIG_GEN_RTC_X
	spin_lock(&gen_rtc_lock);
	if ( !irq_active ) {
		irq_active = 1;
		stop_rtc_timers = 0;
		lostint = 0;
		INIT_WORK(&genrtc_task, genrtc_troutine);
		oldsecs = get_rtc_ss();
		init_timer(&timer_task);

		stask_active = 1;
		if (schedule_work(&genrtc_task) == 0){
			stask_active = 0;
		}
	}
	spin_unlock(&gen_rtc_lock);
	gen_rtc_irq_data = 0;
	return 0;
#else
	return -EINVAL;
#endif
}