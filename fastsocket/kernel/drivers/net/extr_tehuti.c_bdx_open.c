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
struct net_device {int dummy; } ;
struct bdx_priv {int /*<<< orphan*/  nic; int /*<<< orphan*/  napi; int /*<<< orphan*/  rxf_fifo0; int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER ; 
 int /*<<< orphan*/  RET (int) ; 
 int /*<<< orphan*/  bdx_close (struct net_device*) ; 
 int bdx_fw_load (struct bdx_priv*) ; 
 int bdx_hw_start (struct bdx_priv*) ; 
 int /*<<< orphan*/  bdx_reset (struct bdx_priv*) ; 
 int /*<<< orphan*/  bdx_rx_alloc_skbs (struct bdx_priv*,int /*<<< orphan*/ *) ; 
 int bdx_rx_init (struct bdx_priv*) ; 
 int bdx_tx_init (struct bdx_priv*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct bdx_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_fw_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bdx_open(struct net_device *ndev)
{
	struct bdx_priv *priv;
	int rc;

	ENTER;
	priv = netdev_priv(ndev);
	bdx_reset(priv);
	if (netif_running(ndev))
		netif_stop_queue(priv->ndev);

	if ((rc = bdx_tx_init(priv)))
		goto err;

	if ((rc = bdx_rx_init(priv)))
		goto err;

	if ((rc = bdx_fw_load(priv)))
		goto err;

	bdx_rx_alloc_skbs(priv, &priv->rxf_fifo0);

	if ((rc = bdx_hw_start(priv)))
		goto err;

	napi_enable(&priv->napi);

	print_fw_id(priv->nic);

	RET(0);

err:
	bdx_close(ndev);
	RET(rc);
}