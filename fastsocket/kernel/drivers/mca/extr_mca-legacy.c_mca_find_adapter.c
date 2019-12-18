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
struct mca_find_adapter_info {int slot; int id; TYPE_1__* mca_dev; } ;
struct TYPE_2__ {scalar_t__ status; int slot; } ;

/* Variables and functions */
 scalar_t__ MCA_ADAPTER_DISABLED ; 
 int MCA_NOTFOUND ; 
 int /*<<< orphan*/  bus_for_each_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct mca_find_adapter_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mca_bus_type ; 
 int /*<<< orphan*/  mca_find_adapter_callback ; 

int mca_find_adapter(int id, int start)
{
	struct mca_find_adapter_info info;

	if(id == 0xffff)
		return MCA_NOTFOUND;

	info.slot = start;
	info.id = id;
	info.mca_dev = NULL;

	for(;;) {
		bus_for_each_dev(&mca_bus_type, NULL, &info, mca_find_adapter_callback);

		if(info.mca_dev == NULL)
			return MCA_NOTFOUND;

		if(info.mca_dev->status != MCA_ADAPTER_DISABLED)
			break;

		/* OK, found adapter but it was disabled.  Go around
		 * again, excluding the slot we just found */

		info.slot = info.mca_dev->slot + 1;
		info.mca_dev = NULL;
	}
		
	return info.mca_dev->slot;
}