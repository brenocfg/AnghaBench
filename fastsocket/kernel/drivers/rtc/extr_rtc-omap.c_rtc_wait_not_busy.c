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
typedef  int u8 ;

/* Variables and functions */
 scalar_t__ OMAP_RTC_STATUS_BUSY ; 
 int /*<<< orphan*/  OMAP_RTC_STATUS_REG ; 
 int rtc_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void rtc_wait_not_busy(void)
{
	int	count = 0;
	u8	status;

	/* BUSY may stay active for 1/32768 second (~30 usec) */
	for (count = 0; count < 50; count++) {
		status = rtc_read(OMAP_RTC_STATUS_REG);
		if ((status & (u8)OMAP_RTC_STATUS_BUSY) == 0)
			break;
		udelay(1);
	}
	/* now we have ~15 usec to read/write various registers */
}