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
struct xen_netif_rx_response {scalar_t__ status; int flags; scalar_t__ offset; int /*<<< orphan*/  id; } ;
struct xen_netif_extra_info {int dummy; } ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct netfront_rx_info {struct xen_netif_extra_info* extras; struct xen_netif_rx_response rx; } ;
struct TYPE_4__ {scalar_t__ rsp_cons; } ;
struct netfront_info {TYPE_2__ rx; int /*<<< orphan*/  gref_rx_head; TYPE_1__* netdev; } ;
struct device {int dummy; } ;
typedef  scalar_t__ grant_ref_t ;
struct TYPE_3__ {struct device dev; } ;
typedef  scalar_t__ RING_IDX ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int E2BIG ; 
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ GRANT_INVALID_REF ; 
 int MAX_SKB_FRAGS ; 
 int NETRXF_extra_info ; 
 int NETRXF_more_data ; 
 scalar_t__ PAGE_SIZE ; 
 struct xen_netif_rx_response* RING_GET_RESPONSE (TYPE_2__*,scalar_t__) ; 
 scalar_t__ RX_COPY_THRESHOLD ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 unsigned long gnttab_end_foreign_access_ref (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnttab_release_grant_reference (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ net_ratelimit () ; 
 scalar_t__ unlikely (int) ; 
 int xennet_get_extras (struct netfront_info*,struct xen_netif_extra_info*,scalar_t__) ; 
 scalar_t__ xennet_get_rx_ref (struct netfront_info*,scalar_t__) ; 
 struct sk_buff* xennet_get_rx_skb (struct netfront_info*,scalar_t__) ; 
 int /*<<< orphan*/  xennet_move_rx_slot (struct netfront_info*,struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static int xennet_get_responses(struct netfront_info *np,
				struct netfront_rx_info *rinfo, RING_IDX rp,
				struct sk_buff_head *list)
{
	struct xen_netif_rx_response *rx = &rinfo->rx;
	struct xen_netif_extra_info *extras = rinfo->extras;
	struct device *dev = &np->netdev->dev;
	RING_IDX cons = np->rx.rsp_cons;
	struct sk_buff *skb = xennet_get_rx_skb(np, cons);
	grant_ref_t ref = xennet_get_rx_ref(np, cons);
	int max = MAX_SKB_FRAGS + (rx->status <= RX_COPY_THRESHOLD);
	int frags = 1;
	int err = 0;
	unsigned long ret;

	if (rx->flags & NETRXF_extra_info) {
		err = xennet_get_extras(np, extras, rp);
		cons = np->rx.rsp_cons;
	}

	for (;;) {
		if (unlikely(rx->status < 0 ||
			     rx->offset + rx->status > PAGE_SIZE)) {
			if (net_ratelimit())
				dev_warn(dev, "rx->offset: %x, size: %u\n",
					 rx->offset, rx->status);
			xennet_move_rx_slot(np, skb, ref);
			err = -EINVAL;
			goto next;
		}

		/*
		 * This definitely indicates a bug, either in this driver or in
		 * the backend driver. In future this should flag the bad
		 * situation to the system controller to reboot the backed.
		 */
		if (ref == GRANT_INVALID_REF) {
			if (net_ratelimit())
				dev_warn(dev, "Bad rx response id %d.\n",
					 rx->id);
			err = -EINVAL;
			goto next;
		}

		ret = gnttab_end_foreign_access_ref(ref, 0);
		BUG_ON(!ret);

		gnttab_release_grant_reference(&np->gref_rx_head, ref);

		__skb_queue_tail(list, skb);

next:
		if (!(rx->flags & NETRXF_more_data))
			break;

		if (cons + frags == rp) {
			if (net_ratelimit())
				dev_warn(dev, "Need more frags\n");
			err = -ENOENT;
			break;
		}

		rx = RING_GET_RESPONSE(&np->rx, cons + frags);
		skb = xennet_get_rx_skb(np, cons + frags);
		ref = xennet_get_rx_ref(np, cons + frags);
		frags++;
	}

	if (unlikely(frags > max)) {
		if (net_ratelimit())
			dev_warn(dev, "Too many frags\n");
		err = -E2BIG;
	}

	if (unlikely(err))
		np->rx.rsp_cons = cons + frags;

	return err;
}