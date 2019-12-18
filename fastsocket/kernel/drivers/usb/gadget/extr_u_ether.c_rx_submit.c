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
struct usb_request {size_t length; int /*<<< orphan*/  list; struct sk_buff* context; int /*<<< orphan*/  complete; int /*<<< orphan*/  buf; } ;
struct usb_ep {int maxpacket; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct ethhdr {int dummy; } ;
struct eth_dev {int /*<<< orphan*/  req_lock; int /*<<< orphan*/  rx_reqs; TYPE_2__* port_usb; TYPE_1__* net; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_4__ {scalar_t__ header_len; struct usb_ep* out_ep; } ;
struct TYPE_3__ {scalar_t__ mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct eth_dev*,char*,...) ; 
 int ENOMEM ; 
 int ENOTCONN ; 
 scalar_t__ NET_IP_ALIGN ; 
 scalar_t__ RX_EXTRA ; 
 int /*<<< orphan*/  WORK_RX_MEMORY ; 
 struct sk_buff* alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  defer_kevent (struct eth_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rx_complete ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int usb_ep_queue (struct usb_ep*,struct usb_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rx_submit(struct eth_dev *dev, struct usb_request *req, gfp_t gfp_flags)
{
	struct sk_buff	*skb;
	int		retval = -ENOMEM;
	size_t		size = 0;
	struct usb_ep	*out;
	unsigned long	flags;

	spin_lock_irqsave(&dev->lock, flags);
	if (dev->port_usb)
		out = dev->port_usb->out_ep;
	else
		out = NULL;
	spin_unlock_irqrestore(&dev->lock, flags);

	if (!out)
		return -ENOTCONN;


	/* Padding up to RX_EXTRA handles minor disagreements with host.
	 * Normally we use the USB "terminate on short read" convention;
	 * so allow up to (N*maxpacket), since that memory is normally
	 * already allocated.  Some hardware doesn't deal well with short
	 * reads (e.g. DMA must be N*maxpacket), so for now don't trim a
	 * byte off the end (to force hardware errors on overflow).
	 *
	 * RNDIS uses internal framing, and explicitly allows senders to
	 * pad to end-of-packet.  That's potentially nice for speed, but
	 * means receivers can't recover lost synch on their own (because
	 * new packets don't only start after a short RX).
	 */
	size += sizeof(struct ethhdr) + dev->net->mtu + RX_EXTRA;
	size += dev->port_usb->header_len;
	size += out->maxpacket - 1;
	size -= size % out->maxpacket;

	skb = alloc_skb(size + NET_IP_ALIGN, gfp_flags);
	if (skb == NULL) {
		DBG(dev, "no rx skb\n");
		goto enomem;
	}

	/* Some platforms perform better when IP packets are aligned,
	 * but on at least one, checksumming fails otherwise.  Note:
	 * RNDIS headers involve variable numbers of LE32 values.
	 */
	skb_reserve(skb, NET_IP_ALIGN);

	req->buf = skb->data;
	req->length = size;
	req->complete = rx_complete;
	req->context = skb;

	retval = usb_ep_queue(out, req, gfp_flags);
	if (retval == -ENOMEM)
enomem:
		defer_kevent(dev, WORK_RX_MEMORY);
	if (retval) {
		DBG(dev, "rx submit --> %d\n", retval);
		if (skb)
			dev_kfree_skb_any(skb);
		spin_lock_irqsave(&dev->req_lock, flags);
		list_add(&req->list, &dev->rx_reqs);
		spin_unlock_irqrestore(&dev->req_lock, flags);
	}
	return retval;
}