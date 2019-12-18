#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  tx_slot; } ;
struct ath9k_htc_priv {TYPE_1__ tx; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int MAX_TX_BUF_NUM ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int ath9k_htc_tx_get_slot(struct ath9k_htc_priv *priv)
{
	int slot;

	spin_lock_bh(&priv->tx.tx_lock);
	slot = find_first_zero_bit(priv->tx.tx_slot, MAX_TX_BUF_NUM);
	if (slot >= MAX_TX_BUF_NUM) {
		spin_unlock_bh(&priv->tx.tx_lock);
		return -ENOBUFS;
	}
	__set_bit(slot, priv->tx.tx_slot);
	spin_unlock_bh(&priv->tx.tx_lock);

	return slot;
}