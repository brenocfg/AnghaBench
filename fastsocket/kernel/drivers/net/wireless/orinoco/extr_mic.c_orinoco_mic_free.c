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
struct orinoco_private {scalar_t__ rx_tfm_mic; scalar_t__ tx_tfm_mic; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_hash (scalar_t__) ; 

void orinoco_mic_free(struct orinoco_private *priv)
{
	if (priv->tx_tfm_mic)
		crypto_free_hash(priv->tx_tfm_mic);
	if (priv->rx_tfm_mic)
		crypto_free_hash(priv->rx_tfm_mic);
}