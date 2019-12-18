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
struct zd_mac {int /*<<< orphan*/  chip; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  zd_chip_get_tsf (int /*<<< orphan*/ *) ; 
 struct zd_mac* zd_hw_mac (struct ieee80211_hw*) ; 

__attribute__((used)) static u64 zd_op_get_tsf(struct ieee80211_hw *hw, struct ieee80211_vif *vif)
{
	struct zd_mac *mac = zd_hw_mac(hw);
	return zd_chip_get_tsf(&mac->chip);
}