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
 int /*<<< orphan*/  S_RES_CAPTURE ; 
 int /*<<< orphan*/  S_UPDATE_PERIODIC ; 
 TYPE_1__* s5k3e2fx_ctrl ; 
 scalar_t__ s5k3e2fx_setting (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t s5k3e2fx_raw_snapshot_config(int mode)
{
	int32_t rc = 0;

	rc = s5k3e2fx_setting(S_UPDATE_PERIODIC, S_RES_CAPTURE);
	if (rc < 0)
		return rc;

	s5k3e2fx_ctrl->curr_res = s5k3e2fx_ctrl->pict_res;
	s5k3e2fx_ctrl->sensormode = mode;

	return rc;
}