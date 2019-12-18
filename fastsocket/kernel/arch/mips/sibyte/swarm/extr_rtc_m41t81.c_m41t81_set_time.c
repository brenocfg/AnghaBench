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
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_wday; int tm_mday; int tm_mon; int tm_year; } ;

/* Variables and functions */
 int /*<<< orphan*/  M41T81REG_DT ; 
 int /*<<< orphan*/  M41T81REG_DY ; 
 int /*<<< orphan*/  M41T81REG_HR ; 
 int /*<<< orphan*/  M41T81REG_MN ; 
 int /*<<< orphan*/  M41T81REG_MO ; 
 int /*<<< orphan*/  M41T81REG_SC ; 
 int /*<<< orphan*/  M41T81REG_YR ; 
 void* bin2bcd (int) ; 
 int m41t81_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m41t81_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  rtc_time_to_tm (unsigned long,struct rtc_time*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int m41t81_set_time(unsigned long t)
{
	struct rtc_time tm;
	unsigned long flags;

	/* Note we don't care about the century */
	rtc_time_to_tm(t, &tm);

	/*
	 * Note the write order matters as it ensures the correctness.
	 * When we write sec, 10th sec is clear.  It is reasonable to
	 * believe we should finish writing min within a second.
	 */

	spin_lock_irqsave(&rtc_lock, flags);
	tm.tm_sec = bin2bcd(tm.tm_sec);
	m41t81_write(M41T81REG_SC, tm.tm_sec);

	tm.tm_min = bin2bcd(tm.tm_min);
	m41t81_write(M41T81REG_MN, tm.tm_min);

	tm.tm_hour = bin2bcd(tm.tm_hour);
	tm.tm_hour = (tm.tm_hour & 0x3f) | (m41t81_read(M41T81REG_HR) & 0xc0);
	m41t81_write(M41T81REG_HR, tm.tm_hour);

	/* tm_wday starts from 0 to 6 */
	if (tm.tm_wday == 0) tm.tm_wday = 7;
	tm.tm_wday = bin2bcd(tm.tm_wday);
	m41t81_write(M41T81REG_DY, tm.tm_wday);

	tm.tm_mday = bin2bcd(tm.tm_mday);
	m41t81_write(M41T81REG_DT, tm.tm_mday);

	/* tm_mon starts from 0, *ick* */
	tm.tm_mon ++;
	tm.tm_mon = bin2bcd(tm.tm_mon);
	m41t81_write(M41T81REG_MO, tm.tm_mon);

	/* we don't do century, everything is beyond 2000 */
	tm.tm_year %= 100;
	tm.tm_year = bin2bcd(tm.tm_year);
	m41t81_write(M41T81REG_YR, tm.tm_year);
	spin_unlock_irqrestore(&rtc_lock, flags);

	return 0;
}