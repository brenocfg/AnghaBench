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
struct ieee80211_reg_rule {int dummy; } ;
struct ieee80211_channel {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void chan_reg_rule_print_dbg(struct ieee80211_channel *chan,
				    const struct ieee80211_reg_rule *reg_rule)
{
	return;
}