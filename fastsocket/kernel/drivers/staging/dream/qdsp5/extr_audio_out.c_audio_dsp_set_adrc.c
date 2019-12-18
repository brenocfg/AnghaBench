#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  adrc_system_delay; int /*<<< orphan*/  release_const_msw; int /*<<< orphan*/  release_const_lsw; int /*<<< orphan*/  attack_const_msw; int /*<<< orphan*/  attack_const_lsw; int /*<<< orphan*/  rms_time; int /*<<< orphan*/  compression_slope; int /*<<< orphan*/  compression_th; } ;
struct audio {TYPE_2__ adrc; scalar_t__ adrc_enable; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_6__ {int /*<<< orphan*/  command_type; int /*<<< orphan*/  comman_cfg; } ;
struct TYPE_8__ {int /*<<< orphan*/  adrc_flag; int /*<<< orphan*/  adrc_system_delay; int /*<<< orphan*/  release_const_msw; int /*<<< orphan*/  release_const_lsw; int /*<<< orphan*/  attack_const_msw; int /*<<< orphan*/  attack_const_lsw; int /*<<< orphan*/  rms_time; int /*<<< orphan*/  compression_slope; int /*<<< orphan*/  compression_th; TYPE_1__ common; } ;
typedef  TYPE_3__ audpp_cmd_cfg_object_params_adrc ;

/* Variables and functions */
 int /*<<< orphan*/  AUDPP_CMD_ADRC ; 
 int /*<<< orphan*/  AUDPP_CMD_ADRC_FLAG_DIS ; 
 int /*<<< orphan*/  AUDPP_CMD_ADRC_FLAG_ENA ; 
 int /*<<< orphan*/  AUDPP_CMD_CFG_OBJ_UPDATE ; 
 int audpp_send_queue3 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int audio_dsp_set_adrc(struct audio *audio)
{
	audpp_cmd_cfg_object_params_adrc cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.common.comman_cfg = AUDPP_CMD_CFG_OBJ_UPDATE;
	cmd.common.command_type = AUDPP_CMD_ADRC;

	if (audio->adrc_enable) {
		cmd.adrc_flag = AUDPP_CMD_ADRC_FLAG_ENA;
		cmd.compression_th = audio->adrc.compression_th;
		cmd.compression_slope = audio->adrc.compression_slope;
		cmd.rms_time = audio->adrc.rms_time;
		cmd.attack_const_lsw = audio->adrc.attack_const_lsw;
		cmd.attack_const_msw = audio->adrc.attack_const_msw;
		cmd.release_const_lsw = audio->adrc.release_const_lsw;
		cmd.release_const_msw = audio->adrc.release_const_msw;
		cmd.adrc_system_delay = audio->adrc.adrc_system_delay;
	} else {
		cmd.adrc_flag = AUDPP_CMD_ADRC_FLAG_DIS;
	}
	return audpp_send_queue3(&cmd, sizeof(cmd));
}