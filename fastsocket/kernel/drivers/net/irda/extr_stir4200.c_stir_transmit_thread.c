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
struct stir_cb {unsigned int speed; scalar_t__ receiving; struct net_device* netdev; int /*<<< orphan*/  tx_pending; } ;
struct sk_buff {scalar_t__ len; } ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CTRL1_RXPWD ; 
 int CTRL1_TXPWD ; 
 int /*<<< orphan*/  REG_CTRL1 ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 scalar_t__ change_speed (struct stir_cb*,unsigned int) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 scalar_t__ fifo_txwait (struct stir_cb*,int) ; 
 int /*<<< orphan*/  freezing (int /*<<< orphan*/ ) ; 
 scalar_t__ irda_device_txqueue_empty (struct net_device*) ; 
 unsigned int irda_get_next_speed (struct sk_buff*) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  receive_start (struct stir_cb*) ; 
 int /*<<< orphan*/  receive_stop (struct stir_cb*) ; 
 int /*<<< orphan*/  refrigerator () ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stir_send (struct stir_cb*,struct sk_buff*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_reg (struct stir_cb*,int /*<<< orphan*/ ,int) ; 
 struct sk_buff* xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stir_transmit_thread(void *arg)
{
	struct stir_cb *stir = arg;
	struct net_device *dev = stir->netdev;
	struct sk_buff *skb;

        while (!kthread_should_stop()) {
#ifdef CONFIG_PM
		/* if suspending, then power off and wait */
		if (unlikely(freezing(current))) {
			if (stir->receiving)
				receive_stop(stir);
			else
				fifo_txwait(stir, -1);

			write_reg(stir, REG_CTRL1, CTRL1_TXPWD|CTRL1_RXPWD);

			refrigerator();

			if (change_speed(stir, stir->speed))
				break;
		}
#endif

		/* if something to send? */
		skb = xchg(&stir->tx_pending, NULL);
		if (skb) {
			unsigned new_speed = irda_get_next_speed(skb);
			netif_wake_queue(dev);

			if (skb->len > 0)
				stir_send(stir, skb);
			dev_kfree_skb(skb);

			if ((new_speed != -1) && (stir->speed != new_speed)) {
				if (fifo_txwait(stir, -1) ||
				    change_speed(stir, new_speed))
					break;
			}
			continue;
		}

		/* nothing to send? start receiving */
		if (!stir->receiving 
		    && irda_device_txqueue_empty(dev)) {
			/* Wait otherwise chip gets confused. */
			if (fifo_txwait(stir, -1))
				break;

			if (unlikely(receive_start(stir))) {
				if (net_ratelimit())
					dev_info(&dev->dev,
						 "%s: receive usb submit failed\n",
						 stir->netdev->name);
				stir->receiving = 0;
				msleep(10);
				continue;
			}
		}

		/* sleep if nothing to send */
                set_current_state(TASK_INTERRUPTIBLE);
                schedule();

	}
        return 0;
}