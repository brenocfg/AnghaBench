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
 unsigned char mca_device_read_stored_pos (struct mca_device*,int) ; 
 struct mca_device* mca_find_device_by_slot (int) ; 

unsigned char mca_read_stored_pos(int slot, int reg)
{
	struct mca_device *mca_dev = mca_find_device_by_slot(slot);

	if(!mca_dev)
		return 0;

	return mca_device_read_stored_pos(mca_dev, reg);
}