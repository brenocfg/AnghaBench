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
typedef  scalar_t__ u8 ;
struct lbs_private {scalar_t__ cur_rate; } ;
struct TYPE_2__ {void* size; } ;
struct cmd_ds_802_11_data_rate {scalar_t__* rates; void* action; TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_802_11_DATA_RATE ; 
 int CMD_ACT_SET_TX_AUTO ; 
 int CMD_ACT_SET_TX_FIX_RATE ; 
 int /*<<< orphan*/  LBS_DEB_CMD ; 
 void* cpu_to_le16 (int) ; 
 int lbs_cmd_with_response (struct lbs_private*,int /*<<< orphan*/ ,struct cmd_ds_802_11_data_rate*) ; 
 scalar_t__ lbs_data_rate_to_fw_index (scalar_t__) ; 
 int /*<<< orphan*/  lbs_deb_cmd (char*,...) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_hex (int /*<<< orphan*/ ,char*,scalar_t__*,int) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ lbs_fw_index_to_data_rate (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct cmd_ds_802_11_data_rate*,int /*<<< orphan*/ ,int) ; 

int lbs_set_data_rate(struct lbs_private *priv, u8 rate)
{
	struct cmd_ds_802_11_data_rate cmd;
	int ret = 0;

	lbs_deb_enter(LBS_DEB_CMD);

	memset(&cmd, 0, sizeof(cmd));
	cmd.hdr.size = cpu_to_le16(sizeof(cmd));

	if (rate > 0) {
		cmd.action = cpu_to_le16(CMD_ACT_SET_TX_FIX_RATE);
		cmd.rates[0] = lbs_data_rate_to_fw_index(rate);
		if (cmd.rates[0] == 0) {
			lbs_deb_cmd("DATA_RATE: invalid requested rate of"
			            " 0x%02X\n", rate);
			ret = 0;
			goto out;
		}
		lbs_deb_cmd("DATA_RATE: set fixed 0x%02X\n", cmd.rates[0]);
	} else {
		cmd.action = cpu_to_le16(CMD_ACT_SET_TX_AUTO);
		lbs_deb_cmd("DATA_RATE: setting auto\n");
	}

	ret = lbs_cmd_with_response(priv, CMD_802_11_DATA_RATE, &cmd);
	if (ret)
		goto out;

	lbs_deb_hex(LBS_DEB_CMD, "DATA_RATE_RESP", (u8 *) &cmd, sizeof (cmd));

	/* FIXME: get actual rates FW can do if this command actually returns
	 * all data rates supported.
	 */
	priv->cur_rate = lbs_fw_index_to_data_rate(cmd.rates[0]);
	lbs_deb_cmd("DATA_RATE: current rate is 0x%02x\n", priv->cur_rate);

out:
	lbs_deb_leave_args(LBS_DEB_CMD, "ret %d", ret);
	return ret;
}