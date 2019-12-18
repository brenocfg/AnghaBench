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
struct nlattr {int dummy; } ;
struct ieee80211_power_rule {void* max_antenna_gain; void* max_eirp; } ;
struct ieee80211_freq_range {void* max_bandwidth_khz; void* end_freq_khz; void* start_freq_khz; } ;
struct ieee80211_reg_rule {void* flags; struct ieee80211_power_rule power_rule; struct ieee80211_freq_range freq_range; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t NL80211_ATTR_FREQ_RANGE_END ; 
 size_t NL80211_ATTR_FREQ_RANGE_MAX_BW ; 
 size_t NL80211_ATTR_FREQ_RANGE_START ; 
 size_t NL80211_ATTR_POWER_RULE_MAX_ANT_GAIN ; 
 size_t NL80211_ATTR_POWER_RULE_MAX_EIRP ; 
 size_t NL80211_ATTR_REG_RULE_FLAGS ; 
 void* nla_get_u32 (struct nlattr*) ; 

__attribute__((used)) static int parse_reg_rule(struct nlattr *tb[],
	struct ieee80211_reg_rule *reg_rule)
{
	struct ieee80211_freq_range *freq_range = &reg_rule->freq_range;
	struct ieee80211_power_rule *power_rule = &reg_rule->power_rule;

	if (!tb[NL80211_ATTR_REG_RULE_FLAGS])
		return -EINVAL;
	if (!tb[NL80211_ATTR_FREQ_RANGE_START])
		return -EINVAL;
	if (!tb[NL80211_ATTR_FREQ_RANGE_END])
		return -EINVAL;
	if (!tb[NL80211_ATTR_FREQ_RANGE_MAX_BW])
		return -EINVAL;
	if (!tb[NL80211_ATTR_POWER_RULE_MAX_EIRP])
		return -EINVAL;

	reg_rule->flags = nla_get_u32(tb[NL80211_ATTR_REG_RULE_FLAGS]);

	freq_range->start_freq_khz =
		nla_get_u32(tb[NL80211_ATTR_FREQ_RANGE_START]);
	freq_range->end_freq_khz =
		nla_get_u32(tb[NL80211_ATTR_FREQ_RANGE_END]);
	freq_range->max_bandwidth_khz =
		nla_get_u32(tb[NL80211_ATTR_FREQ_RANGE_MAX_BW]);

	power_rule->max_eirp =
		nla_get_u32(tb[NL80211_ATTR_POWER_RULE_MAX_EIRP]);

	if (tb[NL80211_ATTR_POWER_RULE_MAX_ANT_GAIN])
		power_rule->max_antenna_gain =
			nla_get_u32(tb[NL80211_ATTR_POWER_RULE_MAX_ANT_GAIN]);

	return 0;
}