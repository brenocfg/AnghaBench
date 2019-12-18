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
struct rtc_time {scalar_t__ tm_min; scalar_t__ tm_hour; scalar_t__ tm_mon; scalar_t__ tm_year; int tm_sec; int tm_mday; } ;
struct rtc_wkalrm {struct rtc_time time; int /*<<< orphan*/  enabled; } ;
struct rtc_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memcpy (struct rtc_time*,struct rtc_time*,int) ; 
 unsigned int rtc_month_days (int,scalar_t__) ; 
 int rtc_read_alarm_internal (struct rtc_device*,struct rtc_wkalrm*) ; 
 int rtc_read_time (struct rtc_device*,struct rtc_time*) ; 
 int /*<<< orphan*/  rtc_time_to_tm (unsigned long,struct rtc_time*) ; 
 int /*<<< orphan*/  rtc_tm_to_time (struct rtc_time*,unsigned long*) ; 
 scalar_t__ rtc_valid_tm (struct rtc_time*) ; 

int rtc_read_alarm(struct rtc_device *rtc, struct rtc_wkalrm *alarm)
{
	int err;
	struct rtc_time before, now;
	int first_time = 1;
	unsigned long t_now, t_alm;
	enum { none, day, month, year } missing = none;
	unsigned days;

	/* The lower level RTC driver may return -1 in some fields,
	 * creating invalid alarm->time values, for reasons like:
	 *
	 *   - The hardware may not be capable of filling them in;
	 *     many alarms match only on time-of-day fields, not
	 *     day/month/year calendar data.
	 *
	 *   - Some hardware uses illegal values as "wildcard" match
	 *     values, which non-Linux firmware (like a BIOS) may try
	 *     to set up as e.g. "alarm 15 minutes after each hour".
	 *     Linux uses only oneshot alarms.
	 *
	 * When we see that here, we deal with it by using values from
	 * a current RTC timestamp for any missing (-1) values.  The
	 * RTC driver prevents "periodic alarm" modes.
	 *
	 * But this can be racey, because some fields of the RTC timestamp
	 * may have wrapped in the interval since we read the RTC alarm,
	 * which would lead to us inserting inconsistent values in place
	 * of the -1 fields.
	 *
	 * Reading the alarm and timestamp in the reverse sequence
	 * would have the same race condition, and not solve the issue.
	 *
	 * So, we must first read the RTC timestamp,
	 * then read the RTC alarm value,
	 * and then read a second RTC timestamp.
	 *
	 * If any fields of the second timestamp have changed
	 * when compared with the first timestamp, then we know
	 * our timestamp may be inconsistent with that used by
	 * the low-level rtc_read_alarm_internal() function.
	 *
	 * So, when the two timestamps disagree, we just loop and do
	 * the process again to get a fully consistent set of values.
	 *
	 * This could all instead be done in the lower level driver,
	 * but since more than one lower level RTC implementation needs it,
	 * then it's probably best best to do it here instead of there..
	 */

	/* Get the "before" timestamp */
	err = rtc_read_time(rtc, &before);
	if (err < 0)
		return err;
	do {
		if (!first_time)
			memcpy(&before, &now, sizeof(struct rtc_time));
		first_time = 0;

		/* get the RTC alarm values, which may be incomplete */
		err = rtc_read_alarm_internal(rtc, alarm);
		if (err)
			return err;
		if (!alarm->enabled)
			return 0;

		/* full-function RTCs won't have such missing fields */
		if (rtc_valid_tm(&alarm->time) == 0)
			return 0;

		/* get the "after" timestamp, to detect wrapped fields */
		err = rtc_read_time(rtc, &now);
		if (err < 0)
			return err;

		/* note that tm_sec is a "don't care" value here: */
	} while (   before.tm_min   != now.tm_min
		 || before.tm_hour  != now.tm_hour
		 || before.tm_mon   != now.tm_mon
		 || before.tm_year  != now.tm_year);

	/* Fill in the missing alarm fields using the timestamp; we
	 * know there's at least one since alarm->time is invalid.
	 */
	if (alarm->time.tm_sec == -1)
		alarm->time.tm_sec = now.tm_sec;
	if (alarm->time.tm_min == -1)
		alarm->time.tm_min = now.tm_min;
	if (alarm->time.tm_hour == -1)
		alarm->time.tm_hour = now.tm_hour;

	/* For simplicity, only support date rollover for now */
	if (alarm->time.tm_mday == -1) {
		alarm->time.tm_mday = now.tm_mday;
		missing = day;
	}
	if (alarm->time.tm_mon == -1) {
		alarm->time.tm_mon = now.tm_mon;
		if (missing == none)
			missing = month;
	}
	if (alarm->time.tm_year == -1) {
		alarm->time.tm_year = now.tm_year;
		if (missing == none)
			missing = year;
	}

	/* with luck, no rollover is needed */
	rtc_tm_to_time(&now, &t_now);
	rtc_tm_to_time(&alarm->time, &t_alm);
	if (t_now < t_alm)
		goto done;

	switch (missing) {

	/* 24 hour rollover ... if it's now 10am Monday, an alarm that
	 * that will trigger at 5am will do so at 5am Tuesday, which
	 * could also be in the next month or year.  This is a common
	 * case, especially for PCs.
	 */
	case day:
		dev_dbg(&rtc->dev, "alarm rollover: %s\n", "day");
		t_alm += 24 * 60 * 60;
		rtc_time_to_tm(t_alm, &alarm->time);
		break;

	/* Month rollover ... if it's the 31th, an alarm on the 3rd will
	 * be next month.  An alarm matching on the 30th, 29th, or 28th
	 * may end up in the month after that!  Many newer PCs support
	 * this type of alarm.
	 */
	case month:
		dev_dbg(&rtc->dev, "alarm rollover: %s\n", "month");
		do {
			if (alarm->time.tm_mon < 11)
				alarm->time.tm_mon++;
			else {
				alarm->time.tm_mon = 0;
				alarm->time.tm_year++;
			}
			days = rtc_month_days(alarm->time.tm_mon,
					alarm->time.tm_year);
		} while (days < alarm->time.tm_mday);
		break;

	/* Year rollover ... easy except for leap years! */
	case year:
		dev_dbg(&rtc->dev, "alarm rollover: %s\n", "year");
		do {
			alarm->time.tm_year++;
		} while (rtc_valid_tm(&alarm->time) != 0);
		break;

	default:
		dev_warn(&rtc->dev, "alarm rollover not handled\n");
	}

done:
	return 0;
}