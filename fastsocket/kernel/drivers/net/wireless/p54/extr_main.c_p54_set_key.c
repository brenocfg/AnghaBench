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
typedef  scalar_t__ u8 ;
struct p54_common {int privacy_caps; int /*<<< orphan*/  conf_mutex; int /*<<< orphan*/  used_rxkeys; int /*<<< orphan*/  rx_keycache_size; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {scalar_t__* addr; } ;
struct ieee80211_key_conf {int flags; int cipher; int hw_key_idx; int /*<<< orphan*/  key; int /*<<< orphan*/  keylen; int /*<<< orphan*/  keyidx; } ;
struct ieee80211_hw {struct p54_common* priv; } ;
typedef  enum set_key_cmd { ____Placeholder_set_key_cmd } set_key_cmd ;

/* Variables and functions */
 int BR_DESC_PRIV_CAP_AESCCMP ; 
 int BR_DESC_PRIV_CAP_MICHAEL ; 
 int BR_DESC_PRIV_CAP_TKIP ; 
 int BR_DESC_PRIV_CAP_WEP ; 
 int EOPNOTSUPP ; 
 int IEEE80211_KEY_FLAG_GENERATE_IV ; 
 int IEEE80211_KEY_FLAG_RX_MGMT ; 
 scalar_t__ P54_CRYPTO_AESCCMP ; 
 scalar_t__ P54_CRYPTO_TKIPMICHAEL ; 
 scalar_t__ P54_CRYPTO_WEP ; 
 int SET_KEY ; 
#define  WLAN_CIPHER_SUITE_CCMP 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 
 int bitmap_find_free_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_release_region (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ modparam_nohwcrypt ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int p54_upload_key (struct p54_common*,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int p54_set_key(struct ieee80211_hw *dev, enum set_key_cmd cmd,
		       struct ieee80211_vif *vif, struct ieee80211_sta *sta,
		       struct ieee80211_key_conf *key)
{
	struct p54_common *priv = dev->priv;
	int slot, ret = 0;
	u8 algo = 0;
	u8 *addr = NULL;

	if (modparam_nohwcrypt)
		return -EOPNOTSUPP;

	if (key->flags & IEEE80211_KEY_FLAG_RX_MGMT) {
		/*
		 * Unfortunately most/all firmwares are trying to decrypt
		 * incoming management frames if a suitable key can be found.
		 * However, in doing so the data in these frames gets
		 * corrupted. So, we can't have firmware supported crypto
		 * offload in this case.
		 */
		return -EOPNOTSUPP;
	}

	mutex_lock(&priv->conf_mutex);
	if (cmd == SET_KEY) {
		switch (key->cipher) {
		case WLAN_CIPHER_SUITE_TKIP:
			if (!(priv->privacy_caps & (BR_DESC_PRIV_CAP_MICHAEL |
			      BR_DESC_PRIV_CAP_TKIP))) {
				ret = -EOPNOTSUPP;
				goto out_unlock;
			}
			key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;
			algo = P54_CRYPTO_TKIPMICHAEL;
			break;
		case WLAN_CIPHER_SUITE_WEP40:
		case WLAN_CIPHER_SUITE_WEP104:
			if (!(priv->privacy_caps & BR_DESC_PRIV_CAP_WEP)) {
				ret = -EOPNOTSUPP;
				goto out_unlock;
			}
			key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;
			algo = P54_CRYPTO_WEP;
			break;
		case WLAN_CIPHER_SUITE_CCMP:
			if (!(priv->privacy_caps & BR_DESC_PRIV_CAP_AESCCMP)) {
				ret = -EOPNOTSUPP;
				goto out_unlock;
			}
			key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;
			algo = P54_CRYPTO_AESCCMP;
			break;
		default:
			ret = -EOPNOTSUPP;
			goto out_unlock;
		}
		slot = bitmap_find_free_region(priv->used_rxkeys,
					       priv->rx_keycache_size, 0);

		if (slot < 0) {
			/*
			 * The device supports the chosen algorithm, but the
			 * firmware does not provide enough key slots to store
			 * all of them.
			 * But encryption offload for outgoing frames is always
			 * possible, so we just pretend that the upload was
			 * successful and do the decryption in software.
			 */

			/* mark the key as invalid. */
			key->hw_key_idx = 0xff;
			goto out_unlock;
		}
	} else {
		slot = key->hw_key_idx;

		if (slot == 0xff) {
			/* This key was not uploaded into the rx key cache. */

			goto out_unlock;
		}

		bitmap_release_region(priv->used_rxkeys, slot, 0);
		algo = 0;
	}

	if (sta)
		addr = sta->addr;

	ret = p54_upload_key(priv, algo, slot, key->keyidx,
			     key->keylen, addr, key->key);
	if (ret) {
		bitmap_release_region(priv->used_rxkeys, slot, 0);
		ret = -EOPNOTSUPP;
		goto out_unlock;
	}

	key->hw_key_idx = slot;

out_unlock:
	mutex_unlock(&priv->conf_mutex);
	return ret;
}