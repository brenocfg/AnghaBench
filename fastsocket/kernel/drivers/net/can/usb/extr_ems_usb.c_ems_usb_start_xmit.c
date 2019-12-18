#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct urb {int /*<<< orphan*/  transfer_dma; int /*<<< orphan*/  transfer_flags; } ;
struct sk_buff {scalar_t__ data; } ;
struct net_device_stats {int /*<<< orphan*/  tx_dropped; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct net_device {int /*<<< orphan*/  trans_start; TYPE_3__ dev; struct net_device_stats stats; } ;
struct ems_usb {int free_slots; int /*<<< orphan*/  active_tx_urbs; int /*<<< orphan*/  udev; int /*<<< orphan*/  tx_submitted; struct ems_tx_urb_context* tx_contexts; } ;
struct ems_tx_urb_context {int echo_index; int dlc; struct ems_usb* dev; } ;
struct TYPE_4__ {int id; int length; int /*<<< orphan*/ * msg; } ;
struct TYPE_5__ {TYPE_1__ can_msg; } ;
struct ems_cpc_msg {TYPE_2__ msg; void* length; int /*<<< orphan*/  type; } ;
struct cpc_can_msg {int dummy; } ;
struct can_frame {int can_id; int can_dlc; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int CAN_EFF_FLAG ; 
 int CAN_ERR_MASK ; 
 int CAN_RTR_FLAG ; 
 void* CPC_CAN_MSG_MIN_SIZE ; 
 int /*<<< orphan*/  CPC_CMD_TYPE_CAN_FRAME ; 
 int /*<<< orphan*/  CPC_CMD_TYPE_EXT_CAN_FRAME ; 
 int /*<<< orphan*/  CPC_CMD_TYPE_EXT_RTR_FRAME ; 
 int /*<<< orphan*/  CPC_CMD_TYPE_RTR_FRAME ; 
 int CPC_HEADER_SIZE ; 
 int CPC_MSG_HEADER_LEN ; 
 int ENODEV ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int MAX_TX_URBS ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  can_free_echo_skb (struct net_device*,int) ; 
 int /*<<< orphan*/  can_put_echo_skb (struct sk_buff*,struct net_device*,int) ; 
 int cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ems_usb_write_bulk_callback ; 
 int /*<<< orphan*/  jiffies ; 
 struct ems_usb* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 scalar_t__ unlikely (int) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * usb_buffer_alloc (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_buffer_free (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,struct ems_tx_urb_context*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static netdev_tx_t ems_usb_start_xmit(struct sk_buff *skb, struct net_device *netdev)
{
	struct ems_usb *dev = netdev_priv(netdev);
	struct ems_tx_urb_context *context = NULL;
	struct net_device_stats *stats = &netdev->stats;
	struct can_frame *cf = (struct can_frame *)skb->data;
	struct ems_cpc_msg *msg;
	struct urb *urb;
	u8 *buf;
	int i, err;
	size_t size = CPC_HEADER_SIZE + CPC_MSG_HEADER_LEN
			+ sizeof(struct cpc_can_msg);

	/* create a URB, and a buffer for it, and copy the data to the URB */
	urb = usb_alloc_urb(0, GFP_ATOMIC);
	if (!urb) {
		dev_err(netdev->dev.parent, "No memory left for URBs\n");
		goto nomem;
	}

	buf = usb_buffer_alloc(dev->udev, size, GFP_ATOMIC, &urb->transfer_dma);
	if (!buf) {
		dev_err(netdev->dev.parent, "No memory left for USB buffer\n");
		usb_free_urb(urb);
		goto nomem;
	}

	msg = (struct ems_cpc_msg *)&buf[CPC_HEADER_SIZE];

	msg->msg.can_msg.id = cf->can_id & CAN_ERR_MASK;
	msg->msg.can_msg.length = cf->can_dlc;

	if (cf->can_id & CAN_RTR_FLAG) {
		msg->type = cf->can_id & CAN_EFF_FLAG ?
			CPC_CMD_TYPE_EXT_RTR_FRAME : CPC_CMD_TYPE_RTR_FRAME;

		msg->length = CPC_CAN_MSG_MIN_SIZE;
	} else {
		msg->type = cf->can_id & CAN_EFF_FLAG ?
			CPC_CMD_TYPE_EXT_CAN_FRAME : CPC_CMD_TYPE_CAN_FRAME;

		for (i = 0; i < cf->can_dlc; i++)
			msg->msg.can_msg.msg[i] = cf->data[i];

		msg->length = CPC_CAN_MSG_MIN_SIZE + cf->can_dlc;
	}

	/* Respect byte order */
	msg->msg.can_msg.id = cpu_to_le32(msg->msg.can_msg.id);

	for (i = 0; i < MAX_TX_URBS; i++) {
		if (dev->tx_contexts[i].echo_index == MAX_TX_URBS) {
			context = &dev->tx_contexts[i];
			break;
		}
	}

	/*
	 * May never happen! When this happens we'd more URBs in flight as
	 * allowed (MAX_TX_URBS).
	 */
	if (!context) {
		usb_unanchor_urb(urb);
		usb_buffer_free(dev->udev, size, buf, urb->transfer_dma);

		dev_warn(netdev->dev.parent, "couldn't find free context\n");

		return NETDEV_TX_BUSY;
	}

	context->dev = dev;
	context->echo_index = i;
	context->dlc = cf->can_dlc;

	usb_fill_bulk_urb(urb, dev->udev, usb_sndbulkpipe(dev->udev, 2), buf,
			  size, ems_usb_write_bulk_callback, context);
	urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
	usb_anchor_urb(urb, &dev->tx_submitted);

	can_put_echo_skb(skb, netdev, context->echo_index);

	atomic_inc(&dev->active_tx_urbs);

	err = usb_submit_urb(urb, GFP_ATOMIC);
	if (unlikely(err)) {
		can_free_echo_skb(netdev, context->echo_index);

		usb_unanchor_urb(urb);
		usb_buffer_free(dev->udev, size, buf, urb->transfer_dma);
		dev_kfree_skb(skb);

		atomic_dec(&dev->active_tx_urbs);

		if (err == -ENODEV) {
			netif_device_detach(netdev);
		} else {
			dev_warn(netdev->dev.parent, "failed tx_urb %d\n", err);

			stats->tx_dropped++;
		}
	} else {
		netdev->trans_start = jiffies;

		/* Slow down tx path */
		if (atomic_read(&dev->active_tx_urbs) >= MAX_TX_URBS ||
		    dev->free_slots < 5) {
			netif_stop_queue(netdev);
		}
	}

	/*
	 * Release our reference to this URB, the USB core will eventually free
	 * it entirely.
	 */
	usb_free_urb(urb);

	return NETDEV_TX_OK;

nomem:
	if (skb)
		dev_kfree_skb(skb);

	stats->tx_dropped++;

	return NETDEV_TX_OK;
}