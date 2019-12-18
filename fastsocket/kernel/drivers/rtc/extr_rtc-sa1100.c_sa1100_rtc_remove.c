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
struct rtc_device {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct rtc_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  rtc_device_unregister (struct rtc_device*) ; 

__attribute__((used)) static int sa1100_rtc_remove(struct platform_device *pdev)
{
	struct rtc_device *rtc = platform_get_drvdata(pdev);

 	if (rtc)
		rtc_device_unregister(rtc);

	return 0;
}