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
 int /*<<< orphan*/  mca_device_set_name (struct mca_device*,char*) ; 
 struct mca_device* mca_find_device_by_slot (int) ; 

void mca_set_adapter_name(int slot, char* name)
{
	struct mca_device *mca_dev = mca_find_device_by_slot(slot);

	if(!mca_dev)
		return;

	mca_device_set_name(mca_dev, name);
}