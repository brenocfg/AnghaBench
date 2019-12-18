#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int* data; scalar_t__ len; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int fragno; int /*<<< orphan*/  frag_queue; scalar_t__ fraglen; TYPE_1__* ax25_dev; } ;
typedef  TYPE_2__ ax25_cb ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ AX25_MAX_HEADER_LEN ; 
 int AX25_SEG_FIRST ; 
 int AX25_SEG_REM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sk_buff* alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ax25_rx_iframe (TYPE_2__*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 

__attribute__((used)) static int ax25_rx_fragment(ax25_cb *ax25, struct sk_buff *skb)
{
	struct sk_buff *skbn, *skbo;

	if (ax25->fragno != 0) {
		if (!(*skb->data & AX25_SEG_FIRST)) {
			if ((ax25->fragno - 1) == (*skb->data & AX25_SEG_REM)) {
				/* Enqueue fragment */
				ax25->fragno = *skb->data & AX25_SEG_REM;
				skb_pull(skb, 1);	/* skip fragno */
				ax25->fraglen += skb->len;
				skb_queue_tail(&ax25->frag_queue, skb);

				/* Last fragment received ? */
				if (ax25->fragno == 0) {
					skbn = alloc_skb(AX25_MAX_HEADER_LEN +
							 ax25->fraglen,
							 GFP_ATOMIC);
					if (!skbn) {
						skb_queue_purge(&ax25->frag_queue);
						return 1;
					}

					skb_reserve(skbn, AX25_MAX_HEADER_LEN);

					skbn->dev   = ax25->ax25_dev->dev;
					skb_reset_network_header(skbn);
					skb_reset_transport_header(skbn);

					/* Copy data from the fragments */
					while ((skbo = skb_dequeue(&ax25->frag_queue)) != NULL) {
						skb_copy_from_linear_data(skbo,
							  skb_put(skbn, skbo->len),
									  skbo->len);
						kfree_skb(skbo);
					}

					ax25->fraglen = 0;

					if (ax25_rx_iframe(ax25, skbn) == 0)
						kfree_skb(skbn);
				}

				return 1;
			}
		}
	} else {
		/* First fragment received */
		if (*skb->data & AX25_SEG_FIRST) {
			skb_queue_purge(&ax25->frag_queue);
			ax25->fragno = *skb->data & AX25_SEG_REM;
			skb_pull(skb, 1);		/* skip fragno */
			ax25->fraglen = skb->len;
			skb_queue_tail(&ax25->frag_queue, skb);
			return 1;
		}
	}

	return 0;
}