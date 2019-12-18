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
struct ipoib_dev_priv {int /*<<< orphan*/  pd; int /*<<< orphan*/  mr; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; int /*<<< orphan*/  flags; int /*<<< orphan*/ * qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPOIB_PKEY_ASSIGNED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ib_dealloc_pd (int /*<<< orphan*/ ) ; 
 scalar_t__ ib_dereg_mr (int /*<<< orphan*/ ) ; 
 scalar_t__ ib_destroy_cq (int /*<<< orphan*/ ) ; 
 scalar_t__ ib_destroy_qp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipoib_cm_dev_cleanup (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*) ; 
 struct ipoib_dev_priv* netdev_priv (struct net_device*) ; 

void ipoib_transport_dev_cleanup(struct net_device *dev)
{
	struct ipoib_dev_priv *priv = netdev_priv(dev);

	if (priv->qp) {
		if (ib_destroy_qp(priv->qp))
			ipoib_warn(priv, "ib_qp_destroy failed\n");

		priv->qp = NULL;
		clear_bit(IPOIB_PKEY_ASSIGNED, &priv->flags);
	}

	if (ib_destroy_cq(priv->send_cq))
		ipoib_warn(priv, "ib_cq_destroy (send) failed\n");

	if (ib_destroy_cq(priv->recv_cq))
		ipoib_warn(priv, "ib_cq_destroy (recv) failed\n");

	ipoib_cm_dev_cleanup(dev);

	if (ib_dereg_mr(priv->mr))
		ipoib_warn(priv, "ib_dereg_mr failed\n");

	if (ib_dealloc_pd(priv->pd))
		ipoib_warn(priv, "ib_dealloc_pd failed\n");
}