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
struct TYPE_3__ {int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_scope_id; scalar_t__ sin6_flowinfo; int /*<<< orphan*/  sin6_family; int /*<<< orphan*/  sin6_port; } ;
union sctp_addr {TYPE_1__ v6; } ;
struct sk_buff {scalar_t__ cb; } ;
struct sctphdr {int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;
struct inet6_skb_parm {int /*<<< orphan*/  iif; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_4__ {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  ipv6_addr_copy (int /*<<< orphan*/ *,void*) ; 
 TYPE_2__* ipv6_hdr (struct sk_buff*) ; 
 struct sctphdr* sctp_hdr (struct sk_buff*) ; 

__attribute__((used)) static void sctp_v6_from_skb(union sctp_addr *addr,struct sk_buff *skb,
			     int is_saddr)
{
	void *from;
	__be16 *port;
	struct sctphdr *sh;

	port = &addr->v6.sin6_port;
	addr->v6.sin6_family = AF_INET6;
	addr->v6.sin6_flowinfo = 0; /* FIXME */
	addr->v6.sin6_scope_id = ((struct inet6_skb_parm *)skb->cb)->iif;

	sh = sctp_hdr(skb);
	if (is_saddr) {
		*port  = sh->source;
		from = &ipv6_hdr(skb)->saddr;
	} else {
		*port = sh->dest;
		from = &ipv6_hdr(skb)->daddr;
	}
	ipv6_addr_copy(&addr->v6.sin6_addr, from);
}