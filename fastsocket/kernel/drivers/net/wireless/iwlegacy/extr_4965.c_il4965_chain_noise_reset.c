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
struct il_chain_noise_data {scalar_t__ state; scalar_t__ beacon_count; scalar_t__ chain_signal_c; scalar_t__ chain_signal_b; scalar_t__ chain_signal_a; scalar_t__ chain_noise_c; scalar_t__ chain_noise_b; scalar_t__ chain_noise_a; } ;
struct il_priv {struct il_chain_noise_data chain_noise_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  op_code; } ;
struct il_calib_diff_gain_cmd {scalar_t__ diff_gain_c; scalar_t__ diff_gain_b; scalar_t__ diff_gain_a; TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  C_PHY_CALIBRATION ; 
 int /*<<< orphan*/  D_CALIB (char*) ; 
 scalar_t__ IL_CHAIN_NOISE_ACCUMULATE ; 
 scalar_t__ IL_CHAIN_NOISE_ALIVE ; 
 int /*<<< orphan*/  IL_ERR (char*) ; 
 int /*<<< orphan*/  IL_PHY_CALIBRATE_DIFF_GAIN_CMD ; 
 scalar_t__ il_is_any_associated (struct il_priv*) ; 
 scalar_t__ il_send_cmd_pdu (struct il_priv*,int /*<<< orphan*/ ,int,struct il_calib_diff_gain_cmd*) ; 
 int /*<<< orphan*/  memset (struct il_calib_diff_gain_cmd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
il4965_chain_noise_reset(struct il_priv *il)
{
	struct il_chain_noise_data *data = &(il->chain_noise_data);

	if (data->state == IL_CHAIN_NOISE_ALIVE && il_is_any_associated(il)) {
		struct il_calib_diff_gain_cmd cmd;

		/* clear data for chain noise calibration algorithm */
		data->chain_noise_a = 0;
		data->chain_noise_b = 0;
		data->chain_noise_c = 0;
		data->chain_signal_a = 0;
		data->chain_signal_b = 0;
		data->chain_signal_c = 0;
		data->beacon_count = 0;

		memset(&cmd, 0, sizeof(cmd));
		cmd.hdr.op_code = IL_PHY_CALIBRATE_DIFF_GAIN_CMD;
		cmd.diff_gain_a = 0;
		cmd.diff_gain_b = 0;
		cmd.diff_gain_c = 0;
		if (il_send_cmd_pdu(il, C_PHY_CALIBRATION, sizeof(cmd), &cmd))
			IL_ERR("Could not send C_PHY_CALIBRATION\n");
		data->state = IL_CHAIN_NOISE_ACCUMULATE;
		D_CALIB("Run chain_noise_calibrate\n");
	}
}