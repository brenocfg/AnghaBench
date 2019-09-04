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

/* Variables and functions */
 int /*<<< orphan*/  throttle_info_update (void*,int) ; 

void throttle_info_update_by_mask(void *throttle_info_handle, int flags)
{
	void *throttle_info = throttle_info_handle;

	/*
	 * for now we only use the lowest bit of the throttle mask, so the
	 * handle is the same as the throttle_info.  Later if we store a
	 * set of throttle infos in the handle, we will want to loop through
	 * them and call throttle_info_update in a loop
	 */
	throttle_info_update(throttle_info, flags);
}