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
struct maple_device {scalar_t__ unit; size_t port; int /*<<< orphan*/  busy; int /*<<< orphan*/  dev; int /*<<< orphan*/  maple_wait; int /*<<< orphan*/  (* can_unload ) (struct maple_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int* checked ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,size_t,...) ; 
 int* empty ; 
 int /*<<< orphan*/  fullscan ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  maple_clean_submap (struct maple_device*) ; 
 int /*<<< orphan*/  maple_detach_driver (struct maple_device*) ; 
 int /*<<< orphan*/  started ; 
 int /*<<< orphan*/  stub1 (struct maple_device*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void maple_response_none(struct maple_device *mdev)
{
	maple_clean_submap(mdev);

	if (likely(mdev->unit != 0)) {
		/*
		* Block devices play up
		* and give the impression they have
		* been removed even when still in place or
		* trip the mtd layer when they have
		* really gone - this code traps that eventuality
		* and ensures we aren't overloaded with useless
		* error messages
		*/
		if (mdev->can_unload) {
			if (!mdev->can_unload(mdev)) {
				atomic_set(&mdev->busy, 2);
				wake_up(&mdev->maple_wait);
				return;
			}
		}

		dev_info(&mdev->dev, "detaching device at (%d, %d)\n",
			mdev->port, mdev->unit);
		maple_detach_driver(mdev);
		return;
	} else {
		if (!started || !fullscan) {
			if (checked[mdev->port] == false) {
				checked[mdev->port] = true;
				empty[mdev->port] = true;
				dev_info(&mdev->dev, "no devices"
					" to port %d\n", mdev->port);
			}
			return;
		}
	}
	/* Some hardware devices generate false detach messages on unit 0 */
	atomic_set(&mdev->busy, 0);
}