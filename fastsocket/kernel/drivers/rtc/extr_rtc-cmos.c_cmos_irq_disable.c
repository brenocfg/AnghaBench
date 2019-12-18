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
struct cmos_rtc {int dummy; } ;

/* Variables and functions */
 unsigned char CMOS_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMOS_WRITE (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_CONTROL ; 
 int /*<<< orphan*/  cmos_checkintr (struct cmos_rtc*,unsigned char) ; 
 int /*<<< orphan*/  hpet_mask_rtc_irq_bit (unsigned char) ; 

__attribute__((used)) static void cmos_irq_disable(struct cmos_rtc *cmos, unsigned char mask)
{
	unsigned char	rtc_control;

	rtc_control = CMOS_READ(RTC_CONTROL);
	rtc_control &= ~mask;
	CMOS_WRITE(rtc_control, RTC_CONTROL);
	hpet_mask_rtc_irq_bit(mask);

	cmos_checkintr(cmos, rtc_control);
}