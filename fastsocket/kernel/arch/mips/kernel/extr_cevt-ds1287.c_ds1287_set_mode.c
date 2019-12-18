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
typedef  int /*<<< orphan*/  u8 ;
struct clock_event_device {int dummy; } ;
typedef  enum clock_event_mode { ____Placeholder_clock_event_mode } clock_event_mode ;

/* Variables and functions */
#define  CLOCK_EVT_MODE_PERIODIC 128 
 int /*<<< orphan*/  CMOS_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMOS_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_PIE ; 
 int /*<<< orphan*/  RTC_REG_B ; 
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ds1287_set_mode(enum clock_event_mode mode,
			    struct clock_event_device *evt)
{
	u8 val;

	spin_lock(&rtc_lock);

	val = CMOS_READ(RTC_REG_B);

	switch (mode) {
	case CLOCK_EVT_MODE_PERIODIC:
		val |= RTC_PIE;
		break;
	default:
		val &= ~RTC_PIE;
		break;
	}

	CMOS_WRITE(val, RTC_REG_B);

	spin_unlock(&rtc_lock);
}