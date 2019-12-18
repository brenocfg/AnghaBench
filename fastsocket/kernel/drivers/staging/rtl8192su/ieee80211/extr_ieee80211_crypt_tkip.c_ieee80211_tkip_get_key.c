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
typedef  int u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct ieee80211_tkip_data {scalar_t__ tx_iv16; int tx_iv32; int /*<<< orphan*/  key; int /*<<< orphan*/  key_set; } ;

/* Variables and functions */
 int TKIP_KEY_LEN ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ieee80211_tkip_get_key(void *key, int len, u8 *seq, void *priv)
{
	struct ieee80211_tkip_data *tkey = priv;

	if (len < TKIP_KEY_LEN)
		return -1;

	if (!tkey->key_set)
		return 0;
	memcpy(key, tkey->key, TKIP_KEY_LEN);

	if (seq) {
		/* Return the sequence number of the last transmitted frame. */
		u16 iv16 = tkey->tx_iv16;
		u32 iv32 = tkey->tx_iv32;
		if (iv16 == 0)
			iv32--;
		iv16--;
		seq[0] = tkey->tx_iv16;
		seq[1] = tkey->tx_iv16 >> 8;
		seq[2] = tkey->tx_iv32;
		seq[3] = tkey->tx_iv32 >> 8;
		seq[4] = tkey->tx_iv32 >> 16;
		seq[5] = tkey->tx_iv32 >> 24;
	}

	return TKIP_KEY_LEN;
}