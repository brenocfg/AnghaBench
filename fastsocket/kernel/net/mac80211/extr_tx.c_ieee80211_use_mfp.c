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
struct sta_info {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
struct ieee80211_hdr {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_STA_MFP ; 
 int /*<<< orphan*/  ieee80211_is_mgmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_robust_mgmt_frame (struct ieee80211_hdr*) ; 
 int /*<<< orphan*/  test_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ieee80211_use_mfp(__le16 fc, struct sta_info *sta,
			     struct sk_buff *skb)
{
	if (!ieee80211_is_mgmt(fc))
		return 0;

	if (sta == NULL || !test_sta_flag(sta, WLAN_STA_MFP))
		return 0;

	if (!ieee80211_is_robust_mgmt_frame((struct ieee80211_hdr *)
					    skb->data))
		return 0;

	return 1;
}