#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct z8530_channel {int /*<<< orphan*/  netdevice; } ;
struct sk_buff {int /*<<< orphan*/  dev; int /*<<< orphan*/  protocol; scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  hdlc_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static void hostess_input(struct z8530_channel *c, struct sk_buff *skb)
{
	/* Drop the CRC - it's not a good idea to try and negotiate it ;) */
	skb_trim(skb, skb->len - 2);
	skb->protocol = hdlc_type_trans(skb, c->netdevice);
	skb_reset_mac_header(skb);
	skb->dev = c->netdevice;
	/*
	 *	Send it to the PPP layer. We don't have time to process
	 *	it right now.
	 */
	netif_rx(skb);
}