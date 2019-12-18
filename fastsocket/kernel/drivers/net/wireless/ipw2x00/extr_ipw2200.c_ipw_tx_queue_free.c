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
struct ipw_priv {int /*<<< orphan*/ * txq; int /*<<< orphan*/  txq_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipw_queue_tx_free (struct ipw_priv*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipw_tx_queue_free(struct ipw_priv *priv)
{
	/* Tx CMD queue */
	ipw_queue_tx_free(priv, &priv->txq_cmd);

	/* Tx queues */
	ipw_queue_tx_free(priv, &priv->txq[0]);
	ipw_queue_tx_free(priv, &priv->txq[1]);
	ipw_queue_tx_free(priv, &priv->txq[2]);
	ipw_queue_tx_free(priv, &priv->txq[3]);
}