#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct wol_config {int dummy; } ;
struct lbs_private {scalar_t__ wol_criteria; int /*<<< orphan*/  wol_gap; int /*<<< orphan*/  wol_gpio; } ;
struct TYPE_4__ {int /*<<< orphan*/  action; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; } ;
struct cmd_ds_host_sleep {TYPE_2__ wol_conf; int /*<<< orphan*/  gap; int /*<<< orphan*/  gpio; int /*<<< orphan*/  criteria; TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  cmd_config ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_802_11_HOST_SLEEP_CFG ; 
 int /*<<< orphan*/  CMD_ACT_ACTION_NONE ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 int lbs_cmd_with_response (struct lbs_private*,int /*<<< orphan*/ ,struct cmd_ds_host_sleep*) ; 
 int /*<<< orphan*/  lbs_deb_cmd (char*,scalar_t__) ; 
 int /*<<< orphan*/  lbs_pr_info (char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int lbs_host_sleep_cfg(struct lbs_private *priv, uint32_t criteria,
		struct wol_config *p_wol_config)
{
	struct cmd_ds_host_sleep cmd_config;
	int ret;

	cmd_config.hdr.size = cpu_to_le16(sizeof(cmd_config));
	cmd_config.criteria = cpu_to_le32(criteria);
	cmd_config.gpio = priv->wol_gpio;
	cmd_config.gap = priv->wol_gap;

	if (p_wol_config != NULL)
		memcpy((uint8_t *)&cmd_config.wol_conf, (uint8_t *)p_wol_config,
				sizeof(struct wol_config));
	else
		cmd_config.wol_conf.action = CMD_ACT_ACTION_NONE;

	ret = lbs_cmd_with_response(priv, CMD_802_11_HOST_SLEEP_CFG, &cmd_config);
	if (!ret) {
		if (criteria) {
			lbs_deb_cmd("Set WOL criteria to %x\n", criteria);
			priv->wol_criteria = criteria;
		} else
			memcpy((uint8_t *) p_wol_config,
					(uint8_t *)&cmd_config.wol_conf,
					sizeof(struct wol_config));
	} else {
		lbs_pr_info("HOST_SLEEP_CFG failed %d\n", ret);
	}

	return ret;
}