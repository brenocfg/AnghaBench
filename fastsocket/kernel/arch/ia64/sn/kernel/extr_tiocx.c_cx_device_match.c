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
struct cx_device_id {scalar_t__ part_num; scalar_t__ mfg_num; } ;
struct TYPE_2__ {scalar_t__ part_num; scalar_t__ mfg_num; } ;
struct cx_dev {TYPE_1__ cx_id; } ;

/* Variables and functions */

__attribute__((used)) static const struct cx_device_id *cx_device_match(const struct cx_device_id
						  *ids,
						  struct cx_dev *cx_device)
{
	/*
	 * NOTES: We may want to check for CX_ANY_ID too.
	 *        Do we want to match against nasid too?
	 *        CX_DEV_NONE == 0, if the driver tries to register for
	 *        part/mfg == 0 we should return no-match (NULL) here.
	 */
	while (ids->part_num && ids->mfg_num) {
		if (ids->part_num == cx_device->cx_id.part_num &&
		    ids->mfg_num == cx_device->cx_id.mfg_num)
			return ids;
		ids++;
	}

	return NULL;
}