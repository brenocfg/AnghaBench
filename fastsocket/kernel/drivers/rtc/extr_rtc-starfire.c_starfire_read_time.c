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
 int /*<<< orphan*/  rtc_time_to_tm (int /*<<< orphan*/ ,struct rtc_time*) ; 
 int rtc_valid_tm (struct rtc_time*) ; 
 int /*<<< orphan*/  starfire_get_time () ; 

__attribute__((used)) static int starfire_read_time(struct device *dev, struct rtc_time *tm)
{
	rtc_time_to_tm(starfire_get_time(), tm);
	return rtc_valid_tm(tm);
}