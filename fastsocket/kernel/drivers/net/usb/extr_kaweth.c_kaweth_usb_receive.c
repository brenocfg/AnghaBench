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
struct urb {int status; int actual_length; int transfer_buffer_length; struct kaweth_device* context; } ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_errors; } ;
struct kaweth_device {int end; TYPE_1__ stats; scalar_t__ rx_buf; struct net_device* net; int /*<<< orphan*/  device_lock; int /*<<< orphan*/  status; int /*<<< orphan*/  term_wait; } ;
typedef  int __u16 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int ECONNRESET ; 
 int EILSEQ ; 
 int EOVERFLOW ; 
 int EPIPE ; 
 int EPROTO ; 
 int EREMOTEIO ; 
 int ESHUTDOWN ; 
 int ETIME ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IS_BLOCKED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg (char*) ; 
 struct sk_buff* dev_alloc_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (char*,int,...) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  kaweth_resubmit_rx_urb (struct kaweth_device*,int /*<<< orphan*/ ) ; 
 int le16_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,scalar_t__,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kaweth_usb_receive(struct urb *urb)
{
	struct kaweth_device *kaweth = urb->context;
	struct net_device *net = kaweth->net;
	int status = urb->status;

	int count = urb->actual_length;
	int count2 = urb->transfer_buffer_length;

	__u16 pkt_len = le16_to_cpup((__le16 *)kaweth->rx_buf);

	struct sk_buff *skb;

	if (unlikely(status == -EPIPE)) {
		kaweth->stats.rx_errors++;
		kaweth->end = 1;
		wake_up(&kaweth->term_wait);
		dbg("Status was -EPIPE.");
		return;
	}
	if (unlikely(status == -ECONNRESET || status == -ESHUTDOWN)) {
		/* we are killed - set a flag and wake the disconnect handler */
		kaweth->end = 1;
		wake_up(&kaweth->term_wait);
		dbg("Status was -ECONNRESET or -ESHUTDOWN.");
		return;
	}
	if (unlikely(status == -EPROTO || status == -ETIME ||
		     status == -EILSEQ)) {
		kaweth->stats.rx_errors++;
		dbg("Status was -EPROTO, -ETIME, or -EILSEQ.");
		return;
	}
	if (unlikely(status == -EOVERFLOW)) {
		kaweth->stats.rx_errors++;
		dbg("Status was -EOVERFLOW.");
	}
	spin_lock(&kaweth->device_lock);
	if (IS_BLOCKED(kaweth->status)) {
		spin_unlock(&kaweth->device_lock);
		return;
	}
	spin_unlock(&kaweth->device_lock);

	if(status && status != -EREMOTEIO && count != 1) {
		err("%s RX status: %d count: %d packet_len: %d",
                           net->name,
			   status,
			   count,
			   (int)pkt_len);
		kaweth_resubmit_rx_urb(kaweth, GFP_ATOMIC);
                return;
	}

	if(kaweth->net && (count > 2)) {
		if(pkt_len > (count - 2)) {
			err("Packet length too long for USB frame (pkt_len: %x, count: %x)",pkt_len, count);
			err("Packet len & 2047: %x", pkt_len & 2047);
			err("Count 2: %x", count2);
		        kaweth_resubmit_rx_urb(kaweth, GFP_ATOMIC);
                        return;
                }

		if(!(skb = dev_alloc_skb(pkt_len+2))) {
		        kaweth_resubmit_rx_urb(kaweth, GFP_ATOMIC);
                        return;
		}

		skb_reserve(skb, 2);    /* Align IP on 16 byte boundaries */

		skb_copy_to_linear_data(skb, kaweth->rx_buf + 2, pkt_len);

		skb_put(skb, pkt_len);

		skb->protocol = eth_type_trans(skb, net);

		netif_rx(skb);

		kaweth->stats.rx_packets++;
		kaweth->stats.rx_bytes += pkt_len;
	}

	kaweth_resubmit_rx_urb(kaweth, GFP_ATOMIC);
}