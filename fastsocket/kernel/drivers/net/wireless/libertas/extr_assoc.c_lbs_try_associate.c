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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/  auth_mode; } ;
struct lbs_private {int fwrelease; int capability; TYPE_2__ secinfo; } ;
struct TYPE_3__ {int capability; int /*<<< orphan*/  bssid; } ;
struct assoc_request {TYPE_1__ bss; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_802_11_ASSOCIATE ; 
 int /*<<< orphan*/  LBS_DEB_ASSOC ; 
 int /*<<< orphan*/  RADIO_PREAMBLE_LONG ; 
 int /*<<< orphan*/  RADIO_PREAMBLE_SHORT ; 
 int WLAN_CAPABILITY_SHORT_PREAMBLE ; 
 int lbs_associate (struct lbs_private*,struct assoc_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int lbs_set_authentication (struct lbs_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lbs_set_radio (struct lbs_private*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lbs_try_associate(struct lbs_private *priv,
	struct assoc_request *assoc_req)
{
	int ret;
	u8 preamble = RADIO_PREAMBLE_LONG;

	lbs_deb_enter(LBS_DEB_ASSOC);

	/* FW v9 and higher indicate authentication suites as a TLV in the
	 * association command, not as a separate authentication command.
	 */
	if (priv->fwrelease < 0x09000000) {
		ret = lbs_set_authentication(priv, assoc_req->bss.bssid,
					     priv->secinfo.auth_mode);
		if (ret)
			goto out;
	}

	/* Use short preamble only when both the BSS and firmware support it */
	if ((priv->capability & WLAN_CAPABILITY_SHORT_PREAMBLE) &&
	    (assoc_req->bss.capability & WLAN_CAPABILITY_SHORT_PREAMBLE))
		preamble = RADIO_PREAMBLE_SHORT;

	ret = lbs_set_radio(priv, preamble, 1);
	if (ret)
		goto out;

	ret = lbs_associate(priv, assoc_req, CMD_802_11_ASSOCIATE);

out:
	lbs_deb_leave_args(LBS_DEB_ASSOC, "ret %d", ret);
	return ret;
}