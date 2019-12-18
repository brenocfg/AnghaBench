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
typedef  int /*<<< orphan*/  u64 ;
struct wireless_dev {int dummy; } ;
struct wiphy {int dummy; } ;
struct ieee80211_local {int dummy; } ;

/* Variables and functions */
 int ieee80211_cancel_roc (struct ieee80211_local*,int /*<<< orphan*/ ,int) ; 
 struct ieee80211_local* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int ieee80211_mgmt_tx_cancel_wait(struct wiphy *wiphy,
					 struct wireless_dev *wdev,
					 u64 cookie)
{
	struct ieee80211_local *local = wiphy_priv(wiphy);

	return ieee80211_cancel_roc(local, cookie, true);
}