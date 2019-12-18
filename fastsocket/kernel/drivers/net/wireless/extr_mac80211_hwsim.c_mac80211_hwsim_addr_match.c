#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct mac80211_hwsim_data {TYPE_2__* hw; } ;
struct mac80211_hwsim_addr_match_data {int ret; int /*<<< orphan*/  const* addr; } ;
struct TYPE_4__ {TYPE_1__* wiphy; } ;
struct TYPE_3__ {int /*<<< orphan*/  perm_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_NORMAL ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mac80211_hwsim_addr_match_data*) ; 
 int /*<<< orphan*/  mac80211_hwsim_addr_iter ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool mac80211_hwsim_addr_match(struct mac80211_hwsim_data *data,
				      const u8 *addr)
{
	struct mac80211_hwsim_addr_match_data md;

	if (memcmp(addr, data->hw->wiphy->perm_addr, ETH_ALEN) == 0)
		return true;

	md.ret = false;
	md.addr = addr;
	ieee80211_iterate_active_interfaces_atomic(data->hw,
						   IEEE80211_IFACE_ITER_NORMAL,
						   mac80211_hwsim_addr_iter,
						   &md);

	return md.ret;
}