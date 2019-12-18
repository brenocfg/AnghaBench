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
struct ipoib_cm_rx {int dummy; } ;
struct TYPE_4__ {int max_send_wr; int max_send_sge; int /*<<< orphan*/  max_recv_sge; int /*<<< orphan*/  max_recv_wr; } ;
struct ib_qp_init_attr {TYPE_2__ cap; struct ipoib_cm_rx* qp_context; int /*<<< orphan*/  qp_type; int /*<<< orphan*/  sq_sig_type; int /*<<< orphan*/  srq; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; int /*<<< orphan*/  event_handler; } ;
struct ib_qp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_QPT_RC ; 
 int /*<<< orphan*/  IB_SIGNAL_ALL_WR ; 
 int /*<<< orphan*/  IPOIB_CM_RX_SG ; 
 struct ib_qp* ib_create_qp (int /*<<< orphan*/ ,struct ib_qp_init_attr*) ; 
 int /*<<< orphan*/  ipoib_cm_has_srq (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_cm_rx_event_handler ; 
 int /*<<< orphan*/  ipoib_recvq_size ; 
 struct ipoib_dev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static struct ib_qp *ipoib_cm_create_rx_qp(struct net_device *dev,
					   struct ipoib_cm_rx *p)
{
	struct ipoib_dev_priv *priv = netdev_priv(dev);
	struct ib_qp_init_attr attr = {
		.event_handler = ipoib_cm_rx_event_handler,
		.send_cq = priv->recv_cq, /* For drain WR */
		.recv_cq = priv->recv_cq,
		.srq = priv->cm.srq,
		.cap.max_send_wr = 1, /* For drain WR */
		.cap.max_send_sge = 1, /* FIXME: 0 Seems not to work */
		.sq_sig_type = IB_SIGNAL_ALL_WR,
		.qp_type = IB_QPT_RC,
		.qp_context = p,
	};

	if (!ipoib_cm_has_srq(dev)) {
		attr.cap.max_recv_wr  = ipoib_recvq_size;
		attr.cap.max_recv_sge = IPOIB_CM_RX_SG;
	}

	return ib_create_qp(priv->pd, &attr);
}