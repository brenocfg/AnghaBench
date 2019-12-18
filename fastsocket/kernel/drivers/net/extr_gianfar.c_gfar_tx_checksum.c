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
typedef  scalar_t__ u16 ;
struct txfcb {int /*<<< orphan*/  flags; int /*<<< orphan*/  l4os; scalar_t__ l3os; int /*<<< orphan*/  phcs; } ;
struct sk_buff {int dummy; } ;
struct TYPE_6__ {scalar_t__ protocol; } ;
struct TYPE_5__ {int /*<<< orphan*/  check; } ;
struct TYPE_4__ {int /*<<< orphan*/  check; } ;

/* Variables and functions */
 scalar_t__ GMAC_FCB_LEN ; 
 scalar_t__ IPPROTO_UDP ; 
 int /*<<< orphan*/  TXFCB_DEFAULT ; 
 int /*<<< orphan*/  TXFCB_UDP ; 
 TYPE_3__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_network_header_len (struct sk_buff*) ; 
 scalar_t__ skb_network_offset (struct sk_buff*) ; 
 TYPE_2__* tcp_hdr (struct sk_buff*) ; 
 TYPE_1__* udp_hdr (struct sk_buff*) ; 

__attribute__((used)) static inline void gfar_tx_checksum(struct sk_buff *skb, struct txfcb *fcb)
{
	u8 flags = 0;

	/* If we're here, it's a IP packet with a TCP or UDP
	 * payload.  We set it to checksum, using a pseudo-header
	 * we provide
	 */
	flags = TXFCB_DEFAULT;

	/* Tell the controller what the protocol is */
	/* And provide the already calculated phcs */
	if (ip_hdr(skb)->protocol == IPPROTO_UDP) {
		flags |= TXFCB_UDP;
		fcb->phcs = udp_hdr(skb)->check;
	} else
		fcb->phcs = tcp_hdr(skb)->check;

	/* l3os is the distance between the start of the
	 * frame (skb->data) and the start of the IP hdr.
	 * l4os is the distance between the start of the
	 * l3 hdr and the l4 hdr */
	fcb->l3os = (u16)(skb_network_offset(skb) - GMAC_FCB_LEN);
	fcb->l4os = skb_network_header_len(skb);

	fcb->flags = flags;
}