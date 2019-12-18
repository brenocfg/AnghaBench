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
struct device {int dummy; } ;

/* Variables and functions */
 int ENOIOCTLCMD ; 
#define  RTC_AIE_OFF 133 
#define  RTC_AIE_ON 132 
#define  RTC_PIE_OFF 131 
#define  RTC_PIE_ON 130 
#define  RTC_UIE_OFF 129 
#define  RTC_UIE_ON 128 

__attribute__((used)) static int test_rtc_ioctl(struct device *dev, unsigned int cmd,
	unsigned long arg)
{
	/* We do support interrupts, they're generated
	 * using the sysfs interface.
	 */
	switch (cmd) {
	case RTC_PIE_ON:
	case RTC_PIE_OFF:
	case RTC_UIE_ON:
	case RTC_UIE_OFF:
	case RTC_AIE_ON:
	case RTC_AIE_OFF:
		return 0;

	default:
		return -ENOIOCTLCMD;
	}
}