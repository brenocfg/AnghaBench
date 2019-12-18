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
struct thermal_zone_device {int /*<<< orphan*/  poll_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  round_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void thermal_zone_device_set_polling(struct thermal_zone_device *tz,
					    int delay)
{
	cancel_delayed_work(&(tz->poll_queue));

	if (!delay)
		return;

	if (delay > 1000)
		schedule_delayed_work(&(tz->poll_queue),
				      round_jiffies(msecs_to_jiffies(delay)));
	else
		schedule_delayed_work(&(tz->poll_queue),
				      msecs_to_jiffies(delay));
}