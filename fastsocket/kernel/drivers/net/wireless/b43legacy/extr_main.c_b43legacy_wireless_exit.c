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
struct ssb_device {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct b43legacy_wl {struct ieee80211_hw* hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_free_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ssb_set_devtypedata (struct ssb_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void b43legacy_wireless_exit(struct ssb_device *dev,
				  struct b43legacy_wl *wl)
{
	struct ieee80211_hw *hw = wl->hw;

	ssb_set_devtypedata(dev, NULL);
	ieee80211_free_hw(hw);
}