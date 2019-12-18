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
typedef  int u32 ;
struct usb_ctrlrequest {int dummy; } ;
struct urb {int transfer_buffer_length; int setup_dma; int transfer_dma; int transfer_flags; int /*<<< orphan*/  pipe; int /*<<< orphan*/  dev; } ;
struct list_head {int dummy; } ;
struct ehci_qtd {int /*<<< orphan*/  hw_token; int /*<<< orphan*/  qtd_list; int /*<<< orphan*/  qtd_dma; void* hw_next; struct urb* urb; int /*<<< orphan*/  hw_alt_next; } ;
struct ehci_hcd {TYPE_2__* async; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int dma_addr_t ;
struct TYPE_4__ {TYPE_1__* hw; } ;
struct TYPE_3__ {int /*<<< orphan*/  hw_alt_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  EHCI_LIST_END (struct ehci_hcd*) ; 
 int EHCI_TUNE_CERR ; 
 int /*<<< orphan*/  QTD_IOC ; 
 void* QTD_NEXT (struct ehci_hcd*,int /*<<< orphan*/ ) ; 
 int QTD_STS_ACTIVE ; 
 int QTD_TOGGLE ; 
 int URB_NO_INTERRUPT ; 
 int URB_SHORT_NOT_OK ; 
 int URB_ZERO_PACKET ; 
 int /*<<< orphan*/  cpu_to_hc32 (struct ehci_hcd*,int /*<<< orphan*/ ) ; 
 struct ehci_qtd* ehci_qtd_alloc (struct ehci_hcd*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int max_packet (int /*<<< orphan*/ ) ; 
 int qtd_fill (struct ehci_hcd*,struct ehci_qtd*,int,int,int,int) ; 
 int /*<<< orphan*/  qtd_list_free (struct ehci_hcd*,struct urb*,struct list_head*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usb_maxpacket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ usb_pipebulk (int /*<<< orphan*/ ) ; 
 scalar_t__ usb_pipecontrol (int /*<<< orphan*/ ) ; 
 int usb_pipein (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct list_head *
qh_urb_transaction (
	struct ehci_hcd		*ehci,
	struct urb		*urb,
	struct list_head	*head,
	gfp_t			flags
) {
	struct ehci_qtd		*qtd, *qtd_prev;
	dma_addr_t		buf;
	int			len, maxpacket;
	int			is_input;
	u32			token;

	/*
	 * URBs map to sequences of QTDs:  one logical transaction
	 */
	qtd = ehci_qtd_alloc (ehci, flags);
	if (unlikely (!qtd))
		return NULL;
	list_add_tail (&qtd->qtd_list, head);
	qtd->urb = urb;

	token = QTD_STS_ACTIVE;
	token |= (EHCI_TUNE_CERR << 10);
	/* for split transactions, SplitXState initialized to zero */

	len = urb->transfer_buffer_length;
	is_input = usb_pipein (urb->pipe);
	if (usb_pipecontrol (urb->pipe)) {
		/* SETUP pid */
		qtd_fill(ehci, qtd, urb->setup_dma,
				sizeof (struct usb_ctrlrequest),
				token | (2 /* "setup" */ << 8), 8);

		/* ... and always at least one more pid */
		token ^= QTD_TOGGLE;
		qtd_prev = qtd;
		qtd = ehci_qtd_alloc (ehci, flags);
		if (unlikely (!qtd))
			goto cleanup;
		qtd->urb = urb;
		qtd_prev->hw_next = QTD_NEXT(ehci, qtd->qtd_dma);
		list_add_tail (&qtd->qtd_list, head);

		/* for zero length DATA stages, STATUS is always IN */
		if (len == 0)
			token |= (1 /* "in" */ << 8);
	}

	/*
	 * data transfer stage:  buffer setup
	 */
	buf = urb->transfer_dma;

	if (is_input)
		token |= (1 /* "in" */ << 8);
	/* else it's already initted to "out" pid (0 << 8) */

	maxpacket = max_packet(usb_maxpacket(urb->dev, urb->pipe, !is_input));

	/*
	 * buffer gets wrapped in one or more qtds;
	 * last one may be "short" (including zero len)
	 * and may serve as a control status ack
	 */
	for (;;) {
		int this_qtd_len;

		this_qtd_len = qtd_fill(ehci, qtd, buf, len, token, maxpacket);
		len -= this_qtd_len;
		buf += this_qtd_len;

		/*
		 * short reads advance to a "magic" dummy instead of the next
		 * qtd ... that forces the queue to stop, for manual cleanup.
		 * (this will usually be overridden later.)
		 */
		if (is_input)
			qtd->hw_alt_next = ehci->async->hw->hw_alt_next;

		/* qh makes control packets use qtd toggle; maybe switch it */
		if ((maxpacket & (this_qtd_len + (maxpacket - 1))) == 0)
			token ^= QTD_TOGGLE;

		if (likely (len <= 0))
			break;

		qtd_prev = qtd;
		qtd = ehci_qtd_alloc (ehci, flags);
		if (unlikely (!qtd))
			goto cleanup;
		qtd->urb = urb;
		qtd_prev->hw_next = QTD_NEXT(ehci, qtd->qtd_dma);
		list_add_tail (&qtd->qtd_list, head);
	}

	/*
	 * unless the caller requires manual cleanup after short reads,
	 * have the alt_next mechanism keep the queue running after the
	 * last data qtd (the only one, for control and most other cases).
	 */
	if (likely ((urb->transfer_flags & URB_SHORT_NOT_OK) == 0
				|| usb_pipecontrol (urb->pipe)))
		qtd->hw_alt_next = EHCI_LIST_END(ehci);

	/*
	 * control requests may need a terminating data "status" ack;
	 * bulk ones may need a terminating short packet (zero length).
	 */
	if (likely (urb->transfer_buffer_length != 0)) {
		int	one_more = 0;

		if (usb_pipecontrol (urb->pipe)) {
			one_more = 1;
			token ^= 0x0100;	/* "in" <--> "out"  */
			token |= QTD_TOGGLE;	/* force DATA1 */
		} else if (usb_pipebulk (urb->pipe)
				&& (urb->transfer_flags & URB_ZERO_PACKET)
				&& !(urb->transfer_buffer_length % maxpacket)) {
			one_more = 1;
		}
		if (one_more) {
			qtd_prev = qtd;
			qtd = ehci_qtd_alloc (ehci, flags);
			if (unlikely (!qtd))
				goto cleanup;
			qtd->urb = urb;
			qtd_prev->hw_next = QTD_NEXT(ehci, qtd->qtd_dma);
			list_add_tail (&qtd->qtd_list, head);

			/* never any data in such packets */
			qtd_fill(ehci, qtd, 0, 0, token, 0);
		}
	}

	/* by default, enable interrupt on urb completion */
	if (likely (!(urb->transfer_flags & URB_NO_INTERRUPT)))
		qtd->hw_token |= cpu_to_hc32(ehci, QTD_IOC);
	return head;

cleanup:
	qtd_list_free (ehci, urb, head);
	return NULL;
}