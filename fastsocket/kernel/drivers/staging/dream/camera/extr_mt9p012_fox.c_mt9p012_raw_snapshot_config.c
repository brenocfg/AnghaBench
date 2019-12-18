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
typedef  scalar_t__ int32_t ;
struct TYPE_2__ {int sensormode; int /*<<< orphan*/  pict_res; int /*<<< orphan*/  curr_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  RES_CAPTURE ; 
 int /*<<< orphan*/  UPDATE_PERIODIC ; 
 TYPE_1__* mt9p012_ctrl ; 
 scalar_t__ mt9p012_setting (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t mt9p012_raw_snapshot_config(int mode)
{
	int32_t rc = 0;

	rc = mt9p012_setting(UPDATE_PERIODIC, RES_CAPTURE);
	if (rc < 0)
		return rc;

	mt9p012_ctrl->curr_res = mt9p012_ctrl->pict_res;

	mt9p012_ctrl->sensormode = mode;

	return rc;
}