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
struct TYPE_2__ {int /*<<< orphan*/  function; } ;
struct maple_device {scalar_t__ interval; scalar_t__ when; int /*<<< orphan*/  busy; TYPE_1__ devinfo; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAPLE_COMMAND_DEVINFO ; 
 int /*<<< orphan*/  MAPLE_COMMAND_GETCOND ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int maple_add_packet (struct maple_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ maple_pnp_time ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 struct maple_device* to_maple_dev (struct device*) ; 

__attribute__((used)) static int setup_maple_commands(struct device *device, void *ignored)
{
	int add;
	struct maple_device *mdev = to_maple_dev(device);
	if (mdev->interval > 0 && atomic_read(&mdev->busy) == 0 &&
		time_after(jiffies, mdev->when)) {
		/* bounce if we cannot add */
		add = maple_add_packet(mdev,
			be32_to_cpu(mdev->devinfo.function),
			MAPLE_COMMAND_GETCOND, 1, NULL);
		if (!add)
			mdev->when = jiffies + mdev->interval;
	} else {
		if (time_after(jiffies, maple_pnp_time))
			/* Ensure we don't have block reads and devinfo
			* calls interfering with one another - so flag the
			* device as busy */
			if (atomic_read(&mdev->busy) == 0) {
				atomic_set(&mdev->busy, 1);
				maple_add_packet(mdev, 0,
					MAPLE_COMMAND_DEVINFO, 0, NULL);
			}
	}
	return 0;
}