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
struct bdx_priv {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER ; 
 int /*<<< orphan*/  RET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdx_hw_stop (struct bdx_priv*) ; 
 int /*<<< orphan*/  bdx_reset (struct bdx_priv*) ; 
 int /*<<< orphan*/  bdx_rx_free (struct bdx_priv*) ; 
 int /*<<< orphan*/  bdx_tx_free (struct bdx_priv*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct bdx_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bdx_close(struct net_device *ndev)
{
	struct bdx_priv *priv = NULL;

	ENTER;
	priv = netdev_priv(ndev);

	napi_disable(&priv->napi);

	bdx_reset(priv);
	bdx_hw_stop(priv);
	bdx_rx_free(priv);
	bdx_tx_free(priv);
	RET(0);
}