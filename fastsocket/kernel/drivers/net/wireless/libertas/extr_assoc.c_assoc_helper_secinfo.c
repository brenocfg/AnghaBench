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
typedef  int uint16_t ;
struct lbs_private {int /*<<< orphan*/  secinfo; } ;
struct lbs_802_11_security {int dummy; } ;
struct TYPE_2__ {scalar_t__ WPA2enabled; scalar_t__ WPAenabled; } ;
struct assoc_request {TYPE_1__ secinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ACT_GET ; 
 int /*<<< orphan*/  CMD_ACT_SET ; 
 int /*<<< orphan*/  LBS_DEB_ASSOC ; 
 int lbs_cmd_802_11_enable_rsn (struct lbs_private*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  lbs_deb_assoc (char*,int) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lbs_set_mac_control (struct lbs_private*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_1__*,int) ; 

__attribute__((used)) static int assoc_helper_secinfo(struct lbs_private *priv,
                                struct assoc_request * assoc_req)
{
	int ret = 0;
	uint16_t do_wpa;
	uint16_t rsn = 0;

	lbs_deb_enter(LBS_DEB_ASSOC);

	memcpy(&priv->secinfo, &assoc_req->secinfo,
		sizeof(struct lbs_802_11_security));

	lbs_set_mac_control(priv);

	/* If RSN is already enabled, don't try to enable it again, since
	 * ENABLE_RSN resets internal state machines and will clobber the
	 * 4-way WPA handshake.
	 */

	/* Get RSN enabled/disabled */
	ret = lbs_cmd_802_11_enable_rsn(priv, CMD_ACT_GET, &rsn);
	if (ret) {
		lbs_deb_assoc("Failed to get RSN status: %d\n", ret);
		goto out;
	}

	/* Don't re-enable RSN if it's already enabled */
	do_wpa = assoc_req->secinfo.WPAenabled || assoc_req->secinfo.WPA2enabled;
	if (do_wpa == rsn)
		goto out;

	/* Set RSN enabled/disabled */
	ret = lbs_cmd_802_11_enable_rsn(priv, CMD_ACT_SET, &do_wpa);

out:
	lbs_deb_leave_args(LBS_DEB_ASSOC, "ret %d", ret);
	return ret;
}