#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct usb_cardstate {int busy; int bulk_out_endpointAddr; int /*<<< orphan*/  bulk_out_urb; int /*<<< orphan*/  bulk_out_buffer; int /*<<< orphan*/  udev; scalar_t__ bulk_out_size; } ;
struct TYPE_6__ {struct usb_cardstate* usb; } ;
struct cardstate {int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; scalar_t__ connected; TYPE_1__ hw; struct bc_state* bcs; } ;
struct bc_state {TYPE_2__* tx_skb; } ;
struct TYPE_7__ {unsigned long len; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_INTR ; 
 int /*<<< orphan*/  DEBUG_OUTPUT ; 
 int /*<<< orphan*/  DEBUG_WRITE ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (TYPE_2__*) ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  gigaset_skb_sent (struct bc_state*,TYPE_2__*) ; 
 int /*<<< orphan*/  gigaset_write_bulk_callback ; 
 int min (unsigned long,unsigned int) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_pull (TYPE_2__*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct cardstate*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int write_modem(struct cardstate *cs)
{
	int ret = 0;
	int count;
	struct bc_state *bcs = &cs->bcs[0]; /* only one channel */
	struct usb_cardstate *ucs = cs->hw.usb;
	unsigned long flags;

	gig_dbg(DEBUG_WRITE, "len: %d...", bcs->tx_skb->len);

	if (!bcs->tx_skb->len) {
		dev_kfree_skb_any(bcs->tx_skb);
		bcs->tx_skb = NULL;
		return -EINVAL;
	}

	/* Copy data to bulk out buffer and  // FIXME copying not necessary
	 * transmit data
	 */
	count = min(bcs->tx_skb->len, (unsigned) ucs->bulk_out_size);
	skb_copy_from_linear_data(bcs->tx_skb, ucs->bulk_out_buffer, count);
	skb_pull(bcs->tx_skb, count);
	ucs->busy = 1;
	gig_dbg(DEBUG_OUTPUT, "write_modem: send %d bytes", count);

	spin_lock_irqsave(&cs->lock, flags);
	if (cs->connected) {
		usb_fill_bulk_urb(ucs->bulk_out_urb, ucs->udev,
				  usb_sndbulkpipe(ucs->udev,
						  ucs->bulk_out_endpointAddr & 0x0f),
				  ucs->bulk_out_buffer, count,
				  gigaset_write_bulk_callback, cs);
		ret = usb_submit_urb(ucs->bulk_out_urb, GFP_ATOMIC);
	} else {
		ret = -ENODEV;
	}
	spin_unlock_irqrestore(&cs->lock, flags);

	if (ret) {
		dev_err(cs->dev, "could not submit urb (error %d)\n", -ret);
		ucs->busy = 0;
	}

	if (!bcs->tx_skb->len) {
		/* skb sent completely */
		gigaset_skb_sent(bcs, bcs->tx_skb); //FIXME also, when ret<0?

		gig_dbg(DEBUG_INTR, "kfree skb (Adr: %lx)!",
			(unsigned long) bcs->tx_skb);
		dev_kfree_skb_any(bcs->tx_skb);
		bcs->tx_skb = NULL;
	}

	return ret;
}