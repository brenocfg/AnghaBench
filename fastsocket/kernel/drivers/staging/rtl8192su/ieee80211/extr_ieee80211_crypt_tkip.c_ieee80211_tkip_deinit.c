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
struct ieee80211_tkip_data {scalar_t__ rx_tfm_arc4; scalar_t__ rx_tfm_michael; scalar_t__ tx_tfm_arc4; scalar_t__ tx_tfm_michael; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_blkcipher (scalar_t__) ; 
 int /*<<< orphan*/  crypto_free_hash (scalar_t__) ; 
 int /*<<< orphan*/  kfree (void*) ; 

__attribute__((used)) static void ieee80211_tkip_deinit(void *priv)
{
	struct ieee80211_tkip_data *_priv = priv;

	if (_priv) {
		if (_priv->tx_tfm_michael)
			crypto_free_hash(_priv->tx_tfm_michael);
		if (_priv->tx_tfm_arc4)
			crypto_free_blkcipher(_priv->tx_tfm_arc4);
		if (_priv->rx_tfm_michael)
			crypto_free_hash(_priv->rx_tfm_michael);
		if (_priv->rx_tfm_arc4)
			crypto_free_blkcipher(_priv->rx_tfm_arc4);
	}
	kfree(priv);
}