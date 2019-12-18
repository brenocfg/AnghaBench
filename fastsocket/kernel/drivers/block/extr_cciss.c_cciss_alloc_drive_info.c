#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int raid_level; } ;
typedef  TYPE_1__ drive_info_struct ;
struct TYPE_6__ {int highest_lun; TYPE_1__** drv; } ;
typedef  TYPE_2__ ctlr_info_t ;

/* Variables and functions */
 int CISS_MAX_LUN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cciss_alloc_drive_info(ctlr_info_t *h, int controller_node)
{
	int i;
	drive_info_struct *drv;

	/* Search for an empty slot for our drive info */
	for (i = 0; i < CISS_MAX_LUN; i++) {

		/* if not cxd0 case, and it's occupied, skip it. */
		if (h->drv[i] && i != 0)
			continue;
		/*
		 * If it's cxd0 case, and drv is alloc'ed already, and a
		 * disk is configured there, skip it.
		 */
		if (i == 0 && h->drv[i] && h->drv[i]->raid_level != -1)
			continue;

		/*
		 * We've found an empty slot.  Update highest_lun
		 * provided this isn't just the fake cxd0 controller node.
		 */
		if (i > h->highest_lun && !controller_node)
			h->highest_lun = i;

		/* If adding a real disk at cxd0, and it's already alloc'ed */
		if (i == 0 && h->drv[i] != NULL)
			return i;

		/*
		 * Found an empty slot, not already alloc'ed.  Allocate it.
		 * Mark it with raid_level == -1, so we know it's new later on.
		 */
		drv = kzalloc(sizeof(*drv), GFP_KERNEL);
		if (!drv)
			return -1;
		drv->raid_level = -1; /* so we know it's new */
		h->drv[i] = drv;
		return i;
	}
	return -1;
}