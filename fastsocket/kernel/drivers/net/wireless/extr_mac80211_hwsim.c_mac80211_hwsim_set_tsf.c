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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct mac80211_hwsim_data {int /*<<< orphan*/  bcn_delta; int /*<<< orphan*/  tsf_offset; int /*<<< orphan*/  beacon_int; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct mac80211_hwsim_data* priv; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ mac80211_hwsim_get_tsf (struct ieee80211_hw*,struct ieee80211_vif*) ; 

__attribute__((used)) static void mac80211_hwsim_set_tsf(struct ieee80211_hw *hw,
		struct ieee80211_vif *vif, u64 tsf)
{
	struct mac80211_hwsim_data *data = hw->priv;
	u64 now = mac80211_hwsim_get_tsf(hw, vif);
	u32 bcn_int = data->beacon_int;
	s64 delta = tsf - now;

	data->tsf_offset += delta;
	/* adjust after beaconing with new timestamp at old TBTT */
	data->bcn_delta = do_div(delta, bcn_int);
}