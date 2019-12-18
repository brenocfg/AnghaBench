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
struct net_device {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __LINK_STATE_LINKWATCH_PENDING ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  linkwatch_add_event (struct net_device*) ; 
 int /*<<< orphan*/  linkwatch_schedule_work (int) ; 
 int linkwatch_urgent_event (struct net_device*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void linkwatch_fire_event(struct net_device *dev)
{
	bool urgent = linkwatch_urgent_event(dev);

	if (!test_and_set_bit(__LINK_STATE_LINKWATCH_PENDING, &dev->state)) {
		dev_hold(dev);

		linkwatch_add_event(dev);
	} else if (!urgent)
		return;

	linkwatch_schedule_work(urgent);
}