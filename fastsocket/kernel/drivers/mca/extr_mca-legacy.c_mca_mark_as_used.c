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
struct mca_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ mca_device_claimed (struct mca_device*) ; 
 int /*<<< orphan*/  mca_device_set_claim (struct mca_device*,int) ; 
 struct mca_device* mca_find_device_by_slot (int) ; 

int mca_mark_as_used(int slot)
{
	struct mca_device *mca_dev = mca_find_device_by_slot(slot);

	if(!mca_dev)
		/* FIXME: this is actually a severe error */
		return 1;

	if(mca_device_claimed(mca_dev))
		return 1;

	mca_device_set_claim(mca_dev, 1);

	return 0;
}