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
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  srq; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  pd; TYPE_1__ cm; int /*<<< orphan*/  recv_cq; } ;
struct ipoib_cm_tx {int dummy; } ;
struct TYPE_4__ {int max_send_sge; int /*<<< orphan*/  max_send_wr; } ;
struct ib_qp_init_attr {struct ipoib_cm_tx* qp_context; int /*<<< orphan*/  qp_type; int /*<<< orphan*/  sq_sig_type; TYPE_2__ cap; int /*<<< orphan*/  srq; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; } ;
struct ib_qp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_QPT_RC ; 
 int /*<<< orphan*/  IB_SIGNAL_ALL_WR ; 
 struct ib_qp* ib_create_qp (int /*<<< orphan*/ ,struct ib_qp_init_attr*) ; 
 int /*<<< orphan*/  ipoib_sendq_size ; 
 struct ipoib_dev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static struct ib_qp *ipoib_cm_create_tx_qp(struct net_device *dev, struct ipoib_cm_tx *tx)
{
	struct ipoib_dev_priv *priv = netdev_priv(dev);
	struct ib_qp_init_attr attr = {
		.send_cq		= priv->recv_cq,
		.recv_cq		= priv->recv_cq,
		.srq			= priv->cm.srq,
		.cap.max_send_wr	= ipoib_sendq_size,
		.cap.max_send_sge	= 1,
		.sq_sig_type		= IB_SIGNAL_ALL_WR,
		.qp_type		= IB_QPT_RC,
		.qp_context		= tx
	};

	return ib_create_qp(priv->pd, &attr);
}