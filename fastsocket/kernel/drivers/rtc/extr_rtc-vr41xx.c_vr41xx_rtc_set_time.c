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
struct rtc_time {int tm_mon; int tm_mday; int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; scalar_t__ tm_year; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ epoch ; 
 unsigned long mktime (scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_elapsed_second (unsigned long) ; 

__attribute__((used)) static int vr41xx_rtc_set_time(struct device *dev, struct rtc_time *time)
{
	unsigned long epoch_sec, current_sec;

	epoch_sec = mktime(epoch, 1, 1, 0, 0, 0);
	current_sec = mktime(time->tm_year + 1900, time->tm_mon + 1, time->tm_mday,
	                     time->tm_hour, time->tm_min, time->tm_sec);

	write_elapsed_second(current_sec - epoch_sec);

	return 0;
}