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
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_rtc_time (struct rtc_time*) ; 

__attribute__((used)) static int cmos_read_time(struct device *dev, struct rtc_time *t)
{
	/* REVISIT:  if the clock has a "century" register, use
	 * that instead of the heuristic in get_rtc_time().
	 * That'll make Y3K compatility (year > 2070) easy!
	 */
	get_rtc_time(t);
	return 0;
}