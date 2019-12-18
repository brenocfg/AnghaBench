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
struct TYPE_4__ {int /*<<< orphan*/  extension_chan_offset; int /*<<< orphan*/  is_40mhz; int /*<<< orphan*/  enabled; } ;
struct TYPE_3__ {int /*<<< orphan*/  channel; } ;
struct il_priv {TYPE_2__ ht; TYPE_1__ staging; int /*<<< orphan*/  band; scalar_t__ disable_ht40; } ;
struct ieee80211_sta_ht_cap {int /*<<< orphan*/  ht_supported; } ;

/* Variables and functions */
 int il_is_channel_extension (struct il_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

bool
il_is_ht40_tx_allowed(struct il_priv *il, struct ieee80211_sta_ht_cap *ht_cap)
{
	if (!il->ht.enabled || !il->ht.is_40mhz)
		return false;

	/*
	 * We do not check for IEEE80211_HT_CAP_SUP_WIDTH_20_40
	 * the bit will not set if it is pure 40MHz case
	 */
	if (ht_cap && !ht_cap->ht_supported)
		return false;

#ifdef CONFIG_IWLEGACY_DEBUGFS
	if (il->disable_ht40)
		return false;
#endif

	return il_is_channel_extension(il, il->band,
				       le16_to_cpu(il->staging.channel),
				       il->ht.extension_chan_offset);
}