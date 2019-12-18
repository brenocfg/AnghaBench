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
struct tso_state {scalar_t__ protocol; scalar_t__ dma_flags; scalar_t__ unmap_len; scalar_t__ header_len; scalar_t__ out_len; int /*<<< orphan*/  seqnum; scalar_t__ ipv4_id; scalar_t__ tcp_off; scalar_t__ ip_base_len; scalar_t__ ip_off; } ;
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_3__ {unsigned int doff; int /*<<< orphan*/  rst; int /*<<< orphan*/  syn; int /*<<< orphan*/  urg; int /*<<< orphan*/  seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_BUG_ON_PARANOID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 TYPE_2__* ip_hdr (struct sk_buff const*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_network_header (struct sk_buff const*) ; 
 scalar_t__ skb_transport_header (struct sk_buff const*) ; 
 TYPE_1__* tcp_hdr (struct sk_buff const*) ; 

__attribute__((used)) static void tso_start(struct tso_state *st, const struct sk_buff *skb)
{
	st->ip_off = skb_network_header(skb) - skb->data;
	st->tcp_off = skb_transport_header(skb) - skb->data;
	st->header_len = st->tcp_off + (tcp_hdr(skb)->doff << 2u);
	if (st->protocol == htons(ETH_P_IP)) {
		st->ip_base_len = st->header_len - st->ip_off;
		st->ipv4_id = ntohs(ip_hdr(skb)->id);
	} else {
		st->ip_base_len = st->header_len - st->tcp_off;
		st->ipv4_id = 0;
	}
	st->seqnum = ntohl(tcp_hdr(skb)->seq);

	EFX_BUG_ON_PARANOID(tcp_hdr(skb)->urg);
	EFX_BUG_ON_PARANOID(tcp_hdr(skb)->syn);
	EFX_BUG_ON_PARANOID(tcp_hdr(skb)->rst);

	st->out_len = skb->len - st->header_len;
	st->unmap_len = 0;
	st->dma_flags = 0;
}