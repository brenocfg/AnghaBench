#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct sta_info {TYPE_1__ sta; int /*<<< orphan*/  sdata; scalar_t__ rate_ctrl; } ;
struct ieee80211_local {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct sta_info*) ; 
 int /*<<< orphan*/  rate_control_free_sta (struct sta_info*) ; 
 int /*<<< orphan*/  sta_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void sta_info_free(struct ieee80211_local *local, struct sta_info *sta)
{
	if (sta->rate_ctrl)
		rate_control_free_sta(sta);

	sta_dbg(sta->sdata, "Destroyed STA %pM\n", sta->sta.addr);

	kfree(sta);
}