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
struct mca_find_device_by_slot_info {scalar_t__ slot; struct mca_device* mca_dev; } ;
struct mca_device {scalar_t__ slot; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct mca_device* to_mca_device (struct device*) ; 

__attribute__((used)) static int mca_find_device_by_slot_callback(struct device *dev, void *data)
{
	struct mca_find_device_by_slot_info *info = data;
	struct mca_device *mca_dev = to_mca_device(dev);

	if(mca_dev->slot == info->slot)
		info->mca_dev = mca_dev;

	return 0;
}