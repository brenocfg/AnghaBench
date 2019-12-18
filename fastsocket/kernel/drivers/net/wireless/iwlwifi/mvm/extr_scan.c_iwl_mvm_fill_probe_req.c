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
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/ * variable; } ;
struct TYPE_4__ {TYPE_1__ probe_req; } ;
struct ieee80211_mgmt {TYPE_2__ u; scalar_t__ seq_ctrl; int /*<<< orphan*/  bssid; int /*<<< orphan*/ * sa; int /*<<< orphan*/  da; int /*<<< orphan*/  frame_control; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  IEEE80211_STYPE_PROBE_REQ ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WLAN_EID_SSID ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_broadcast_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static u16 iwl_mvm_fill_probe_req(struct ieee80211_mgmt *frame, const u8 *ta,
				  int n_ssids, const u8 *ssid, int ssid_len,
				  const u8 *ie, int ie_len,
				  int left)
{
	int len = 0;
	u8 *pos = NULL;

	/* Make sure there is enough space for the probe request,
	 * two mandatory IEs and the data */
	left -= 24;
	if (left < 0)
		return 0;

	frame->frame_control = cpu_to_le16(IEEE80211_STYPE_PROBE_REQ);
	eth_broadcast_addr(frame->da);
	memcpy(frame->sa, ta, ETH_ALEN);
	eth_broadcast_addr(frame->bssid);
	frame->seq_ctrl = 0;

	len += 24;

	/* for passive scans, no need to fill anything */
	if (n_ssids == 0)
		return (u16)len;

	/* points to the payload of the request */
	pos = &frame->u.probe_req.variable[0];

	/* fill in our SSID IE */
	left -= ssid_len + 2;
	if (left < 0)
		return 0;
	*pos++ = WLAN_EID_SSID;
	*pos++ = ssid_len;
	if (ssid && ssid_len) { /* ssid_len may be == 0 even if ssid is valid */
		memcpy(pos, ssid, ssid_len);
		pos += ssid_len;
	}

	len += ssid_len + 2;

	if (WARN_ON(left < ie_len))
		return len;

	if (ie && ie_len) {
		memcpy(pos, ie, ie_len);
		len += ie_len;
	}

	return (u16)len;
}