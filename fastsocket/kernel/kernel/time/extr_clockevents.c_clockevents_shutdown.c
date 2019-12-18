#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  tv64; } ;
struct clock_event_device {TYPE_1__ next_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_EVT_MODE_SHUTDOWN ; 
 int /*<<< orphan*/  KTIME_MAX ; 
 int /*<<< orphan*/  clockevents_set_mode (struct clock_event_device*,int /*<<< orphan*/ ) ; 

void clockevents_shutdown(struct clock_event_device *dev)
{
	clockevents_set_mode(dev, CLOCK_EVT_MODE_SHUTDOWN);
	dev->next_event.tv64 = KTIME_MAX;
}