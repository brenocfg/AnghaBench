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
struct iwl_priv {TYPE_1__* nvm_data; } ;
struct iwl_calib_temperature_offset_cmd {scalar_t__ radio_sensor_offset; int /*<<< orphan*/  hdr; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_2__ {scalar_t__ raw_temperature; } ;

/* Variables and functions */
 scalar_t__ DEFAULT_RADIO_SENSOR_OFFSET ; 
 int /*<<< orphan*/  IWL_DEBUG_CALIB (struct iwl_priv*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_PHY_CALIBRATE_TEMP_OFFSET_CMD ; 
 int iwl_calib_set (struct iwl_priv*,void*,int) ; 
 int /*<<< orphan*/  iwl_set_calib_hdr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct iwl_calib_temperature_offset_cmd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int iwl_set_temperature_offset_calib(struct iwl_priv *priv)
{
	struct iwl_calib_temperature_offset_cmd cmd;

	memset(&cmd, 0, sizeof(cmd));
	iwl_set_calib_hdr(&cmd.hdr, IWL_PHY_CALIBRATE_TEMP_OFFSET_CMD);
	cmd.radio_sensor_offset = priv->nvm_data->raw_temperature;
	if (!(cmd.radio_sensor_offset))
		cmd.radio_sensor_offset = DEFAULT_RADIO_SENSOR_OFFSET;

	IWL_DEBUG_CALIB(priv, "Radio sensor offset: %d\n",
			le16_to_cpu(cmd.radio_sensor_offset));
	return iwl_calib_set(priv, (void *)&cmd, sizeof(cmd));
}