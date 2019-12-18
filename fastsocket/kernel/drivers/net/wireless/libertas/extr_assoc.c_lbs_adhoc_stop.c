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
struct lbs_private {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;
struct cmd_ds_802_11_ad_hoc_stop {TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_802_11_AD_HOC_STOP ; 
 int /*<<< orphan*/  LBS_DEB_ASSOC ; 
 int /*<<< orphan*/  LBS_DEB_JOIN ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int lbs_cmd_with_response (struct lbs_private*,int /*<<< orphan*/ ,struct cmd_ds_802_11_ad_hoc_stop*) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lbs_mac_event_disconnected (struct lbs_private*) ; 
 int /*<<< orphan*/  memset (struct cmd_ds_802_11_ad_hoc_stop*,int /*<<< orphan*/ ,int) ; 

int lbs_adhoc_stop(struct lbs_private *priv)
{
	struct cmd_ds_802_11_ad_hoc_stop cmd;
	int ret;

	lbs_deb_enter(LBS_DEB_JOIN);

	memset(&cmd, 0, sizeof (cmd));
	cmd.hdr.size = cpu_to_le16 (sizeof (cmd));

	ret = lbs_cmd_with_response(priv, CMD_802_11_AD_HOC_STOP, &cmd);

	/* Clean up everything even if there was an error */
	lbs_mac_event_disconnected(priv);

	lbs_deb_leave_args(LBS_DEB_ASSOC, "ret %d", ret);
	return ret;
}