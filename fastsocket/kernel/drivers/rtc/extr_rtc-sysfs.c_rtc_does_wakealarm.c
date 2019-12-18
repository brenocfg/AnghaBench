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
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct rtc_device {TYPE_2__* ops; TYPE_1__ dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * set_alarm; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_can_wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int rtc_does_wakealarm(struct rtc_device *rtc)
{
	if (!device_can_wakeup(rtc->dev.parent))
		return 0;
	return rtc->ops->set_alarm != NULL;
}