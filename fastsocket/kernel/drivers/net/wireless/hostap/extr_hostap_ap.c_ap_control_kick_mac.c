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
typedef  int /*<<< orphan*/  u8 ;
struct sta_info {int flags; int /*<<< orphan*/  ap; int /*<<< orphan*/  addr; int /*<<< orphan*/  list; } ;
struct net_device {int dummy; } ;
struct ap_data {int /*<<< orphan*/  sta_table_lock; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int EINVAL ; 
 int IEEE80211_FTYPE_MGMT ; 
 int IEEE80211_STYPE_DEAUTH ; 
 int /*<<< orphan*/  WLAN_REASON_PREV_AUTH_NOT_VALID ; 
 int WLAN_STA_ASSOC ; 
 int /*<<< orphan*/  ap_free_sta (struct ap_data*,struct sta_info*) ; 
 struct sta_info* ap_get_sta (struct ap_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ap_sta_hash_del (struct ap_data*,struct sta_info*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostap_event_expired_sta (struct net_device*,struct sta_info*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prism2_send_mgmt (struct net_device*,int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int ap_control_kick_mac(struct ap_data *ap, struct net_device *dev, u8 *mac)
{
	struct sta_info *sta;
	__le16 resp;

	spin_lock_bh(&ap->sta_table_lock);
	sta = ap_get_sta(ap, mac);
	if (sta) {
		ap_sta_hash_del(ap, sta);
		list_del(&sta->list);
	}
	spin_unlock_bh(&ap->sta_table_lock);

	if (!sta)
		return -EINVAL;

	resp = cpu_to_le16(WLAN_REASON_PREV_AUTH_NOT_VALID);
	prism2_send_mgmt(dev, IEEE80211_FTYPE_MGMT | IEEE80211_STYPE_DEAUTH,
			 (char *) &resp, 2, sta->addr, 0);

	if ((sta->flags & WLAN_STA_ASSOC) && !sta->ap)
		hostap_event_expired_sta(dev, sta);

	ap_free_sta(ap, sta);

	return 0;
}