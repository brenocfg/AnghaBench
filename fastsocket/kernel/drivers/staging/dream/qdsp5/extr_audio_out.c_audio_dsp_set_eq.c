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
struct TYPE_6__ {int /*<<< orphan*/  eq_params; int /*<<< orphan*/  num_bands; } ;
struct audio {TYPE_1__ eq; scalar_t__ eq_enable; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_7__ {int /*<<< orphan*/  command_type; int /*<<< orphan*/  comman_cfg; } ;
struct TYPE_8__ {int /*<<< orphan*/  eq_flag; int /*<<< orphan*/  eq_params; int /*<<< orphan*/  num_bands; TYPE_2__ common; } ;
typedef  TYPE_3__ audpp_cmd_cfg_object_params_eq ;

/* Variables and functions */
 int /*<<< orphan*/  AUDPP_CMD_CFG_OBJ_UPDATE ; 
 int /*<<< orphan*/  AUDPP_CMD_EQUALIZER ; 
 int /*<<< orphan*/  AUDPP_CMD_EQ_FLAG_DIS ; 
 int /*<<< orphan*/  AUDPP_CMD_EQ_FLAG_ENA ; 
 int audpp_send_queue3 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int audio_dsp_set_eq(struct audio *audio)
{
	audpp_cmd_cfg_object_params_eq cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.common.comman_cfg = AUDPP_CMD_CFG_OBJ_UPDATE;
	cmd.common.command_type = AUDPP_CMD_EQUALIZER;

	if (audio->eq_enable) {
		cmd.eq_flag = AUDPP_CMD_EQ_FLAG_ENA;
		cmd.num_bands = audio->eq.num_bands;
		memcpy(&cmd.eq_params, audio->eq.eq_params,
		       sizeof(audio->eq.eq_params));
	} else {
		cmd.eq_flag = AUDPP_CMD_EQ_FLAG_DIS;
	}
	return audpp_send_queue3(&cmd, sizeof(cmd));
}