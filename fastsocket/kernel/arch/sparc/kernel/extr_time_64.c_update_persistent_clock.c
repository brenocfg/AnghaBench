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
struct timespec {int /*<<< orphan*/  tv_sec; } ;
struct rtc_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtc_class_close (struct rtc_device*) ; 
 struct rtc_device* rtc_class_open (char*) ; 
 int rtc_set_mmss (struct rtc_device*,int /*<<< orphan*/ ) ; 

int update_persistent_clock(struct timespec now)
{
	struct rtc_device *rtc = rtc_class_open("rtc0");
	int err = -1;

	if (rtc) {
		err = rtc_set_mmss(rtc, now.tv_sec);
		rtc_class_close(rtc);
	}

	return err;
}