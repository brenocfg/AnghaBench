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
typedef  size_t u32 ;
struct dfs_pattern_detector {size_t num_radar_types; int /*<<< orphan*/  last_pulse_ts; } ;
struct channel_detector {TYPE_1__** detectors; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reset ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void channel_detector_reset(struct dfs_pattern_detector *dpd,
				   struct channel_detector *cd)
{
	u32 i;
	if (cd == NULL)
		return;
	for (i = 0; i < dpd->num_radar_types; i++)
		cd->detectors[i]->reset(cd->detectors[i], dpd->last_pulse_ts);
}