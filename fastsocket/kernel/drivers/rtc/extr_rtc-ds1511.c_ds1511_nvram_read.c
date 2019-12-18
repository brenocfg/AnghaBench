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
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct bin_attribute {int dummy; } ;
typedef  int ssize_t ;
typedef  size_t loff_t ;

/* Variables and functions */
 size_t DS1511_BME ; 
 int /*<<< orphan*/  DS1511_RAMADDR_LSB ; 
 int /*<<< orphan*/  DS1511_RAMDATA ; 
 size_t DS1511_RAM_MAX ; 
 int /*<<< orphan*/  RTC_CMD ; 
 size_t rtc_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_write (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
ds1511_nvram_read(struct file *filp, struct kobject *kobj,
		  struct bin_attribute *ba,
		  char *buf, loff_t pos, size_t size)
{
	ssize_t count;

	/*
	 * if count is more than one, turn on "burst" mode
	 * turn it off when you're done
	 */
	if (size > 1) {
		rtc_write((rtc_read(RTC_CMD) | DS1511_BME), RTC_CMD);
	}
	if (pos > DS1511_RAM_MAX) {
		pos = DS1511_RAM_MAX;
	}
	if (size + pos > DS1511_RAM_MAX + 1) {
		size = DS1511_RAM_MAX - pos + 1;
	}
	rtc_write(pos, DS1511_RAMADDR_LSB);
	for (count = 0; size > 0; count++, size--) {
		*buf++ = rtc_read(DS1511_RAMDATA);
	}
	if (count > 1) {
		rtc_write((rtc_read(RTC_CMD) & ~DS1511_BME), RTC_CMD);
	}
	return count;
}