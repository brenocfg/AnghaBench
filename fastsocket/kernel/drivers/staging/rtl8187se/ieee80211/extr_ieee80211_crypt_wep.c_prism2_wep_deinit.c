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
struct prism2_wep_data {scalar_t__ rx_tfm; scalar_t__ tx_tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_blkcipher (scalar_t__) ; 
 int /*<<< orphan*/  kfree (void*) ; 

__attribute__((used)) static void prism2_wep_deinit(void *priv)
{
	struct prism2_wep_data *_priv = priv;

	if (_priv) {
		if (_priv->tx_tfm)
			crypto_free_blkcipher(_priv->tx_tfm);
		if (_priv->rx_tfm)
			crypto_free_blkcipher(_priv->rx_tfm);
	}

	kfree(priv);
}