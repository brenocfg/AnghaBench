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
struct veth_port {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__* len; int eofmask; int /*<<< orphan*/ * addr; } ;
struct veth_msg {int in_use; TYPE_1__ data; int /*<<< orphan*/  token; int /*<<< orphan*/  dev; int /*<<< orphan*/  skb; } ;
struct veth_lpar_connection {int state; scalar_t__ outstanding_tx; int /*<<< orphan*/  lock; scalar_t__ last_contact; scalar_t__ reset_timeout; int /*<<< orphan*/  reset_timer; } ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct net_device {int dummy; } ;
typedef  size_t HvLpIndex ;
typedef  scalar_t__ HvLpEvent_Rc ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ ETH_HLEN ; 
 scalar_t__ HvLpEvent_Rc_Good ; 
 int VETH_EOF_SHIFT ; 
 int /*<<< orphan*/  VETH_EVENT_FRAMES ; 
 scalar_t__ VETH_MAX_MTU ; 
 int VETH_STATE_READY ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct veth_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  skb_get (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct veth_lpar_connection** veth_cnx ; 
 int /*<<< orphan*/  veth_recycle_msg (struct veth_lpar_connection*,struct veth_msg*) ; 
 scalar_t__ veth_signaldata (struct veth_lpar_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ veth_stack_is_empty (struct veth_lpar_connection*) ; 
 struct veth_msg* veth_stack_pop (struct veth_lpar_connection*) ; 
 int /*<<< orphan*/  veth_stop_queues (struct veth_lpar_connection*) ; 

__attribute__((used)) static int veth_transmit_to_one(struct sk_buff *skb, HvLpIndex rlp,
				struct net_device *dev)
{
	struct veth_lpar_connection *cnx = veth_cnx[rlp];
	struct veth_port *port = netdev_priv(dev);
	HvLpEvent_Rc rc;
	struct veth_msg *msg = NULL;
	unsigned long flags;

	if (! cnx)
		return 0;

	spin_lock_irqsave(&cnx->lock, flags);

	if (! (cnx->state & VETH_STATE_READY))
		goto no_error;

	if ((skb->len - ETH_HLEN) > VETH_MAX_MTU)
		goto drop;

	msg = veth_stack_pop(cnx);
	if (! msg)
		goto drop;

	msg->in_use = 1;
	msg->skb = skb_get(skb);

	msg->data.addr[0] = dma_map_single(port->dev, skb->data,
				skb->len, DMA_TO_DEVICE);

	if (dma_mapping_error(port->dev, msg->data.addr[0]))
		goto recycle_and_drop;

	msg->dev = port->dev;
	msg->data.len[0] = skb->len;
	msg->data.eofmask = 1 << VETH_EOF_SHIFT;

	rc = veth_signaldata(cnx, VETH_EVENT_FRAMES, msg->token, &msg->data);

	if (rc != HvLpEvent_Rc_Good)
		goto recycle_and_drop;

	/* If the timer's not already running, start it now. */
	if (0 == cnx->outstanding_tx)
		mod_timer(&cnx->reset_timer, jiffies + cnx->reset_timeout);

	cnx->last_contact = jiffies;
	cnx->outstanding_tx++;

	if (veth_stack_is_empty(cnx))
		veth_stop_queues(cnx);

 no_error:
	spin_unlock_irqrestore(&cnx->lock, flags);
	return 0;

 recycle_and_drop:
	veth_recycle_msg(cnx, msg);
 drop:
	spin_unlock_irqrestore(&cnx->lock, flags);
	return 1;
}