#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct sta_info {int /*<<< orphan*/  users; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; int /*<<< orphan*/  addr2; } ;
struct TYPE_5__ {TYPE_4__* ap; } ;
typedef  TYPE_1__ local_info_t ;
struct TYPE_6__ {int /*<<< orphan*/  sta_table_lock; } ;

/* Variables and functions */
 int IEEE80211_FCTL_FTYPE ; 
 int IEEE80211_FCTL_PM ; 
 int IEEE80211_FCTL_STYPE ; 
 struct sta_info* ap_get_sta (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hostap_update_sta_ps2 (TYPE_1__*,struct sta_info*,int,int,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int hostap_update_sta_ps(local_info_t *local, struct ieee80211_hdr *hdr)
{
	struct sta_info *sta;
	u16 fc;

	spin_lock(&local->ap->sta_table_lock);
	sta = ap_get_sta(local->ap, hdr->addr2);
	if (sta)
		atomic_inc(&sta->users);
	spin_unlock(&local->ap->sta_table_lock);

	if (!sta)
		return -1;

	fc = le16_to_cpu(hdr->frame_control);
	hostap_update_sta_ps2(local, sta, fc & IEEE80211_FCTL_PM,
			      fc & IEEE80211_FCTL_FTYPE,
			      fc & IEEE80211_FCTL_STYPE);

	atomic_dec(&sta->users);
	return 0;
}