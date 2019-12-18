#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u8 ;
struct wl12xx_vif {scalar_t__ band; } ;
struct wl12xx_cmd_roc {int /*<<< orphan*/  band; scalar_t__ channel; scalar_t__ role_id; } ;
struct wl1271 {int dummy; } ;
typedef  enum ieee80211_band { ____Placeholder_ieee80211_band } ieee80211_band ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_REMAIN_ON_CHANNEL ; 
 int /*<<< orphan*/  DEBUG_CMD ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  IEEE80211_BAND_2GHZ 129 
#define  IEEE80211_BAND_5GHZ 128 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ WL12XX_INVALID_ROLE_ID ; 
 int /*<<< orphan*/  WLCORE_BAND_2_4GHZ ; 
 int /*<<< orphan*/  WLCORE_BAND_5GHZ ; 
 int /*<<< orphan*/  kfree (struct wl12xx_cmd_roc*) ; 
 struct wl12xx_cmd_roc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_send (struct wl1271*,int /*<<< orphan*/ ,struct wl12xx_cmd_roc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wl1271_error (char*,...) ; 

__attribute__((used)) static int wl12xx_cmd_roc(struct wl1271 *wl, struct wl12xx_vif *wlvif,
			  u8 role_id, enum ieee80211_band band, u8 channel)
{
	struct wl12xx_cmd_roc *cmd;
	int ret = 0;

	wl1271_debug(DEBUG_CMD, "cmd roc %d (%d)", channel, role_id);

	if (WARN_ON(role_id == WL12XX_INVALID_ROLE_ID))
		return -EINVAL;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd) {
		ret = -ENOMEM;
		goto out;
	}

	cmd->role_id = role_id;
	cmd->channel = channel;
	switch (band) {
	case IEEE80211_BAND_2GHZ:
		cmd->band = WLCORE_BAND_2_4GHZ;
		break;
	case IEEE80211_BAND_5GHZ:
		cmd->band = WLCORE_BAND_5GHZ;
		break;
	default:
		wl1271_error("roc - unknown band: %d", (int)wlvif->band);
		ret = -EINVAL;
		goto out_free;
	}


	ret = wl1271_cmd_send(wl, CMD_REMAIN_ON_CHANNEL, cmd, sizeof(*cmd), 0);
	if (ret < 0) {
		wl1271_error("failed to send ROC command");
		goto out_free;
	}

out_free:
	kfree(cmd);

out:
	return ret;
}