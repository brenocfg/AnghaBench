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
struct ieee80211_local {void* wep_rx_tfm; void* wep_tx_tfm; int /*<<< orphan*/  wep_iv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_ASYNC ; 
 int /*<<< orphan*/  EINVAL ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  WEP_IV_LEN ; 
 void* crypto_alloc_cipher (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_cipher (void*) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ieee80211_wep_init(struct ieee80211_local *local)
{
	/* start WEP IV from a random value */
	get_random_bytes(&local->wep_iv, WEP_IV_LEN);

	local->wep_tx_tfm = crypto_alloc_cipher("arc4", 0, CRYPTO_ALG_ASYNC);
	if (IS_ERR(local->wep_tx_tfm)) {
		local->wep_rx_tfm = ERR_PTR(-EINVAL);
		return PTR_ERR(local->wep_tx_tfm);
	}

	local->wep_rx_tfm = crypto_alloc_cipher("arc4", 0, CRYPTO_ALG_ASYNC);
	if (IS_ERR(local->wep_rx_tfm)) {
		crypto_free_cipher(local->wep_tx_tfm);
		local->wep_tx_tfm = ERR_PTR(-EINVAL);
		return PTR_ERR(local->wep_rx_tfm);
	}

	return 0;
}