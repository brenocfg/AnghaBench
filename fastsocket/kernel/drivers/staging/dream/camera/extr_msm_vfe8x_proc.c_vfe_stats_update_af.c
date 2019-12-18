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
typedef  int /*<<< orphan*/  uint32_t ;
struct vfe_statsaf_update {int /*<<< orphan*/  windowWidth; int /*<<< orphan*/  windowHeight; int /*<<< orphan*/  windowMode; int /*<<< orphan*/  windowHOffset; int /*<<< orphan*/  windowVOffset; } ;
struct vfe_cmd_stats_af_update {int /*<<< orphan*/  windowWidth; int /*<<< orphan*/  windowHeight; int /*<<< orphan*/  windowMode; int /*<<< orphan*/  windowHOffset; int /*<<< orphan*/  windowVOffset; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_2__ {scalar_t__ vfebase; } ;

/* Variables and functions */
 scalar_t__ VFE_STATS_AF_CFG ; 
 TYPE_1__* ctrl ; 
 int /*<<< orphan*/  memset (struct vfe_statsaf_update*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfe_prog_hw (scalar_t__,int /*<<< orphan*/ *,int) ; 

void vfe_stats_update_af(struct vfe_cmd_stats_af_update *in)
{
	struct vfe_statsaf_update cmd;
	memset(&cmd, 0, sizeof(cmd));

	cmd.windowVOffset = in->windowVOffset;
	cmd.windowHOffset = in->windowHOffset;
	cmd.windowMode    = in->windowMode;
	cmd.windowHeight  = in->windowHeight;
	cmd.windowWidth   = in->windowWidth;

	vfe_prog_hw(ctrl->vfebase + VFE_STATS_AF_CFG,
		(uint32_t *)&cmd, sizeof(cmd));
}