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
struct smu_simple_cmd {int /*<<< orphan*/ * buffer; } ;
struct rtc_time {void* tm_year; void* tm_mon; void* tm_mday; void* tm_wday; void* tm_hour; void* tm_min; void* tm_sec; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  SMU_CMD_RTC_COMMAND ; 
 int /*<<< orphan*/  SMU_CMD_RTC_GET_DATETIME ; 
 void* bcd2hex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct rtc_time*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * smu ; 
 int smu_queue_simple (struct smu_simple_cmd*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smu_spinwait_simple (struct smu_simple_cmd*) ; 

int smu_get_rtc_time(struct rtc_time *time, int spinwait)
{
	struct smu_simple_cmd cmd;
	int rc;

	if (smu == NULL)
		return -ENODEV;

	memset(time, 0, sizeof(struct rtc_time));
	rc = smu_queue_simple(&cmd, SMU_CMD_RTC_COMMAND, 1, NULL, NULL,
			      SMU_CMD_RTC_GET_DATETIME);
	if (rc)
		return rc;
	smu_spinwait_simple(&cmd);

	time->tm_sec = bcd2hex(cmd.buffer[0]);
	time->tm_min = bcd2hex(cmd.buffer[1]);
	time->tm_hour = bcd2hex(cmd.buffer[2]);
	time->tm_wday = bcd2hex(cmd.buffer[3]);
	time->tm_mday = bcd2hex(cmd.buffer[4]);
	time->tm_mon = bcd2hex(cmd.buffer[5]) - 1;
	time->tm_year = bcd2hex(cmd.buffer[6]) + 100;

	return 0;
}