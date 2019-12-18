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
 scalar_t__ HvLpConfig_getHostingLpIndex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HvLpConfig_getLpIndex () ; 
 scalar_t__ HvLpIndexInvalid ; 
 int /*<<< orphan*/  handleConfig ; 
 int /*<<< orphan*/  vio_setHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  viomajorsubtype_config ; 
 scalar_t__ viopath_hostLp ; 
 int /*<<< orphan*/  viopath_ourLp ; 

void vio_set_hostlp(void)
{
	/*
	 * If this has already been set then we DON'T want to either change
	 * it or re-register the proc file system
	 */
	if (viopath_hostLp != HvLpIndexInvalid)
		return;

	/*
	 * Figure out our hosting partition.  This isn't allowed to change
	 * while we're active
	 */
	viopath_ourLp = HvLpConfig_getLpIndex();
	viopath_hostLp = HvLpConfig_getHostingLpIndex(viopath_ourLp);

	if (viopath_hostLp != HvLpIndexInvalid)
		vio_setHandler(viomajorsubtype_config, handleConfig);
}