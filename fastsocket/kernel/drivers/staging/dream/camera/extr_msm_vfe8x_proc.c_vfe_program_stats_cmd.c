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
struct vfe_stats_cmd_data {int /*<<< orphan*/  colorConversionEnable; int /*<<< orphan*/  histAutoClearEnable; int /*<<< orphan*/  clearHistEnable; int /*<<< orphan*/  histEnable; int /*<<< orphan*/  axwEnable; int /*<<< orphan*/  autoFocusEnable; } ;
struct VFE_StatsCmdType {int /*<<< orphan*/  colorConversionEnable; int /*<<< orphan*/  histAutoClearEnable; int /*<<< orphan*/  clearHistEnable; int /*<<< orphan*/  histEnable; int /*<<< orphan*/  axwEnable; int /*<<< orphan*/  autoFocusEnable; } ;
typedef  int /*<<< orphan*/  stats ;
struct TYPE_2__ {scalar_t__ vfebase; } ;

/* Variables and functions */
 scalar_t__ VFE_STATS_CMD ; 
 TYPE_1__* ctrl ; 
 int /*<<< orphan*/  memset (struct VFE_StatsCmdType*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void vfe_program_stats_cmd(struct vfe_stats_cmd_data *in)
{
	struct VFE_StatsCmdType stats;
	memset(&stats, 0, sizeof(stats));

	stats.autoFocusEnable        = in->autoFocusEnable;
	stats.axwEnable              = in->axwEnable;
	stats.histEnable             = in->histEnable;
	stats.clearHistEnable        = in->clearHistEnable;
	stats.histAutoClearEnable    = in->histAutoClearEnable;
	stats.colorConversionEnable  = in->colorConversionEnable;

	writel(*((uint32_t *)&stats), ctrl->vfebase + VFE_STATS_CMD);
}