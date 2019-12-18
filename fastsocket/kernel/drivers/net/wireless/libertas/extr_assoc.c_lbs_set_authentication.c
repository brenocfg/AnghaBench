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
struct lbs_private {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;
struct cmd_ds_802_11_authenticate {int /*<<< orphan*/  authtype; int /*<<< orphan*/  bssid; TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_802_11_AUTHENTICATE ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  LBS_DEB_JOIN ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  iw_auth_to_ieee_auth (int /*<<< orphan*/ ) ; 
 int lbs_cmd_with_response (struct lbs_private*,int /*<<< orphan*/ ,struct cmd_ds_802_11_authenticate*) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_join (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lbs_set_authentication(struct lbs_private *priv, u8 bssid[6], u8 auth)
{
	struct cmd_ds_802_11_authenticate cmd;
	int ret = -1;

	lbs_deb_enter(LBS_DEB_JOIN);

	cmd.hdr.size = cpu_to_le16(sizeof(cmd));
	memcpy(cmd.bssid, bssid, ETH_ALEN);

	cmd.authtype = iw_auth_to_ieee_auth(auth);

	lbs_deb_join("AUTH_CMD: BSSID %pM, auth 0x%x\n", bssid, cmd.authtype);

	ret = lbs_cmd_with_response(priv, CMD_802_11_AUTHENTICATE, &cmd);

	lbs_deb_leave_args(LBS_DEB_JOIN, "ret %d", ret);
	return ret;
}