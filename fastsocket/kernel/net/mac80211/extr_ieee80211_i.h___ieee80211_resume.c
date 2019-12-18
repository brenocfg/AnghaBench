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
struct ieee80211_local {int /*<<< orphan*/  scanning; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCAN_HW_SCANNING ; 
 int /*<<< orphan*/  WARN (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct ieee80211_local* hw_to_local (struct ieee80211_hw*) ; 
 int ieee80211_reconfig (struct ieee80211_local*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiphy_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int __ieee80211_resume(struct ieee80211_hw *hw)
{
	struct ieee80211_local *local = hw_to_local(hw);

	WARN(test_bit(SCAN_HW_SCANNING, &local->scanning),
		"%s: resume with hardware scan still in progress\n",
		wiphy_name(hw->wiphy));

	return ieee80211_reconfig(hw_to_local(hw));
}