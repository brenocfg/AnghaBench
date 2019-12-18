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
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00lib_crypto {scalar_t__ cmd; scalar_t__ wcid; int /*<<< orphan*/  rx_mic; int /*<<< orphan*/  tx_mic; int /*<<< orphan*/  key; } ;
struct rt2x00_dev {int dummy; } ;
struct ieee80211_key_conf {scalar_t__ hw_key_idx; } ;
struct hw_key_entry {int /*<<< orphan*/  rx_mic; int /*<<< orphan*/  tx_mic; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  key_entry ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  PAIRWISE_KEY_ENTRY (scalar_t__) ; 
 scalar_t__ SET_KEY ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2800_config_wcid_attr_cipher (struct rt2x00_dev*,struct rt2x00lib_crypto*,struct ieee80211_key_conf*) ; 
 int /*<<< orphan*/  rt2800_register_multiwrite (struct rt2x00_dev*,int /*<<< orphan*/ ,struct hw_key_entry*,int) ; 

int rt2800_config_pairwise_key(struct rt2x00_dev *rt2x00dev,
			       struct rt2x00lib_crypto *crypto,
			       struct ieee80211_key_conf *key)
{
	struct hw_key_entry key_entry;
	u32 offset;

	if (crypto->cmd == SET_KEY) {
		/*
		 * Allow key configuration only for STAs that are
		 * known by the hw.
		 */
		if (crypto->wcid < 0)
			return -ENOSPC;
		key->hw_key_idx = crypto->wcid;

		memcpy(key_entry.key, crypto->key,
		       sizeof(key_entry.key));
		memcpy(key_entry.tx_mic, crypto->tx_mic,
		       sizeof(key_entry.tx_mic));
		memcpy(key_entry.rx_mic, crypto->rx_mic,
		       sizeof(key_entry.rx_mic));

		offset = PAIRWISE_KEY_ENTRY(key->hw_key_idx);
		rt2800_register_multiwrite(rt2x00dev, offset,
					      &key_entry, sizeof(key_entry));
	}

	/*
	 * Update WCID information
	 */
	rt2800_config_wcid_attr_cipher(rt2x00dev, crypto, key);

	return 0;
}