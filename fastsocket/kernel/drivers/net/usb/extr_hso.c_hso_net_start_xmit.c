#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_9__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_errors; } ;
struct net_device {int /*<<< orphan*/  trans_start; TYPE_3__ stats; } ;
struct hso_net {TYPE_6__* parent; TYPE_4__* mux_bulk_tx_urb; int /*<<< orphan*/  mux_bulk_tx_buf; TYPE_1__* out_endp; struct sk_buff* skb_tx_buf; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_11__ {TYPE_2__* interface; int /*<<< orphan*/  usb; } ;
struct TYPE_10__ {int /*<<< orphan*/  transfer_flags; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int bEndpointAddress; } ;

/* Variables and functions */
 int /*<<< orphan*/  D1 (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DUMP1 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  MUX_BULK_TX_BUF_SIZE ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  URB_ZERO_PACKET ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  hso_get_activity (TYPE_6__*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct hso_net* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct hso_net*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int) ; 
 int usb_submit_urb (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_bulk_callback ; 

__attribute__((used)) static netdev_tx_t hso_net_start_xmit(struct sk_buff *skb,
					    struct net_device *net)
{
	struct hso_net *odev = netdev_priv(net);
	int result;

	/* Tell the kernel, "No more frames 'til we are done with this one." */
	netif_stop_queue(net);
	if (hso_get_activity(odev->parent) == -EAGAIN) {
		odev->skb_tx_buf = skb;
		return NETDEV_TX_OK;
	}

	/* log if asked */
	DUMP1(skb->data, skb->len);
	/* Copy it from kernel memory to OUR memory */
	memcpy(odev->mux_bulk_tx_buf, skb->data, skb->len);
	D1("len: %d/%d", skb->len, MUX_BULK_TX_BUF_SIZE);

	/* Fill in the URB for shipping it out. */
	usb_fill_bulk_urb(odev->mux_bulk_tx_urb,
			  odev->parent->usb,
			  usb_sndbulkpipe(odev->parent->usb,
					  odev->out_endp->
					  bEndpointAddress & 0x7F),
			  odev->mux_bulk_tx_buf, skb->len, write_bulk_callback,
			  odev);

	/* Deal with the Zero Length packet problem, I hope */
	odev->mux_bulk_tx_urb->transfer_flags |= URB_ZERO_PACKET;

	/* Send the URB on its merry way. */
	result = usb_submit_urb(odev->mux_bulk_tx_urb, GFP_ATOMIC);
	if (result) {
		dev_warn(&odev->parent->interface->dev,
			"failed mux_bulk_tx_urb %d", result);
		net->stats.tx_errors++;
		netif_start_queue(net);
	} else {
		net->stats.tx_packets++;
		net->stats.tx_bytes += skb->len;
		/* And tell the kernel when the last transmit started. */
		net->trans_start = jiffies;
	}
	dev_kfree_skb(skb);
	/* we're done */
	return NETDEV_TX_OK;
}