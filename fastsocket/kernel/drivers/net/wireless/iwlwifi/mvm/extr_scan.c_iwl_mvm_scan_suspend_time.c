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
struct TYPE_2__ {int /*<<< orphan*/  beacon_int; scalar_t__ assoc; } ;
struct ieee80211_vif {TYPE_1__ bss_conf; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline __le32 iwl_mvm_scan_suspend_time(struct ieee80211_vif *vif)
{
	if (vif->bss_conf.assoc)
		return cpu_to_le32(vif->bss_conf.beacon_int);
	else
		return 0;
}