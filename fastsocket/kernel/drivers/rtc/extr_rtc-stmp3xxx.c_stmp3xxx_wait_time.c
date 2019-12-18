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
struct stmp3xxx_rtc_data {scalar_t__ io; } ;

/* Variables and functions */
 int BF (int,int /*<<< orphan*/ ) ; 
 scalar_t__ HW_RTC_STAT ; 
 int /*<<< orphan*/  RTC_STAT_STALE_REGS ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  cpu_relax () ; 

__attribute__((used)) static void stmp3xxx_wait_time(struct stmp3xxx_rtc_data *rtc_data)
{
	/*
	 * The datasheet doesn't say which way round the
	 * NEW_REGS/STALE_REGS bitfields go. In fact it's 0x1=P0,
	 * 0x2=P1, .., 0x20=P5, 0x40=ALARM, 0x80=SECONDS
	 */
	while (__raw_readl(rtc_data->io + HW_RTC_STAT) &
			BF(0x80, RTC_STAT_STALE_REGS))
		cpu_relax();
}