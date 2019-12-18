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
struct notifier_block {int dummy; } ;
struct in_ifaddr {struct in_device* ifa_dev; } ;
struct in_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_CHANGE ; 
 unsigned long NETDEV_UP ; 
 int NOTIFY_DONE ; 
 int clip_device_event (struct notifier_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clip_inet_event(struct notifier_block *this, unsigned long event,
			   void *ifa)
{
	struct in_device *in_dev;

	in_dev = ((struct in_ifaddr *)ifa)->ifa_dev;
	/*
	 * Transitions are of the down-change-up type, so it's sufficient to
	 * handle the change on up.
	 */
	if (event != NETDEV_UP)
		return NOTIFY_DONE;
	return clip_device_event(this, NETDEV_CHANGE, in_dev->dev);
}