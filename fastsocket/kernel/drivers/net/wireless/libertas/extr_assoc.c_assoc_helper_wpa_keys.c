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
struct lbs_private {int /*<<< orphan*/  wpa_mcast_key; int /*<<< orphan*/  wpa_unicast_key; } ;
struct enc_key {int dummy; } ;
struct assoc_request {unsigned int flags; int /*<<< orphan*/  wpa_mcast_key; int /*<<< orphan*/  wpa_unicast_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSOC_FLAG_WPA_MCAST_KEY ; 
 int /*<<< orphan*/  ASSOC_FLAG_WPA_UCAST_KEY ; 
 int /*<<< orphan*/  CMD_ACT_SET ; 
 int /*<<< orphan*/  LBS_DEB_ASSOC ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,unsigned int*) ; 
 int lbs_cmd_802_11_key_material (struct lbs_private*,int /*<<< orphan*/ ,struct assoc_request*) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int assoc_helper_wpa_keys(struct lbs_private *priv,
                                 struct assoc_request * assoc_req)
{
	int ret = 0;
	unsigned int flags = assoc_req->flags;

	lbs_deb_enter(LBS_DEB_ASSOC);

	/* Work around older firmware bug where WPA unicast and multicast
	 * keys must be set independently.  Seen in SDIO parts with firmware
	 * version 5.0.11p0.
	 */

	if (test_bit(ASSOC_FLAG_WPA_UCAST_KEY, &assoc_req->flags)) {
		clear_bit(ASSOC_FLAG_WPA_MCAST_KEY, &assoc_req->flags);
		ret = lbs_cmd_802_11_key_material(priv, CMD_ACT_SET, assoc_req);
		assoc_req->flags = flags;
	}

	if (ret)
		goto out;

	memcpy(&priv->wpa_unicast_key, &assoc_req->wpa_unicast_key,
			sizeof(struct enc_key));

	if (test_bit(ASSOC_FLAG_WPA_MCAST_KEY, &assoc_req->flags)) {
		clear_bit(ASSOC_FLAG_WPA_UCAST_KEY, &assoc_req->flags);

		ret = lbs_cmd_802_11_key_material(priv, CMD_ACT_SET, assoc_req);
		assoc_req->flags = flags;

		memcpy(&priv->wpa_mcast_key, &assoc_req->wpa_mcast_key,
				sizeof(struct enc_key));
	}

out:
	lbs_deb_leave_args(LBS_DEB_ASSOC, "ret %d", ret);
	return ret;
}