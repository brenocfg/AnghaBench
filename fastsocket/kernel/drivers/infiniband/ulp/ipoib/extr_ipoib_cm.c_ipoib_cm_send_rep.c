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
struct net_device {int dummy; } ;
struct ipoib_dev_priv {TYPE_1__* qp; } ;
struct ipoib_cm_data {void* mtu; void* qpn; } ;
struct ib_qp {int /*<<< orphan*/  qp_num; } ;
struct ib_cm_req_event_param {int /*<<< orphan*/  rnr_retry_count; } ;
struct ib_cm_rep_param {int private_data_len; unsigned int starting_psn; int /*<<< orphan*/  qp_num; int /*<<< orphan*/  srq; int /*<<< orphan*/  rnr_retry_count; scalar_t__ flow_control; struct ipoib_cm_data* private_data; } ;
struct ib_cm_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  qp_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPOIB_CM_BUF_SIZE ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int ib_send_cm_rep (struct ib_cm_id*,struct ib_cm_rep_param*) ; 
 int /*<<< orphan*/  ipoib_cm_has_srq (struct net_device*) ; 
 struct ipoib_dev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ipoib_cm_send_rep(struct net_device *dev, struct ib_cm_id *cm_id,
			     struct ib_qp *qp, struct ib_cm_req_event_param *req,
			     unsigned psn)
{
	struct ipoib_dev_priv *priv = netdev_priv(dev);
	struct ipoib_cm_data data = {};
	struct ib_cm_rep_param rep = {};

	data.qpn = cpu_to_be32(priv->qp->qp_num);
	data.mtu = cpu_to_be32(IPOIB_CM_BUF_SIZE);

	rep.private_data = &data;
	rep.private_data_len = sizeof data;
	rep.flow_control = 0;
	rep.rnr_retry_count = req->rnr_retry_count;
	rep.srq = ipoib_cm_has_srq(dev);
	rep.qp_num = qp->qp_num;
	rep.starting_psn = psn;
	return ib_send_cm_rep(cm_id, &rep);
}