#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  union sctp_addr {int dummy; } sctp_addr ;
struct TYPE_8__ {int /*<<< orphan*/ * s6_addr32; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_scope_id; TYPE_3__ sin6_addr; int /*<<< orphan*/  sin6_port; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct sctphdr {int /*<<< orphan*/  source; } ;
struct sctp_ulpevent {int /*<<< orphan*/  iif; } ;
struct TYPE_9__ {int version; int /*<<< orphan*/  saddr; } ;
struct TYPE_7__ {int /*<<< orphan*/  saddr; } ;
struct TYPE_6__ {scalar_t__ v4mapped; } ;

/* Variables and functions */
 int IPV6_ADDR_LINKLOCAL ; 
 TYPE_5__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_addr_copy (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int ipv6_addr_type (TYPE_3__*) ; 
 TYPE_2__* ipv6_hdr (struct sk_buff*) ; 
 struct sctphdr* sctp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  sctp_inet6_msgname (char*,int*) ; 
 TYPE_1__* sctp_sk (int /*<<< orphan*/ ) ; 
 struct sctp_ulpevent* sctp_skb2event (struct sk_buff*) ; 
 int /*<<< orphan*/  sctp_v4_map_v6 (union sctp_addr*) ; 

__attribute__((used)) static void sctp_inet6_skb_msgname(struct sk_buff *skb, char *msgname,
				   int *addr_len)
{
	struct sctphdr *sh;
	struct sockaddr_in6 *sin6;

	if (msgname) {
		sctp_inet6_msgname(msgname, addr_len);
		sin6 = (struct sockaddr_in6 *)msgname;
		sh = sctp_hdr(skb);
		sin6->sin6_port = sh->source;

		/* Map ipv4 address into v4-mapped-on-v6 address. */
		if (sctp_sk(skb->sk)->v4mapped &&
		    ip_hdr(skb)->version == 4) {
			sctp_v4_map_v6((union sctp_addr *)sin6);
			sin6->sin6_addr.s6_addr32[3] = ip_hdr(skb)->saddr;
			return;
		}

		/* Otherwise, just copy the v6 address. */
		ipv6_addr_copy(&sin6->sin6_addr, &ipv6_hdr(skb)->saddr);
		if (ipv6_addr_type(&sin6->sin6_addr) & IPV6_ADDR_LINKLOCAL) {
			struct sctp_ulpevent *ev = sctp_skb2event(skb);
			sin6->sin6_scope_id = ev->iif;
		}
	}
}