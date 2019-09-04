#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  v4addr; } ;
struct TYPE_9__ {int /*<<< orphan*/  v4addr; } ;
struct pf_pdesc {int tos; int tot_len; scalar_t__ proto; TYPE_2__ ndaddr; TYPE_1__ naddr; int /*<<< orphan*/  ttl; } ;
struct mbuf {int dummy; } ;
struct ip {int ip_v; int ip_hl; int ip_tos; scalar_t__ ip_p; void* ip_len; void* ip_sum; int /*<<< orphan*/  ip_dst; int /*<<< orphan*/  ip_src; int /*<<< orphan*/  ip_ttl; void* ip_off; scalar_t__ ip_id; } ;
struct icmp {void* icmp_cksum; } ;
struct TYPE_11__ {int /*<<< orphan*/ * pb_ifp; } ;
typedef  TYPE_3__ pbuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ICMP_MINLEN ; 
 scalar_t__ IPPROTO_ICMP ; 
 int IP_DF ; 
 int PF_DROP ; 
 int PF_NAT64 ; 
 int /*<<< orphan*/  TRUE ; 
 int htonl (int) ; 
 void* htons (int) ; 
 int /*<<< orphan*/  ip_input (struct mbuf*) ; 
 int ntohs (void*) ; 
 scalar_t__ pbuf_contig_segment (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 void* pbuf_inet_cksum (TYPE_3__*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ pbuf_resize_segment (TYPE_3__*,int /*<<< orphan*/ ,int,int) ; 
 struct mbuf* pbuf_to_mbuf (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pf_nat64_ipv6(pbuf_t *pbuf, int off, struct pf_pdesc *pd)
{
	struct ip		*ip4;
	struct mbuf *m;

	/*
	 * ip_input asserts for rcvif to be not NULL
	 * That may not be true for two corner cases
	 * 1. If for some reason a local app sends DNS
	 * AAAA query to local host
	 * 2. If IPv6 stack in kernel internally generates a
	 * message destined for a synthesized IPv6 end-point.
	 */
	if (pbuf->pb_ifp == NULL)
		return (PF_DROP);

	ip4 = (struct ip *)pbuf_resize_segment(pbuf, 0, off, sizeof(*ip4));
	if (ip4 == NULL)
		return (PF_DROP);

	ip4->ip_v   = 4;
	ip4->ip_hl  = 5;
	ip4->ip_tos = pd->tos & htonl(0x0ff00000);
	ip4->ip_len = htons(sizeof(*ip4) + (pd->tot_len - off));
	ip4->ip_id  = 0;
	ip4->ip_off = htons(IP_DF);
	ip4->ip_ttl = pd->ttl;
	ip4->ip_p   = pd->proto;
	ip4->ip_sum = 0;
	ip4->ip_src = pd->naddr.v4addr;
	ip4->ip_dst = pd->ndaddr.v4addr;
	ip4->ip_sum = pbuf_inet_cksum(pbuf, 0, 0, ip4->ip_hl << 2);

	/* recalculate icmp checksums */
	if (pd->proto == IPPROTO_ICMP) {
		struct icmp *icmp;
		int hlen = sizeof(*ip4);

		icmp = (struct icmp *)pbuf_contig_segment(pbuf, hlen,
		    ICMP_MINLEN);
		if (icmp == NULL)
			return (PF_DROP);

		icmp->icmp_cksum = 0;
		icmp->icmp_cksum = pbuf_inet_cksum(pbuf, 0, hlen,
						ntohs(ip4->ip_len) - hlen);
	}

	if ((m = pbuf_to_mbuf(pbuf, TRUE)) != NULL)
		ip_input(m);

	return (PF_NAT64);
}