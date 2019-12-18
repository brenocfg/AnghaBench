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
struct xtm {int weekday; int monthday; } ;
struct xt_time_info {int flags; scalar_t__ date_start; scalar_t__ date_stop; unsigned int daytime_start; unsigned int daytime_stop; int weekdays_match; int monthdays_match; } ;
struct xt_match_param {struct xt_time_info* matchinfo; } ;
struct TYPE_4__ {scalar_t__ tv64; } ;
struct sk_buff {TYPE_2__ tstamp; } ;
typedef  scalar_t__ s64 ;
struct TYPE_3__ {int tz_minuteswest; } ;

/* Variables and functions */
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 int XT_TIME_ALL_MONTHDAYS ; 
 int XT_TIME_LOCAL_TZ ; 
 int /*<<< orphan*/  __net_timestamp (struct sk_buff*) ; 
 scalar_t__ div_s64 (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_to_ns (TYPE_2__) ; 
 unsigned int localtime_1 (struct xtm*,scalar_t__) ; 
 int /*<<< orphan*/  localtime_2 (struct xtm*,scalar_t__) ; 
 int /*<<< orphan*/  localtime_3 (struct xtm*,scalar_t__) ; 
 TYPE_1__ sys_tz ; 

__attribute__((used)) static bool
time_mt(const struct sk_buff *skb, const struct xt_match_param *par)
{
	const struct xt_time_info *info = par->matchinfo;
	unsigned int packet_time;
	struct xtm current_time;
	s64 stamp;

	/*
	 * We cannot use get_seconds() instead of __net_timestamp() here.
	 * Suppose you have two rules:
	 * 	1. match before 13:00
	 * 	2. match after 13:00
	 * If you match against processing time (get_seconds) it
	 * may happen that the same packet matches both rules if
	 * it arrived at the right moment before 13:00.
	 */
	if (skb->tstamp.tv64 == 0)
		__net_timestamp((struct sk_buff *)skb);

	stamp = ktime_to_ns(skb->tstamp);
	stamp = div_s64(stamp, NSEC_PER_SEC);

	if (info->flags & XT_TIME_LOCAL_TZ)
		/* Adjust for local timezone */
		stamp -= 60 * sys_tz.tz_minuteswest;

	/*
	 * xt_time will match when _all_ of the following hold:
	 *   - 'now' is in the global time range date_start..date_end
	 *   - 'now' is in the monthday mask
	 *   - 'now' is in the weekday mask
	 *   - 'now' is in the daytime range time_start..time_end
	 * (and by default, libxt_time will set these so as to match)
	 */

	if (stamp < info->date_start || stamp > info->date_stop)
		return false;

	packet_time = localtime_1(&current_time, stamp);

	if (info->daytime_start < info->daytime_stop) {
		if (packet_time < info->daytime_start ||
		    packet_time > info->daytime_stop)
			return false;
	} else {
		if (packet_time < info->daytime_start &&
		    packet_time > info->daytime_stop)
			return false;
	}

	localtime_2(&current_time, stamp);

	if (!(info->weekdays_match & (1 << current_time.weekday)))
		return false;

	/* Do not spend time computing monthday if all days match anyway */
	if (info->monthdays_match != XT_TIME_ALL_MONTHDAYS) {
		localtime_3(&current_time, stamp);
		if (!(info->monthdays_match & (1 << current_time.monthday)))
			return false;
	}

	return true;
}