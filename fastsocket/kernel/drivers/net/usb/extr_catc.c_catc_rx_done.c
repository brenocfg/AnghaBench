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
typedef  int /*<<< orphan*/  u8 ;
struct urb {int status; int actual_length; int /*<<< orphan*/  dev; int /*<<< orphan*/ * transfer_buffer; struct catc* context; } ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct catc {int /*<<< orphan*/  flags; int /*<<< orphan*/  usbdev; int /*<<< orphan*/  recq_sz; scalar_t__ is_f5u011; TYPE_2__* netdev; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_3__ {int rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_length_errors; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  RX_RUNNING ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbg (char*,...) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,TYPE_2__*) ; 
 int le16_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void catc_rx_done(struct urb *urb)
{
	struct catc *catc = urb->context;
	u8 *pkt_start = urb->transfer_buffer;
	struct sk_buff *skb;
	int pkt_len, pkt_offset = 0;
	int status = urb->status;

	if (!catc->is_f5u011) {
		clear_bit(RX_RUNNING, &catc->flags);
		pkt_offset = 2;
	}

	if (status) {
		dbg("rx_done, status %d, length %d", status, urb->actual_length);
		return;
	}

	do {
		if(!catc->is_f5u011) {
			pkt_len = le16_to_cpup((__le16*)pkt_start);
			if (pkt_len > urb->actual_length) {
				catc->netdev->stats.rx_length_errors++;
				catc->netdev->stats.rx_errors++;
				break;
			}
		} else {
			pkt_len = urb->actual_length;
		}

		if (!(skb = dev_alloc_skb(pkt_len)))
			return;

		skb_copy_to_linear_data(skb, pkt_start + pkt_offset, pkt_len);
		skb_put(skb, pkt_len);

		skb->protocol = eth_type_trans(skb, catc->netdev);
		netif_rx(skb);

		catc->netdev->stats.rx_packets++;
		catc->netdev->stats.rx_bytes += pkt_len;

		/* F5U011 only does one packet per RX */
		if (catc->is_f5u011)
			break;
		pkt_start += (((pkt_len + 1) >> 6) + 1) << 6;

	} while (pkt_start - (u8 *) urb->transfer_buffer < urb->actual_length);

	if (catc->is_f5u011) {
		if (atomic_read(&catc->recq_sz)) {
			int state;
			atomic_dec(&catc->recq_sz);
			dbg("getting extra packet");
			urb->dev = catc->usbdev;
			if ((state = usb_submit_urb(urb, GFP_ATOMIC)) < 0) {
				dbg("submit(rx_urb) status %d", state);
			}
		} else {
			clear_bit(RX_RUNNING, &catc->flags);
		}
	}
}