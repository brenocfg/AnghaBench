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
typedef  void* u8 ;
struct ieee80211_ccmp_data {int key_idx; int key_set; int /*<<< orphan*/  key; struct crypto_tfm* tfm; void** rx_pn; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int CCMP_TK_LEN ; 
 int /*<<< orphan*/  crypto_cipher_setkey (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  memset (struct ieee80211_ccmp_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ieee80211_ccmp_set_key(void *key, int len, u8 *seq, void *priv)
{
	struct ieee80211_ccmp_data *data = priv;
	int keyidx;
	struct crypto_tfm *tfm = data->tfm;

	keyidx = data->key_idx;
	memset(data, 0, sizeof(*data));
	data->key_idx = keyidx;
	data->tfm = tfm;
	if (len == CCMP_TK_LEN) {
		memcpy(data->key, key, CCMP_TK_LEN);
		data->key_set = 1;
		if (seq) {
			data->rx_pn[0] = seq[5];
			data->rx_pn[1] = seq[4];
			data->rx_pn[2] = seq[3];
			data->rx_pn[3] = seq[2];
			data->rx_pn[4] = seq[1];
			data->rx_pn[5] = seq[0];
		}
		crypto_cipher_setkey((void*)data->tfm, data->key, CCMP_TK_LEN);
	} else if (len == 0)
		data->key_set = 0;
	else
		return -1;

	return 0;
}