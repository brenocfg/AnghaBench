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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct lbs_private {int dummy; } ;
struct TYPE_2__ {void* size; } ;
struct cmd_ds_802_11_deauthenticate {void* reasoncode; int /*<<< orphan*/  macaddr; TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_802_11_DEAUTHENTICATE ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  LBS_DEB_JOIN ; 
 void* cpu_to_le16 (int) ; 
 int lbs_cmd_with_response (struct lbs_private*,int /*<<< orphan*/ ,struct cmd_ds_802_11_deauthenticate*) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_mac_event_disconnected (struct lbs_private*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct cmd_ds_802_11_deauthenticate*,int /*<<< orphan*/ ,int) ; 

int lbs_cmd_80211_deauthenticate(struct lbs_private *priv, u8 bssid[ETH_ALEN],
				 u16 reason)
{
	struct cmd_ds_802_11_deauthenticate cmd;
	int ret;

	lbs_deb_enter(LBS_DEB_JOIN);

	memset(&cmd, 0, sizeof(cmd));
	cmd.hdr.size = cpu_to_le16(sizeof(cmd));
	memcpy(cmd.macaddr, &bssid[0], ETH_ALEN);
	cmd.reasoncode = cpu_to_le16(reason);

	ret = lbs_cmd_with_response(priv, CMD_802_11_DEAUTHENTICATE, &cmd);

	/* Clean up everything even if there was an error; can't assume that
	 * we're still authenticated to the AP after trying to deauth.
	 */
	lbs_mac_event_disconnected(priv);

	lbs_deb_leave(LBS_DEB_JOIN);
	return ret;
}