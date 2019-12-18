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
struct device {int dummy; } ;
struct net_device {struct device dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_errors; } ;
struct emac_priv {TYPE_1__ net_dev_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMAC_DEF_TX_CH ; 
 int /*<<< orphan*/  EMAC_TXHDP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EMAC_TXINTMASKSET ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  emac_cleanup_txch (struct emac_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emac_init_txch (struct emac_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emac_int_disable (struct emac_priv*) ; 
 int /*<<< orphan*/  emac_int_enable (struct emac_priv*) ; 
 int /*<<< orphan*/  emac_stop_txch (struct emac_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emac_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct emac_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_tx_err (struct emac_priv*) ; 

__attribute__((used)) static void emac_dev_tx_timeout(struct net_device *ndev)
{
	struct emac_priv *priv = netdev_priv(ndev);
	struct device *emac_dev = &ndev->dev;

	if (netif_msg_tx_err(priv))
		dev_err(emac_dev, "DaVinci EMAC: xmit timeout, restarting TX");

	priv->net_dev_stats.tx_errors++;
	emac_int_disable(priv);
	emac_stop_txch(priv, EMAC_DEF_TX_CH);
	emac_cleanup_txch(priv, EMAC_DEF_TX_CH);
	emac_init_txch(priv, EMAC_DEF_TX_CH);
	emac_write(EMAC_TXHDP(0), 0);
	emac_write(EMAC_TXINTMASKSET, BIT(EMAC_DEF_TX_CH));
	emac_int_enable(priv);
}