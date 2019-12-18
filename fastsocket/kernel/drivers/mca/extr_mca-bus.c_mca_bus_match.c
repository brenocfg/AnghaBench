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
struct mca_driver {unsigned short* id_table; unsigned short const integrated_id; } ;
struct mca_device {unsigned short const pos_id; int index; } ;
struct device_driver {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct mca_device* to_mca_device (struct device*) ; 
 struct mca_driver* to_mca_driver (struct device_driver*) ; 

__attribute__((used)) static int mca_bus_match (struct device *dev, struct device_driver *drv)
{
	struct mca_device *mca_dev = to_mca_device (dev);
	struct mca_driver *mca_drv = to_mca_driver (drv);
	const unsigned short *mca_ids = mca_drv->id_table;
	int i = 0;

	if (mca_ids) {
		for(i = 0; mca_ids[i]; i++) {
			if (mca_ids[i] == mca_dev->pos_id) {
				mca_dev->index = i;
				return 1;
			}
		}
	}
	/* If the integrated id is present, treat it as though it were an
	 * additional id in the id_table (it can't be because by definition,
	 * integrated id's overflow a short */
	if (mca_drv->integrated_id && mca_dev->pos_id ==
	    mca_drv->integrated_id) {
		mca_dev->index = i;
		return 1;
	}
	return 0;
}