#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct ieee80211_mmie {int dummy; } ;
struct TYPE_12__ {int cipher; int keyidx; size_t keylen; int icv_len; int /*<<< orphan*/  key; int /*<<< orphan*/  iv_len; scalar_t__ flags; } ;
struct TYPE_10__ {int /*<<< orphan*/  tfm; int /*<<< orphan*/ * rx_pn; } ;
struct TYPE_9__ {int /*<<< orphan*/  tfm; int /*<<< orphan*/ ** rx_pn; } ;
struct TYPE_8__ {int /*<<< orphan*/  txlock; TYPE_1__* rx; } ;
struct TYPE_11__ {TYPE_4__ aes_cmac; TYPE_3__ ccmp; TYPE_2__ tkip; } ;
struct ieee80211_key {int /*<<< orphan*/  list; TYPE_6__ conf; TYPE_5__ u; scalar_t__ flags; } ;
struct TYPE_7__ {int /*<<< orphan*/  iv16; int /*<<< orphan*/  iv32; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CCMP_HDR_LEN ; 
 int CCMP_MIC_LEN ; 
 int CCMP_PN_LEN ; 
 int CMAC_PN_LEN ; 
 int ENOMEM ; 
 struct ieee80211_key* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IEEE80211_NUM_TIDS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int NUM_DEFAULT_KEYS ; 
 int NUM_DEFAULT_MGMT_KEYS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int TKIP_ICV_LEN ; 
 int /*<<< orphan*/  TKIP_IV_LEN ; 
 int WEP_ICV_LEN ; 
 int /*<<< orphan*/  WEP_IV_LEN ; 
#define  WLAN_CIPHER_SUITE_AES_CMAC 132 
#define  WLAN_CIPHER_SUITE_CCMP 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 
 int /*<<< orphan*/  get_unaligned_le16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  get_unaligned_le32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ieee80211_aes_cmac_key_setup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ieee80211_aes_key_setup_encrypt (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  kfree (struct ieee80211_key*) ; 
 struct ieee80211_key* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct ieee80211_key *ieee80211_key_alloc(u32 cipher, int idx, size_t key_len,
					  const u8 *key_data,
					  size_t seq_len, const u8 *seq)
{
	struct ieee80211_key *key;
	int i, j, err;

	BUG_ON(idx < 0 || idx >= NUM_DEFAULT_KEYS + NUM_DEFAULT_MGMT_KEYS);

	key = kzalloc(sizeof(struct ieee80211_key) + key_len, GFP_KERNEL);
	if (!key)
		return ERR_PTR(-ENOMEM);

	/*
	 * Default to software encryption; we'll later upload the
	 * key to the hardware if possible.
	 */
	key->conf.flags = 0;
	key->flags = 0;

	key->conf.cipher = cipher;
	key->conf.keyidx = idx;
	key->conf.keylen = key_len;
	switch (cipher) {
	case WLAN_CIPHER_SUITE_WEP40:
	case WLAN_CIPHER_SUITE_WEP104:
		key->conf.iv_len = WEP_IV_LEN;
		key->conf.icv_len = WEP_ICV_LEN;
		break;
	case WLAN_CIPHER_SUITE_TKIP:
		key->conf.iv_len = TKIP_IV_LEN;
		key->conf.icv_len = TKIP_ICV_LEN;
		if (seq) {
			for (i = 0; i < IEEE80211_NUM_TIDS; i++) {
				key->u.tkip.rx[i].iv32 =
					get_unaligned_le32(&seq[2]);
				key->u.tkip.rx[i].iv16 =
					get_unaligned_le16(seq);
			}
		}
		spin_lock_init(&key->u.tkip.txlock);
		break;
	case WLAN_CIPHER_SUITE_CCMP:
		key->conf.iv_len = CCMP_HDR_LEN;
		key->conf.icv_len = CCMP_MIC_LEN;
		if (seq) {
			for (i = 0; i < IEEE80211_NUM_TIDS + 1; i++)
				for (j = 0; j < CCMP_PN_LEN; j++)
					key->u.ccmp.rx_pn[i][j] =
						seq[CCMP_PN_LEN - j - 1];
		}
		/*
		 * Initialize AES key state here as an optimization so that
		 * it does not need to be initialized for every packet.
		 */
		key->u.ccmp.tfm = ieee80211_aes_key_setup_encrypt(key_data);
		if (IS_ERR(key->u.ccmp.tfm)) {
			err = PTR_ERR(key->u.ccmp.tfm);
			kfree(key);
			return ERR_PTR(err);
		}
		break;
	case WLAN_CIPHER_SUITE_AES_CMAC:
		key->conf.iv_len = 0;
		key->conf.icv_len = sizeof(struct ieee80211_mmie);
		if (seq)
			for (j = 0; j < CMAC_PN_LEN; j++)
				key->u.aes_cmac.rx_pn[j] =
					seq[CMAC_PN_LEN - j - 1];
		/*
		 * Initialize AES key state here as an optimization so that
		 * it does not need to be initialized for every packet.
		 */
		key->u.aes_cmac.tfm =
			ieee80211_aes_cmac_key_setup(key_data);
		if (IS_ERR(key->u.aes_cmac.tfm)) {
			err = PTR_ERR(key->u.aes_cmac.tfm);
			kfree(key);
			return ERR_PTR(err);
		}
		break;
	}
	memcpy(key->conf.key, key_data, key_len);
	INIT_LIST_HEAD(&key->list);

	return key;
}