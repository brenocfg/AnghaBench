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
typedef  size_t u32 ;
struct emac_txch {struct emac_txch* tx_complete; int /*<<< orphan*/ * bd_mem; } ;
struct emac_priv {struct emac_txch** txch; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct emac_txch*) ; 

__attribute__((used)) static void emac_cleanup_txch(struct emac_priv *priv, u32 ch)
{
	struct emac_txch *txch = priv->txch[ch];

	if (txch) {
		if (txch->bd_mem)
			txch->bd_mem = NULL;
		kfree(txch->tx_complete);
		kfree(txch);
		priv->txch[ch] = NULL;
	}
}