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
struct rtc_time {void* tm_year; void* tm_mon; void* tm_mday; void* tm_hour; void* tm_min; void* tm_sec; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (unsigned char*) ; 
 unsigned char RDAYCNT ; 
 unsigned char RHRCNT ; 
 unsigned char RMINCNT ; 
 unsigned char RMONCNT ; 
 unsigned char RSECCNT ; 
 unsigned char RYRCNT ; 
 void* bcd2bin (unsigned char) ; 
 int /*<<< orphan*/  memset (struct rtc_time*,int /*<<< orphan*/ ,int) ; 
 int read_regs (struct device*,unsigned char*,int /*<<< orphan*/ ) ; 
 int rtc_valid_tm (struct rtc_time*) ; 

__attribute__((used)) static int r9701_get_datetime(struct device *dev, struct rtc_time *dt)
{
	int ret;
	unsigned char buf[] = { RSECCNT, RMINCNT, RHRCNT,
				RDAYCNT, RMONCNT, RYRCNT };

	ret = read_regs(dev, buf, ARRAY_SIZE(buf));
	if (ret)
		return ret;

	memset(dt, 0, sizeof(*dt));

	dt->tm_sec = bcd2bin(buf[0]); /* RSECCNT */
	dt->tm_min = bcd2bin(buf[1]); /* RMINCNT */
	dt->tm_hour = bcd2bin(buf[2]); /* RHRCNT */

	dt->tm_mday = bcd2bin(buf[3]); /* RDAYCNT */
	dt->tm_mon = bcd2bin(buf[4]) - 1; /* RMONCNT */
	dt->tm_year = bcd2bin(buf[5]) + 100; /* RYRCNT */

	/* the rtc device may contain illegal values on power up
	 * according to the data sheet. make sure they are valid.
	 */

	return rtc_valid_tm(dt);
}