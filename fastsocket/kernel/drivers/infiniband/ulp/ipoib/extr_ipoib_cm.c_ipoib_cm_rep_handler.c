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
struct sk_buff_head {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  lock; } ;
struct ipoib_cm_tx {scalar_t__ mtu; int /*<<< orphan*/  dev; TYPE_1__* neigh; int /*<<< orphan*/  flags; int /*<<< orphan*/  qp; } ;
struct ipoib_cm_data {int /*<<< orphan*/  mtu; } ;
struct ib_qp_attr {int /*<<< orphan*/  qp_state; scalar_t__ rq_psn; } ;
struct ib_cm_id {struct ipoib_cm_tx* context; } ;
struct ib_cm_event {struct ipoib_cm_data* private_data; } ;
struct TYPE_2__ {struct sk_buff_head queue; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IB_QPS_RTR ; 
 int /*<<< orphan*/  IB_QPS_RTS ; 
 scalar_t__ IPOIB_ENCAP_LEN ; 
 int /*<<< orphan*/  IPOIB_FLAG_OPER_UP ; 
 struct sk_buff* __skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ dev_queue_xmit (struct sk_buff*) ; 
 int ib_cm_init_qp_attr (struct ib_cm_id*,struct ib_qp_attr*,int*) ; 
 int ib_modify_qp (int /*<<< orphan*/ ,struct ib_qp_attr*,int) ; 
 int ib_send_cm_rtu (struct ib_cm_id*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*,...) ; 
 struct ipoib_dev_priv* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipoib_cm_rep_handler(struct ib_cm_id *cm_id, struct ib_cm_event *event)
{
	struct ipoib_cm_tx *p = cm_id->context;
	struct ipoib_dev_priv *priv = netdev_priv(p->dev);
	struct ipoib_cm_data *data = event->private_data;
	struct sk_buff_head skqueue;
	struct ib_qp_attr qp_attr;
	int qp_attr_mask, ret;
	struct sk_buff *skb;

	p->mtu = be32_to_cpu(data->mtu);

	if (p->mtu <= IPOIB_ENCAP_LEN) {
		ipoib_warn(priv, "Rejecting connection: mtu %d <= %d\n",
			   p->mtu, IPOIB_ENCAP_LEN);
		return -EINVAL;
	}

	qp_attr.qp_state = IB_QPS_RTR;
	ret = ib_cm_init_qp_attr(cm_id, &qp_attr, &qp_attr_mask);
	if (ret) {
		ipoib_warn(priv, "failed to init QP attr for RTR: %d\n", ret);
		return ret;
	}

	qp_attr.rq_psn = 0 /* FIXME */;
	ret = ib_modify_qp(p->qp, &qp_attr, qp_attr_mask);
	if (ret) {
		ipoib_warn(priv, "failed to modify QP to RTR: %d\n", ret);
		return ret;
	}

	qp_attr.qp_state = IB_QPS_RTS;
	ret = ib_cm_init_qp_attr(cm_id, &qp_attr, &qp_attr_mask);
	if (ret) {
		ipoib_warn(priv, "failed to init QP attr for RTS: %d\n", ret);
		return ret;
	}
	ret = ib_modify_qp(p->qp, &qp_attr, qp_attr_mask);
	if (ret) {
		ipoib_warn(priv, "failed to modify QP to RTS: %d\n", ret);
		return ret;
	}

	skb_queue_head_init(&skqueue);

	spin_lock_irq(&priv->lock);
	set_bit(IPOIB_FLAG_OPER_UP, &p->flags);
	if (p->neigh)
		while ((skb = __skb_dequeue(&p->neigh->queue)))
			__skb_queue_tail(&skqueue, skb);
	spin_unlock_irq(&priv->lock);

	while ((skb = __skb_dequeue(&skqueue))) {
		skb->dev = p->dev;
		if (dev_queue_xmit(skb))
			ipoib_warn(priv, "dev_queue_xmit failed "
				   "to requeue packet\n");
	}

	ret = ib_send_cm_rtu(cm_id, NULL, 0);
	if (ret) {
		ipoib_warn(priv, "failed to send RTU: %d\n", ret);
		return ret;
	}
	return 0;
}