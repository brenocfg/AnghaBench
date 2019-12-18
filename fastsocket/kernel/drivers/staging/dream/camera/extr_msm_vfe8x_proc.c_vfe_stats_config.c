#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vfe_cmd_stats_setting {int /*<<< orphan*/ * awbBuffer; int /*<<< orphan*/ * afBuffer; } ;
struct TYPE_5__ {int /*<<< orphan*/  nextFrameAddrBuf; int /*<<< orphan*/ * addressBuffer; } ;
struct TYPE_4__ {int /*<<< orphan*/  nextFrameAddrBuf; int /*<<< orphan*/ * addressBuffer; } ;
struct TYPE_6__ {TYPE_2__ awbStatsControl; TYPE_1__ afStatsControl; } ;

/* Variables and functions */
 TYPE_3__* ctrl ; 
 int /*<<< orphan*/  vfe_stats_setting (struct vfe_cmd_stats_setting*) ; 

void vfe_stats_config(struct vfe_cmd_stats_setting *in)
{
	ctrl->afStatsControl.addressBuffer[0] = in->afBuffer[0];
	ctrl->afStatsControl.addressBuffer[1] = in->afBuffer[1];
	ctrl->afStatsControl.nextFrameAddrBuf = in->afBuffer[2];

	ctrl->awbStatsControl.addressBuffer[0] = in->awbBuffer[0];
	ctrl->awbStatsControl.addressBuffer[1] = in->awbBuffer[1];
	ctrl->awbStatsControl.nextFrameAddrBuf = in->awbBuffer[2];

	vfe_stats_setting(in);
}