#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stmmac_priv {int cur_rx; int dma_rx_size; scalar_t__ dirty_tx; scalar_t__ cur_tx; scalar_t__ dma_rx; TYPE_2__* mac_type; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* get_rx_owner ) (scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ likely (int) ; 
 int stub1 (scalar_t__) ; 

__attribute__((used)) static int stmmac_has_work(struct stmmac_priv *priv)
{
	unsigned int has_work = 0;
	int rxret, tx_work = 0;

	rxret = priv->mac_type->ops->get_rx_owner(priv->dma_rx +
		(priv->cur_rx % priv->dma_rx_size));

	if (priv->dirty_tx != priv->cur_tx)
		tx_work = 1;

	if (likely(!rxret || tx_work))
		has_work = 1;

	return has_work;
}