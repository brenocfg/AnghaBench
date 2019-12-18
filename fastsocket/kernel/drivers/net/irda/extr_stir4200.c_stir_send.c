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
struct stir_cb {TYPE_2__* netdev; int /*<<< orphan*/  io_buf; int /*<<< orphan*/  usbdev; int /*<<< orphan*/  speed; scalar_t__ receiving; } ;
struct sk_buff {scalar_t__ len; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct TYPE_4__ {TYPE_1__ stats; int /*<<< orphan*/  trans_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRANSMIT_TIMEOUT ; 
 int /*<<< orphan*/  fifo_txwait (struct stir_cb*,unsigned int) ; 
 int /*<<< orphan*/  irda_get_mtt (struct sk_buff*) ; 
 scalar_t__ isfir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  receive_stop (struct stir_cb*) ; 
 int /*<<< orphan*/  turnaround_delay (struct stir_cb*,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int) ; 
 unsigned int wrap_fir_skb (struct sk_buff*,int /*<<< orphan*/ ) ; 
 unsigned int wrap_sir_skb (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stir_send(struct stir_cb *stir, struct sk_buff *skb)
{
	unsigned wraplen;
	int first_frame = 0;

	/* if receiving, need to turnaround */
	if (stir->receiving) {
		receive_stop(stir);
		turnaround_delay(stir, irda_get_mtt(skb));
		first_frame = 1;
	}

	if (isfir(stir->speed))
		wraplen = wrap_fir_skb(skb, stir->io_buf);
	else
		wraplen = wrap_sir_skb(skb, stir->io_buf);
		
	/* check for space available in fifo */
	if (!first_frame)
		fifo_txwait(stir, wraplen);

	stir->netdev->stats.tx_packets++;
	stir->netdev->stats.tx_bytes += skb->len;
	stir->netdev->trans_start = jiffies;
	pr_debug("send %d (%d)\n", skb->len, wraplen);

	if (usb_bulk_msg(stir->usbdev, usb_sndbulkpipe(stir->usbdev, 1),
			 stir->io_buf, wraplen,
			 NULL, TRANSMIT_TIMEOUT))
		stir->netdev->stats.tx_errors++;
}