#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wait_queue_t ;
typedef  int /*<<< orphan*/  ulong ;
struct sk_buff {scalar_t__ len; } ;
struct btmrvl_thread {int /*<<< orphan*/  wait_q; struct btmrvl_private* priv; } ;
struct TYPE_8__ {TYPE_2__* hcidev; int /*<<< orphan*/  tx_dnld_rdy; } ;
struct btmrvl_private {TYPE_3__ btmrvl_dev; int /*<<< orphan*/  driver_lock; int /*<<< orphan*/  (* hw_wakeup_firmware ) (struct btmrvl_private*) ;struct btmrvl_adapter* adapter; } ;
struct btmrvl_adapter {scalar_t__ ps_state; int /*<<< orphan*/  tx_queue; scalar_t__ wakeup_tries; scalar_t__ int_count; } ;
struct TYPE_9__ {int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  byte_tx; int /*<<< orphan*/  err_tx; } ;
struct TYPE_7__ {TYPE_1__ stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*) ; 
 int /*<<< orphan*/  PF_NOFREEZE ; 
 scalar_t__ PS_SLEEP ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ btmrvl_tx_pkt (struct btmrvl_private*,struct sk_buff*) ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  init_waitqueue_entry (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct btmrvl_private*) ; 

__attribute__((used)) static int btmrvl_service_main_thread(void *data)
{
	struct btmrvl_thread *thread = data;
	struct btmrvl_private *priv = thread->priv;
	struct btmrvl_adapter *adapter = priv->adapter;
	wait_queue_t wait;
	struct sk_buff *skb;
	ulong flags;

	init_waitqueue_entry(&wait, current);

	current->flags |= PF_NOFREEZE;

	for (;;) {
		add_wait_queue(&thread->wait_q, &wait);

		set_current_state(TASK_INTERRUPTIBLE);

		if (adapter->wakeup_tries ||
				((!adapter->int_count) &&
				(!priv->btmrvl_dev.tx_dnld_rdy ||
				skb_queue_empty(&adapter->tx_queue)))) {
			BT_DBG("main_thread is sleeping...");
			schedule();
		}

		set_current_state(TASK_RUNNING);

		remove_wait_queue(&thread->wait_q, &wait);

		BT_DBG("main_thread woke up");

		if (kthread_should_stop()) {
			BT_DBG("main_thread: break from main thread");
			break;
		}

		spin_lock_irqsave(&priv->driver_lock, flags);
		if (adapter->int_count) {
			adapter->int_count = 0;
		} else if (adapter->ps_state == PS_SLEEP &&
					!skb_queue_empty(&adapter->tx_queue)) {
			spin_unlock_irqrestore(&priv->driver_lock, flags);
			adapter->wakeup_tries++;
			priv->hw_wakeup_firmware(priv);
			continue;
		}
		spin_unlock_irqrestore(&priv->driver_lock, flags);

		if (adapter->ps_state == PS_SLEEP)
			continue;

		if (!priv->btmrvl_dev.tx_dnld_rdy)
			continue;

		skb = skb_dequeue(&adapter->tx_queue);
		if (skb) {
			if (btmrvl_tx_pkt(priv, skb))
				priv->btmrvl_dev.hcidev->stat.err_tx++;
			else
				priv->btmrvl_dev.hcidev->stat.byte_tx += skb->len;

			kfree_skb(skb);
		}
	}

	return 0;
}