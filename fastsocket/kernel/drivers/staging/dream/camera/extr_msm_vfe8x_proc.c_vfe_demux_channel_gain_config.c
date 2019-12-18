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
struct vfe_demux_cfg {int /*<<< orphan*/  ch2Gain; int /*<<< orphan*/  ch1Gain; int /*<<< orphan*/  ch0OddGain; int /*<<< orphan*/  ch0EvenGain; } ;
struct vfe_cmd_demux_channel_gain_config {int /*<<< orphan*/  ch2Gain; int /*<<< orphan*/  ch1Gain; int /*<<< orphan*/  ch0OddGain; int /*<<< orphan*/  ch0EvenGain; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_2__ {scalar_t__ vfebase; } ;

/* Variables and functions */
 scalar_t__ VFE_DEMUX_GAIN_0 ; 
 TYPE_1__* ctrl ; 
 int /*<<< orphan*/  memset (struct vfe_demux_cfg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfe_prog_hw (scalar_t__,int /*<<< orphan*/ *,int) ; 

void vfe_demux_channel_gain_config(
	struct vfe_cmd_demux_channel_gain_config *in)
{
	struct vfe_demux_cfg cmd;

	memset(&cmd, 0, sizeof(cmd));

	cmd.ch0EvenGain = in->ch0EvenGain;
	cmd.ch0OddGain  = in->ch0OddGain;
	cmd.ch1Gain     = in->ch1Gain;
	cmd.ch2Gain     = in->ch2Gain;

	vfe_prog_hw(ctrl->vfebase + VFE_DEMUX_GAIN_0,
		(uint32_t *)&cmd, sizeof(cmd));
}