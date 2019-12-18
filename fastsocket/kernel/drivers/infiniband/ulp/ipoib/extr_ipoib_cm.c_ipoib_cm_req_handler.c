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
struct net_device {scalar_t__ state; int /*<<< orphan*/  qp; int /*<<< orphan*/  list; void* jiffies; struct ib_cm_id* id; struct net_device* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  passive_ids; int /*<<< orphan*/  stale_task; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  lock; TYPE_1__ cm; } ;
struct ipoib_cm_rx {scalar_t__ state; int /*<<< orphan*/  qp; int /*<<< orphan*/  list; void* jiffies; struct ib_cm_id* id; struct ipoib_cm_rx* dev; } ;
struct ib_cm_id {struct net_device* context; } ;
struct TYPE_4__ {int /*<<< orphan*/  req_rcvd; } ;
struct ib_cm_event {TYPE_2__ param; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_QP_STATE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPOIB_CM_RX_DELAY ; 
 scalar_t__ IPOIB_CM_RX_LIVE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_destroy_qp (int /*<<< orphan*/ ) ; 
 scalar_t__ ib_modify_qp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_cm_create_rx_qp (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  ipoib_cm_err_attr ; 
 int /*<<< orphan*/  ipoib_cm_has_srq (struct net_device*) ; 
 int ipoib_cm_modify_rx_qp (struct net_device*,struct ib_cm_id*,int /*<<< orphan*/ ,unsigned int) ; 
 int ipoib_cm_nonsrq_init_rx (struct net_device*,struct ib_cm_id*,struct net_device*) ; 
 int ipoib_cm_send_rep (struct net_device*,struct ib_cm_id*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  ipoib_dbg (struct ipoib_dev_priv*,char*) ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*,...) ; 
 int /*<<< orphan*/  ipoib_workqueue ; 
 void* jiffies ; 
 int /*<<< orphan*/  kfree (struct net_device*) ; 
 struct net_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ipoib_dev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int random32 () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipoib_cm_req_handler(struct ib_cm_id *cm_id, struct ib_cm_event *event)
{
	struct net_device *dev = cm_id->context;
	struct ipoib_dev_priv *priv = netdev_priv(dev);
	struct ipoib_cm_rx *p;
	unsigned psn;
	int ret;

	ipoib_dbg(priv, "REQ arrived\n");
	p = kzalloc(sizeof *p, GFP_KERNEL);
	if (!p)
		return -ENOMEM;
	p->dev = dev;
	p->id = cm_id;
	cm_id->context = p;
	p->state = IPOIB_CM_RX_LIVE;
	p->jiffies = jiffies;
	INIT_LIST_HEAD(&p->list);

	p->qp = ipoib_cm_create_rx_qp(dev, p);
	if (IS_ERR(p->qp)) {
		ret = PTR_ERR(p->qp);
		goto err_qp;
	}

	psn = random32() & 0xffffff;
	ret = ipoib_cm_modify_rx_qp(dev, cm_id, p->qp, psn);
	if (ret)
		goto err_modify;

	if (!ipoib_cm_has_srq(dev)) {
		ret = ipoib_cm_nonsrq_init_rx(dev, cm_id, p);
		if (ret)
			goto err_modify;
	}

	spin_lock_irq(&priv->lock);
	queue_delayed_work(ipoib_workqueue,
			   &priv->cm.stale_task, IPOIB_CM_RX_DELAY);
	/* Add this entry to passive ids list head, but do not re-add it
	 * if IB_EVENT_QP_LAST_WQE_REACHED has moved it to flush list. */
	p->jiffies = jiffies;
	if (p->state == IPOIB_CM_RX_LIVE)
		list_move(&p->list, &priv->cm.passive_ids);
	spin_unlock_irq(&priv->lock);

	ret = ipoib_cm_send_rep(dev, cm_id, p->qp, &event->param.req_rcvd, psn);
	if (ret) {
		ipoib_warn(priv, "failed to send REP: %d\n", ret);
		if (ib_modify_qp(p->qp, &ipoib_cm_err_attr, IB_QP_STATE))
			ipoib_warn(priv, "unable to move qp to error state\n");
	}
	return 0;

err_modify:
	ib_destroy_qp(p->qp);
err_qp:
	kfree(p);
	return ret;
}