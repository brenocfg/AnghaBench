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
struct sk_buff {scalar_t__ len; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {struct net_device* net_dev; } ;
struct i2400m {TYPE_1__ wimax_dev; } ;
struct i2400mu {int rx_size; TYPE_2__* usb_iface; int /*<<< orphan*/  urb_edc; int /*<<< orphan*/  rx_size_acc; int /*<<< orphan*/  rx_size_cnt; int /*<<< orphan*/  rx_pending_count; int /*<<< orphan*/  rx_wq; struct i2400m i2400m; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDC_ERROR_TIMEFRAME ; 
 int /*<<< orphan*/  EDC_MAX_ERRORS ; 
 int EIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 struct sk_buff* __netdev_alloc_skb (struct net_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 size_t atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d_fnend (int,struct device*,char*,struct i2400mu*,int) ; 
 int /*<<< orphan*/  d_fnstart (int,struct device*,char*,struct i2400mu*) ; 
 int /*<<< orphan*/  d_printf (int,struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 scalar_t__ edc_inc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2400m_rx (struct i2400m*,struct sk_buff*) ; 
 struct sk_buff* i2400mu_rx (struct i2400mu*,struct sk_buff*) ; 
 int /*<<< orphan*/  i2400mu_rx_size_maybe_shrink (struct i2400mu*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  usb_queue_reset_device (TYPE_2__*) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
int i2400mu_rxd(void *_i2400mu)
{
	int result = 0;
	struct i2400mu *i2400mu = _i2400mu;
	struct i2400m *i2400m = &i2400mu->i2400m;
	struct device *dev = &i2400mu->usb_iface->dev;
	struct net_device *net_dev = i2400m->wimax_dev.net_dev;
	size_t pending;
	int rx_size;
	struct sk_buff *rx_skb;

	d_fnstart(4, dev, "(i2400mu %p)\n", i2400mu);
	while (1) {
		d_printf(2, dev, "TX: waiting for messages\n");
		pending = 0;
		wait_event_interruptible(
			i2400mu->rx_wq,
			(kthread_should_stop()	/* check this first! */
			 || (pending = atomic_read(&i2400mu->rx_pending_count)))
			);
		if (kthread_should_stop())
			break;
		if (pending == 0)
			continue;
		rx_size = i2400mu->rx_size;
		d_printf(2, dev, "RX: reading up to %d bytes\n", rx_size);
		rx_skb = __netdev_alloc_skb(net_dev, rx_size, GFP_KERNEL);
		if (rx_skb == NULL) {
			dev_err(dev, "RX: can't allocate skb [%d bytes]\n",
				rx_size);
			msleep(50);	/* give it some time? */
			continue;
		}

		/* Receive the message with the payloads */
		rx_skb = i2400mu_rx(i2400mu, rx_skb);
		result = PTR_ERR(rx_skb);
		if (IS_ERR(rx_skb))
			goto out;
		atomic_dec(&i2400mu->rx_pending_count);
		if (rx_skb == NULL || rx_skb->len == 0) {
			/* some "ignorable" condition */
			kfree_skb(rx_skb);
			continue;
		}

		/* Deliver the message to the generic i2400m code */
		i2400mu->rx_size_cnt++;
		i2400mu->rx_size_acc += rx_skb->len;
		result = i2400m_rx(i2400m, rx_skb);
		if (result == -EIO
		    && edc_inc(&i2400mu->urb_edc,
			       EDC_MAX_ERRORS, EDC_ERROR_TIMEFRAME)) {
			goto error_reset;
		}

		/* Maybe adjust RX buffer size */
		i2400mu_rx_size_maybe_shrink(i2400mu);
	}
	result = 0;
out:
	d_fnend(4, dev, "(i2400mu %p) = %d\n", i2400mu, result);
	return result;

error_reset:
	dev_err(dev, "RX: maximum errors in received buffer exceeded; "
		"resetting device\n");
	usb_queue_reset_device(i2400mu->usb_iface);
	goto out;
}