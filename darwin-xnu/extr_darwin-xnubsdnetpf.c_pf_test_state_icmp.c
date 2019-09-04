#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_9__ ;
typedef  struct TYPE_39__   TYPE_8__ ;
typedef  struct TYPE_38__   TYPE_7__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_24__ ;
typedef  struct TYPE_31__   TYPE_1__ ;
typedef  struct TYPE_30__   TYPE_16__ ;
typedef  struct TYPE_29__   TYPE_14__ ;
typedef  struct TYPE_28__   TYPE_13__ ;
typedef  struct TYPE_27__   TYPE_12__ ;
typedef  struct TYPE_26__   TYPE_11__ ;
typedef  struct TYPE_25__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uh ;
typedef  int /*<<< orphan*/  u_short ;
typedef  int u_int8_t ;
typedef  int u_int32_t ;
typedef  void* u_int16_t ;
struct udphdr {int /*<<< orphan*/  uh_sum; void* uh_dport; void* uh_sport; void* th_dport; void* th_sport; int /*<<< orphan*/  th_sum; int /*<<< orphan*/  th_seq; } ;
struct tcphdr {int /*<<< orphan*/  uh_sum; void* uh_dport; void* uh_sport; void* th_dport; void* th_sport; int /*<<< orphan*/  th_sum; int /*<<< orphan*/  th_seq; } ;
struct pfi_kif {int dummy; } ;
struct pf_state_peer {int wscale; int seqdiff; int seqhi; int seqlo; int /*<<< orphan*/  max_win; } ;
struct TYPE_26__ {void* port; } ;
struct TYPE_32__ {int /*<<< orphan*/ * addr32; } ;
struct TYPE_27__ {TYPE_11__ xport; TYPE_24__ addr; } ;
struct TYPE_40__ {void* port; } ;
struct TYPE_25__ {TYPE_9__ xport; TYPE_24__ addr; } ;
struct TYPE_38__ {void* port; } ;
struct TYPE_39__ {TYPE_7__ xport; TYPE_24__ addr; } ;
struct TYPE_36__ {void* port; } ;
struct TYPE_37__ {TYPE_5__ xport; TYPE_24__ addr; } ;
struct pf_state_key_cmp {int proto; scalar_t__ af_lan; scalar_t__ af_gwy; TYPE_12__ ext_lan; TYPE_10__ lan; TYPE_8__ gwy; TYPE_6__ ext_gwy; int /*<<< orphan*/  proto_variant; struct pf_app_state* app_state; } ;
struct in_addr {int dummy; } ;
struct pf_addr {struct in_addr v4addr; } ;
struct TYPE_35__ {int /*<<< orphan*/  port; } ;
struct pf_state_host {struct pf_addr addr; TYPE_4__ xport; } ;
struct pf_state_key {scalar_t__ af_lan; scalar_t__ af_gwy; int direction; struct pf_state_host gwy; struct pf_state_host lan; struct pf_state_host ext_gwy; struct pf_state_host ext_lan; int /*<<< orphan*/  flowhash; int /*<<< orphan*/  flowsrc; } ;
struct pf_state {struct pf_state_key* state_key; struct pf_state_peer dst; struct pf_state_peer src; int /*<<< orphan*/  timeout; int /*<<< orphan*/  expire; } ;
struct TYPE_34__ {struct udphdr* icmp6; TYPE_14__* icmp; } ;
struct pf_pdesc {int off; int proto; scalar_t__ af; scalar_t__ naf; int pktflags; int /*<<< orphan*/  ip_sum; struct pf_addr* dst; struct pf_addr* src; TYPE_24__ naddr; TYPE_24__ ndaddr; TYPE_3__ hdr; int /*<<< orphan*/  flowhash; int /*<<< orphan*/  flowsrc; } ;
struct pf_ike_hdr {int /*<<< orphan*/  initiator_cookie; } ;
struct TYPE_31__ {int /*<<< orphan*/  cookie; } ;
struct TYPE_33__ {TYPE_1__ ike; } ;
struct pf_app_state {TYPE_2__ u; void* compare_ext_gwy; void* compare_lan_ext; } ;
struct icmp6_hdr {int dummy; } ;
typedef  int /*<<< orphan*/  pd2 ;
struct TYPE_28__ {int /*<<< orphan*/  pb_packet_len; } ;
typedef  TYPE_13__ pbuf_t ;
typedef  int /*<<< orphan*/  ike ;
struct TYPE_30__ {int /*<<< orphan*/  debug; } ;
struct TYPE_29__ {int icmp_code; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  DPFPRINTF (int /*<<< orphan*/ ,char*) ; 
 void* IPPROTO_ICMP ; 
 void* IPPROTO_ICMPV6 ; 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int /*<<< orphan*/  PFRES_BADSTATE ; 
 int /*<<< orphan*/  PFTM_ICMP_ERROR_REPLY ; 
 int /*<<< orphan*/  PF_ACPY (TYPE_24__*,struct pf_addr*,scalar_t__) ; 
 int /*<<< orphan*/  PF_DEBUG_MISC ; 
 int PF_DROP ; 
 int /*<<< orphan*/  PF_EXTFILTER_AD ; 
 int /*<<< orphan*/  PF_EXTFILTER_APD ; 
 int /*<<< orphan*/  PF_EXTFILTER_EI ; 
 int /*<<< orphan*/  PF_IKE_PORT ; 
 int PF_IN ; 
 int PF_OUT ; 
 int PF_PASS ; 
 int PF_WSCALE_FLAG ; 
 int PF_WSCALE_MASK ; 
 int PKTF_FLOW_ADV ; 
 int PKTF_FLOW_ID ; 
 int /*<<< orphan*/  REASON_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEQ_GEQ (int,int) ; 
 int /*<<< orphan*/  STATE_LOOKUP () ; 
 scalar_t__ STATE_TRANSLATE (struct pf_state_key*) ; 
 int TCP_MAX_WINSHIFT ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct in_addr*,int) ; 
 int /*<<< orphan*/  memset (struct pf_pdesc*,int /*<<< orphan*/ ,int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (void*) ; 
 int /*<<< orphan*/  pbuf_copy_back (TYPE_13__*,int,int,struct udphdr*) ; 
 int /*<<< orphan*/  pbuf_copy_data (TYPE_13__*,int,size_t,struct pf_ike_hdr*) ; 
 int /*<<< orphan*/  pf_change_a (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_change_ap (int,int /*<<< orphan*/ *,struct pf_addr*,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pf_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_change_icmp (struct pf_addr*,void**,struct pf_addr*,struct pf_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  pf_change_icmp_af (TYPE_13__*,int,struct pf_pdesc*,struct pf_pdesc*,struct pf_addr*,struct pf_addr*,scalar_t__,scalar_t__) ; 
 struct pf_state* pf_find_state (struct pfi_kif*,struct pf_state_key_cmp*,int) ; 
 void* pf_ike_compare ; 
 int /*<<< orphan*/ * pf_lazy_makewritable (struct pf_pdesc*,TYPE_13__*,int) ; 
 int pf_nat64_ipv4 (TYPE_13__*,int,struct pf_pdesc*) ; 
 int pf_nat64_ipv6 (TYPE_13__*,int,struct pf_pdesc*) ; 
 int /*<<< orphan*/  pf_print_host (struct pf_addr*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pf_print_state (struct pf_state*) ; 
 int /*<<< orphan*/  pf_pull_hdr (TYPE_13__*,int,struct udphdr*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pf_state_lookup_aux (struct pf_state**,struct pfi_kif*,int,int*) ; 
 TYPE_16__ pf_status ; 
 int /*<<< orphan*/  pf_time_second () ; 
 int /*<<< orphan*/  pf_translate_icmp_af (scalar_t__,TYPE_14__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
pf_test_state_icmp(struct pf_state **state, int direction, struct pfi_kif *kif,
    pbuf_t *pbuf, int off, void *h, struct pf_pdesc *pd, u_short *reason)
{
#pragma unused(h)
	struct pf_addr	*saddr = pd->src, *daddr = pd->dst;
	struct in_addr	srcv4_inaddr = saddr->v4addr;
	u_int16_t	 icmpid = 0, *icmpsum = NULL;
	u_int8_t	 icmptype = 0;
	int		 state_icmp = 0;
	struct pf_state_key_cmp key;
	struct pf_state_key	*sk;

	struct pf_app_state as;
	key.app_state = 0;

	pd->off = off;

	switch (pd->proto) {
#if INET
	case IPPROTO_ICMP:
		icmptype = pd->hdr.icmp->icmp_type;
		icmpid = pd->hdr.icmp->icmp_id;
		icmpsum = &pd->hdr.icmp->icmp_cksum;

		if (ICMP_ERRORTYPE(icmptype))
			state_icmp++;
		break;
#endif /* INET */
#if INET6
	case IPPROTO_ICMPV6:
		icmptype = pd->hdr.icmp6->icmp6_type;
		icmpid = pd->hdr.icmp6->icmp6_id;
		icmpsum = &pd->hdr.icmp6->icmp6_cksum;

		if (ICMP6_ERRORTYPE(icmptype))
			state_icmp++;
		break;
#endif /* INET6 */
	}

	if (!state_icmp) {

		/*
		 * ICMP query/reply message not related to a TCP/UDP packet.
		 * Search for an ICMP state.
		 */
		/*
		 * NAT64 requires protocol translation  between ICMPv4
		 * and ICMPv6. TCP and UDP do not require protocol
		 * translation. To avoid adding complexity just to
		 * handle ICMP(v4addr/v6addr), we always lookup  for
		 * proto = IPPROTO_ICMP on both LAN and WAN side
		 */
		key.proto = IPPROTO_ICMP;
		key.af_lan = key.af_gwy = pd->af;

		PF_ACPY(&key.ext_gwy.addr, pd->src, key.af_gwy);
		PF_ACPY(&key.gwy.addr, pd->dst, key.af_gwy);
		key.ext_gwy.xport.port = 0;
		key.gwy.xport.port = icmpid;

		PF_ACPY(&key.lan.addr, pd->src, key.af_lan);
		PF_ACPY(&key.ext_lan.addr, pd->dst, key.af_lan);
		key.lan.xport.port = icmpid;
		key.ext_lan.xport.port = 0;

		STATE_LOOKUP();

		sk = (*state)->state_key;
		(*state)->expire = pf_time_second();
		(*state)->timeout = PFTM_ICMP_ERROR_REPLY;

		/* translate source/destination address, if necessary */
		if (STATE_TRANSLATE(sk)) {
			pd->naf = (pd->af == sk->af_lan) ?
						sk->af_gwy : sk->af_lan;
			if (direction == PF_OUT) {
				switch (pd->af) {
#if INET
				case AF_INET:
					pf_change_a(&saddr->v4addr.s_addr,
					    pd->ip_sum,
					    sk->gwy.addr.v4addr.s_addr, 0);
					pd->hdr.icmp->icmp_cksum =
					    pf_cksum_fixup(
					    pd->hdr.icmp->icmp_cksum, icmpid,
					    sk->gwy.xport.port, 0);
					pd->hdr.icmp->icmp_id =
							sk->gwy.xport.port;
					if (pf_lazy_makewritable(pd, pbuf,
					    off + ICMP_MINLEN) == NULL)
						return (PF_DROP);
					pbuf_copy_back(pbuf, off, ICMP_MINLEN,
					    pd->hdr.icmp);
					break;
#endif /* INET */
#if INET6
				case AF_INET6:
					pf_change_a6(saddr,
					    &pd->hdr.icmp6->icmp6_cksum,
					    &sk->gwy.addr, 0);
					if (pf_lazy_makewritable(pd, NULL,
					    off + sizeof (struct icmp6_hdr)) ==
					    NULL)
						return (PF_DROP);
					pbuf_copy_back(pbuf, off,
					    sizeof (struct icmp6_hdr),
					    pd->hdr.icmp6);
					break;
#endif /* INET6 */
				}
			} else {
				switch (pd->af) {
#if INET
				case AF_INET:
					if (pd->naf != AF_INET) {
						if (pf_translate_icmp_af(
							AF_INET6, pd->hdr.icmp))
							return (PF_DROP);

						pd->proto = IPPROTO_ICMPV6;

					} else {

						pf_change_a(&daddr->v4addr.s_addr,
						pd->ip_sum,
						sk->lan.addr.v4addr.s_addr, 0);

						pd->hdr.icmp->icmp_cksum =
						pf_cksum_fixup(
						pd->hdr.icmp->icmp_cksum,
						icmpid, sk->lan.xport.port, 0);

						pd->hdr.icmp->icmp_id =
							sk->lan.xport.port;
					}

					if (pf_lazy_makewritable(pd, pbuf,
					    off + ICMP_MINLEN) == NULL)
						return (PF_DROP);
					pbuf_copy_back(pbuf, off, ICMP_MINLEN,
							pd->hdr.icmp);
					if (sk->af_lan != sk->af_gwy)
						return (pf_do_nat64(sk, pd,
						    pbuf, off));
					break;
#endif /* INET */
#if INET6
				case AF_INET6:
					if (pd->naf != AF_INET6) {
						if (pf_translate_icmp_af(
							AF_INET, pd->hdr.icmp6))
							return (PF_DROP);

						pd->proto = IPPROTO_ICMP;
					} else {
						pf_change_a6(daddr,
						&pd->hdr.icmp6->icmp6_cksum,
						&sk->lan.addr, 0);
					}
					if (pf_lazy_makewritable(pd, pbuf,
					    off + sizeof (struct icmp6_hdr)) ==
					    NULL)
						return (PF_DROP);
					pbuf_copy_back(pbuf, off,
						sizeof (struct icmp6_hdr),
						pd->hdr.icmp6);
					if (sk->af_lan != sk->af_gwy)
						return (pf_do_nat64(sk, pd,
						    pbuf, off));
					break;
#endif /* INET6 */
				}
			}
		}

		return (PF_PASS);

	} else {
		/*
		 * ICMP error message in response to a TCP/UDP packet.
		 * Extract the inner TCP/UDP header and search for that state.
		 */
		struct pf_pdesc	pd2; /* For inner (original) header */
#if INET
		struct ip	h2;
#endif /* INET */
#if INET6
		struct ip6_hdr	h2_6;
		int		terminal = 0;
#endif /* INET6 */
		int		ipoff2 = 0;
		int		off2 = 0;

		memset(&pd2, 0, sizeof (pd2));

		pd2.af = pd->af;
		switch (pd->af) {
#if INET
		case AF_INET:
			/* offset of h2 in mbuf chain */
			ipoff2 = off + ICMP_MINLEN;

			if (!pf_pull_hdr(pbuf, ipoff2, &h2, sizeof (h2),
			    NULL, reason, pd2.af)) {
				DPFPRINTF(PF_DEBUG_MISC,
				    ("pf: ICMP error message too short "
				    "(ip)\n"));
				return (PF_DROP);
			}
			/*
			 * ICMP error messages don't refer to non-first
			 * fragments
			 */
			if (h2.ip_off & htons(IP_OFFMASK)) {
				REASON_SET(reason, PFRES_FRAG);
				return (PF_DROP);
			}

			/* offset of protocol header that follows h2 */
			off2 = ipoff2 + (h2.ip_hl << 2);
			/* TODO */
			pd2.off = ipoff2 + (h2.ip_hl << 2);

			pd2.proto = h2.ip_p;
			pd2.src = (struct pf_addr *)&h2.ip_src;
			pd2.dst = (struct pf_addr *)&h2.ip_dst;
			pd2.ip_sum = &h2.ip_sum;
			break;
#endif /* INET */
#if INET6
		case AF_INET6:
			ipoff2 = off + sizeof (struct icmp6_hdr);

			if (!pf_pull_hdr(pbuf, ipoff2, &h2_6, sizeof (h2_6),
			    NULL, reason, pd2.af)) {
				DPFPRINTF(PF_DEBUG_MISC,
				    ("pf: ICMP error message too short "
				    "(ip6)\n"));
				return (PF_DROP);
			}
			pd2.proto = h2_6.ip6_nxt;
			pd2.src = (struct pf_addr *)(uintptr_t)&h2_6.ip6_src;
			pd2.dst = (struct pf_addr *)(uintptr_t)&h2_6.ip6_dst;
			pd2.ip_sum = NULL;
			off2 = ipoff2 + sizeof (h2_6);
			do {
				switch (pd2.proto) {
				case IPPROTO_FRAGMENT:
					/*
					 * ICMPv6 error messages for
					 * non-first fragments
					 */
					REASON_SET(reason, PFRES_FRAG);
					return (PF_DROP);
				case IPPROTO_AH:
				case IPPROTO_HOPOPTS:
				case IPPROTO_ROUTING:
				case IPPROTO_DSTOPTS: {
					/* get next header and header length */
					struct ip6_ext opt6;

					if (!pf_pull_hdr(pbuf, off2, &opt6,
					    sizeof (opt6), NULL, reason,
					    pd2.af)) {
						DPFPRINTF(PF_DEBUG_MISC,
						    ("pf: ICMPv6 short opt\n"));
						return (PF_DROP);
					}
					if (pd2.proto == IPPROTO_AH)
						off2 += (opt6.ip6e_len + 2) * 4;
					else
						off2 += (opt6.ip6e_len + 1) * 8;
					pd2.proto = opt6.ip6e_nxt;
					/* goto the next header */
					break;
				}
				default:
					terminal++;
					break;
				}
			} while (!terminal);
			/* TODO */
			pd2.off = ipoff2;
			break;
#endif /* INET6 */
		}

		switch (pd2.proto) {
		case IPPROTO_TCP: {
			struct tcphdr		 th;
			u_int32_t		 seq;
			struct pf_state_peer	*src, *dst;
			u_int8_t		 dws;
			int			 copyback = 0;

			/*
			 * Only the first 8 bytes of the TCP header can be
			 * expected. Don't access any TCP header fields after
			 * th_seq, an ackskew test is not possible.
			 */
			if (!pf_pull_hdr(pbuf, off2, &th, 8, NULL, reason,
			    pd2.af)) {
				DPFPRINTF(PF_DEBUG_MISC,
				    ("pf: ICMP error message too short "
				    "(tcp)\n"));
				return (PF_DROP);
			}

			key.proto = IPPROTO_TCP;
			key.af_gwy = pd2.af;
			PF_ACPY(&key.ext_gwy.addr, pd2.dst, key.af_gwy);
			PF_ACPY(&key.gwy.addr, pd2.src, key.af_gwy);
			key.ext_gwy.xport.port = th.th_dport;
			key.gwy.xport.port = th.th_sport;

			key.af_lan = pd2.af;
			PF_ACPY(&key.lan.addr, pd2.dst, key.af_lan);
			PF_ACPY(&key.ext_lan.addr, pd2.src, key.af_lan);
			key.lan.xport.port = th.th_dport;
			key.ext_lan.xport.port = th.th_sport;

			STATE_LOOKUP();

			sk = (*state)->state_key;
			if ((direction == sk->direction) &&
			    ((sk->af_lan == sk->af_gwy) ||
			     (pd2.af == sk->af_lan))) {
				src = &(*state)->dst;
				dst = &(*state)->src;
			} else {
				src = &(*state)->src;
				dst = &(*state)->dst;
			}

			if (src->wscale && (dst->wscale & PF_WSCALE_FLAG))
				dws = dst->wscale & PF_WSCALE_MASK;
			else
				dws = TCP_MAX_WINSHIFT;

			/* Demodulate sequence number */
			seq = ntohl(th.th_seq) - src->seqdiff;
			if (src->seqdiff) {
				pf_change_a(&th.th_seq, icmpsum,
				    htonl(seq), 0);
				copyback = 1;
			}

			if (!SEQ_GEQ(src->seqhi, seq) ||
			    !SEQ_GEQ(seq,
			    src->seqlo - ((u_int32_t)dst->max_win << dws))) {
				if (pf_status.debug >= PF_DEBUG_MISC) {
					printf("pf: BAD ICMP %d:%d ",
					    icmptype, pd->hdr.icmp->icmp_code);
					pf_print_host(pd->src, 0, pd->af);
					printf(" -> ");
					pf_print_host(pd->dst, 0, pd->af);
					printf(" state: ");
					pf_print_state(*state);
					printf(" seq=%u\n", seq);
				}
				REASON_SET(reason, PFRES_BADSTATE);
				return (PF_DROP);
			}

			pd->naf = pd2.naf = (pd2.af == sk->af_lan) ?
						sk->af_gwy : sk->af_lan;

			if (STATE_TRANSLATE(sk)) {
				/* NAT64 case */
				if (sk->af_lan != sk->af_gwy) {
					struct pf_state_host *saddr2, *daddr2;

					if (pd2.naf == sk->af_lan) {
						saddr2 = &sk->lan;
						daddr2 = &sk->ext_lan;
					} else {
						saddr2 = &sk->ext_gwy;
						daddr2 = &sk->gwy;
					}

					/* translate ICMP message types and codes */
					if (pf_translate_icmp_af(pd->naf,
						pd->hdr.icmp))
						return (PF_DROP);

					if (pf_lazy_makewritable(pd, pbuf,
					    off2 + 8) == NULL)
						return (PF_DROP);

					pbuf_copy_back(pbuf, pd->off,
						sizeof(struct icmp6_hdr),
						pd->hdr.icmp6);

					/*
					 * translate inner ip header within the
					 * ICMP message
					 */
					if (pf_change_icmp_af(pbuf, ipoff2, pd,
					    &pd2, &saddr2->addr, &daddr2->addr,
					    pd->af, pd->naf))
						return (PF_DROP);

					if (pd->naf == AF_INET)
						pd->proto = IPPROTO_ICMP;
					else
						pd->proto = IPPROTO_ICMPV6;

					/*
					 * translate inner tcp header within
					 * the ICMP message
					 */
					pf_change_ap(direction, NULL, pd2.src,
						&th.th_sport, pd2.ip_sum,
						&th.th_sum, &daddr2->addr,
						saddr2->xport.port, 0, pd2.af,
						pd2.naf, 0);

					pf_change_ap(direction, NULL, pd2.dst,
						&th.th_dport, pd2.ip_sum,
						&th.th_sum, &saddr2->addr,
						daddr2->xport.port, 0, pd2.af,
						pd2.naf, 0);

					pbuf_copy_back(pbuf, pd2.off, 8, &th);

					/* translate outer ip header */
					PF_ACPY(&pd->naddr, &daddr2->addr,
						pd->naf);
					PF_ACPY(&pd->ndaddr, &saddr2->addr,
						pd->naf);
					if (pd->af == AF_INET) {
						memcpy(&pd->naddr.addr32[3],
						    &srcv4_inaddr,
						    sizeof(pd->naddr.addr32[3]));
						return (pf_nat64_ipv4(pbuf, off,
									pd));
					} else {
						return (pf_nat64_ipv6(pbuf, off,
									pd));
					}
				}
				if (direction == PF_IN) {
					pf_change_icmp(pd2.src, &th.th_sport,
					    daddr, &sk->lan.addr,
					    sk->lan.xport.port, NULL,
					    pd2.ip_sum, icmpsum,
					    pd->ip_sum, 0, pd2.af);
				} else {
					pf_change_icmp(pd2.dst, &th.th_dport,
					    saddr, &sk->gwy.addr,
					    sk->gwy.xport.port, NULL,
					    pd2.ip_sum, icmpsum,
					    pd->ip_sum, 0, pd2.af);
				}
				copyback = 1;
			}

			if (copyback) {
				if (pf_lazy_makewritable(pd, pbuf, off2 + 8) ==
				    NULL)
					return (PF_DROP);
				switch (pd2.af) {
#if INET
				case AF_INET:
					pbuf_copy_back(pbuf, off, ICMP_MINLEN,
					    pd->hdr.icmp);
					pbuf_copy_back(pbuf, ipoff2, sizeof(h2),
					    &h2);
					break;
#endif /* INET */
#if INET6
				case AF_INET6:
					pbuf_copy_back(pbuf, off,
					    sizeof (struct icmp6_hdr),
					    pd->hdr.icmp6);
					pbuf_copy_back(pbuf, ipoff2,
					    sizeof (h2_6), &h2_6);
					break;
#endif /* INET6 */
				}
				pbuf_copy_back(pbuf, off2, 8, &th);
			}

			return (PF_PASS);
		}
		case IPPROTO_UDP: {
			struct udphdr uh;
			int dx, action;
			if (!pf_pull_hdr(pbuf, off2, &uh, sizeof (uh),
			    NULL, reason, pd2.af)) {
				DPFPRINTF(PF_DEBUG_MISC,
				    ("pf: ICMP error message too short "
				    "(udp)\n"));
				return (PF_DROP);
			}

			key.af_gwy = pd2.af;
			PF_ACPY(&key.ext_gwy.addr, pd2.dst, key.af_gwy);
			PF_ACPY(&key.gwy.addr, pd2.src, key.af_gwy);
			key.ext_gwy.xport.port = uh.uh_dport;
			key.gwy.xport.port = uh.uh_sport;

			key.af_lan = pd2.af;
			PF_ACPY(&key.lan.addr, pd2.dst, key.af_lan);
			PF_ACPY(&key.ext_lan.addr, pd2.src, key.af_lan);
			key.lan.xport.port = uh.uh_dport;
			key.ext_lan.xport.port = uh.uh_sport;

			key.proto = IPPROTO_UDP;
			key.proto_variant = PF_EXTFILTER_APD;
			dx = direction;

			if (ntohs(uh.uh_sport) == PF_IKE_PORT &&
			    ntohs(uh.uh_dport) == PF_IKE_PORT) {
				struct pf_ike_hdr ike;
				size_t plen = pbuf->pb_packet_len - off2 -
				    sizeof (uh);
				if (direction == PF_IN &&
				    plen < 8 /* PF_IKE_PACKET_MINSIZE */) {
					DPFPRINTF(PF_DEBUG_MISC, ("pf: "
					    "ICMP error, embedded IKE message "
					    "too small.\n"));
					return (PF_DROP);
				}

				if (plen > sizeof (ike))
					plen = sizeof (ike);
				pbuf_copy_data(pbuf, off + sizeof (uh), plen,
				    &ike);

				key.app_state = &as;
				as.compare_lan_ext = pf_ike_compare;
				as.compare_ext_gwy = pf_ike_compare;
				as.u.ike.cookie = ike.initiator_cookie;
			}

			*state = pf_find_state(kif, &key, dx);

			if (key.app_state && *state == 0) {
				key.app_state = 0;
				*state = pf_find_state(kif, &key, dx);
			}

			if (*state == 0) {
				key.proto_variant = PF_EXTFILTER_AD;
				*state = pf_find_state(kif, &key, dx);
			}

			if (*state == 0) {
				key.proto_variant = PF_EXTFILTER_EI;
				*state = pf_find_state(kif, &key, dx);
			}

			/* similar to STATE_LOOKUP() */
			if (*state != NULL && pd != NULL &&
			    !(pd->pktflags & PKTF_FLOW_ID)) {
				pd->flowsrc = (*state)->state_key->flowsrc;
				pd->flowhash = (*state)->state_key->flowhash;
				if (pd->flowhash != 0) {
					pd->pktflags |= PKTF_FLOW_ID;
					pd->pktflags &= ~PKTF_FLOW_ADV;
				}
			}

			if (pf_state_lookup_aux(state, kif, direction, &action))
				return (action);

			sk = (*state)->state_key;
			pd->naf = pd2.naf = (pd2.af == sk->af_lan) ?
						sk->af_gwy : sk->af_lan;

			if (STATE_TRANSLATE(sk)) {
				/* NAT64 case */
				if (sk->af_lan != sk->af_gwy) {
					struct pf_state_host *saddr2, *daddr2;

					if (pd2.naf == sk->af_lan) {
						saddr2 = &sk->lan;
						daddr2 = &sk->ext_lan;
					} else {
						saddr2 = &sk->ext_gwy;
						daddr2 = &sk->gwy;
					}

					/* translate ICMP message */
					if (pf_translate_icmp_af(pd->naf,
						pd->hdr.icmp))
						return (PF_DROP);
					if (pf_lazy_makewritable(pd, pbuf,
					    off2 + 8) == NULL)
						return (PF_DROP);

					pbuf_copy_back(pbuf, pd->off,
						sizeof(struct icmp6_hdr),
						pd->hdr.icmp6);

					/*
					 * translate inner ip header within the
					 * ICMP message
					 */
					if (pf_change_icmp_af(pbuf, ipoff2, pd,
					    &pd2, &saddr2->addr, &daddr2->addr,
					    pd->af, pd->naf))
						return (PF_DROP);

					if (pd->naf == AF_INET)
						pd->proto = IPPROTO_ICMP;
					else
						pd->proto = IPPROTO_ICMPV6;

					/*
					 * translate inner udp header within
					 * the ICMP message
					 */
					pf_change_ap(direction, NULL, pd2.src,
						&uh.uh_sport, pd2.ip_sum,
						&uh.uh_sum, &daddr2->addr,
						saddr2->xport.port, 0, pd2.af,
						pd2.naf, 0);

					pf_change_ap(direction, NULL, pd2.dst,
						&uh.uh_dport, pd2.ip_sum,
						&uh.uh_sum, &saddr2->addr,
						daddr2->xport.port, 0, pd2.af,
						pd2.naf, 0);

					pbuf_copy_back(pbuf, pd2.off,
					    sizeof(uh), &uh);

					/* translate outer ip header */
					PF_ACPY(&pd->naddr, &daddr2->addr,
						pd->naf);
					PF_ACPY(&pd->ndaddr, &saddr2->addr,
						pd->naf);
					if (pd->af == AF_INET) {
						memcpy(&pd->naddr.addr32[3],
						    &srcv4_inaddr,
						    sizeof(pd->naddr.addr32[3]));
						return (pf_nat64_ipv4(pbuf, off,
									pd));
					} else {
						return (pf_nat64_ipv6(pbuf, off,
									pd));
					}
				}
				if (direction == PF_IN) {
					pf_change_icmp(pd2.src, &uh.uh_sport,
					    daddr, &sk->lan.addr,
					    sk->lan.xport.port, &uh.uh_sum,
					    pd2.ip_sum, icmpsum,
					    pd->ip_sum, 1, pd2.af);
				} else {
					pf_change_icmp(pd2.dst, &uh.uh_dport,
					    saddr, &sk->gwy.addr,
					    sk->gwy.xport.port, &uh.uh_sum,
					    pd2.ip_sum, icmpsum,
					    pd->ip_sum, 1, pd2.af);
				}
				if (pf_lazy_makewritable(pd, pbuf,
				    off2 + sizeof (uh)) == NULL)
					return (PF_DROP);
				switch (pd2.af) {
#if INET
				case AF_INET:
					pbuf_copy_back(pbuf, off, ICMP_MINLEN,
					    pd->hdr.icmp);
					pbuf_copy_back(pbuf, ipoff2,
					    sizeof (h2), &h2);
					break;
#endif /* INET */
#if INET6
				case AF_INET6:
					pbuf_copy_back(pbuf, off,
					    sizeof (struct icmp6_hdr),
					    pd->hdr.icmp6);
					pbuf_copy_back(pbuf, ipoff2,
					    sizeof (h2_6), &h2_6);
					break;
#endif /* INET6 */
				}
				pbuf_copy_back(pbuf, off2, sizeof (uh), &uh);
			}

			return (PF_PASS);
		}
#if INET
		case IPPROTO_ICMP: {
			struct icmp		iih;

			if (!pf_pull_hdr(pbuf, off2, &iih, ICMP_MINLEN,
			    NULL, reason, pd2.af)) {
				DPFPRINTF(PF_DEBUG_MISC,
				    ("pf: ICMP error message too short i"
				    "(icmp)\n"));
				return (PF_DROP);
			}

			key.proto = IPPROTO_ICMP;
			if (direction == PF_IN)	{
				key.af_gwy = pd2.af;
				PF_ACPY(&key.ext_gwy.addr, pd2.dst, key.af_gwy);
				PF_ACPY(&key.gwy.addr, pd2.src, key.af_gwy);
				key.ext_gwy.xport.port = 0;
				key.gwy.xport.port = iih.icmp_id;
			} else {
				key.af_lan = pd2.af;
				PF_ACPY(&key.lan.addr, pd2.dst, key.af_lan);
				PF_ACPY(&key.ext_lan.addr, pd2.src, key.af_lan);
				key.lan.xport.port = iih.icmp_id;
				key.ext_lan.xport.port = 0;
			}

			STATE_LOOKUP();

			sk = (*state)->state_key;
			if (STATE_TRANSLATE(sk)) {
				if (direction == PF_IN) {
					pf_change_icmp(pd2.src, &iih.icmp_id,
					    daddr, &sk->lan.addr,
					    sk->lan.xport.port, NULL,
					    pd2.ip_sum, icmpsum,
					    pd->ip_sum, 0, AF_INET);
				} else {
					pf_change_icmp(pd2.dst, &iih.icmp_id,
					    saddr, &sk->gwy.addr,
					    sk->gwy.xport.port, NULL,
					    pd2.ip_sum, icmpsum,
					    pd->ip_sum, 0, AF_INET);
				}
				if (pf_lazy_makewritable(pd, pbuf,
				     off2 + ICMP_MINLEN) == NULL)
					return (PF_DROP);
				pbuf_copy_back(pbuf, off, ICMP_MINLEN,
				    pd->hdr.icmp);
				pbuf_copy_back(pbuf, ipoff2, sizeof (h2), &h2);
				pbuf_copy_back(pbuf, off2, ICMP_MINLEN, &iih);
			}

			return (PF_PASS);
		}
#endif /* INET */
#if INET6
		case IPPROTO_ICMPV6: {
			struct icmp6_hdr	iih;

			if (!pf_pull_hdr(pbuf, off2, &iih,
			    sizeof (struct icmp6_hdr), NULL, reason, pd2.af)) {
				DPFPRINTF(PF_DEBUG_MISC,
				    ("pf: ICMP error message too short "
				    "(icmp6)\n"));
				return (PF_DROP);
			}

			key.proto = IPPROTO_ICMPV6;
			if (direction == PF_IN)	{
				key.af_gwy = pd2.af;
				PF_ACPY(&key.ext_gwy.addr, pd2.dst, key.af_gwy);
				PF_ACPY(&key.gwy.addr, pd2.src, key.af_gwy);
				key.ext_gwy.xport.port = 0;
				key.gwy.xport.port = iih.icmp6_id;
			} else {
				key.af_lan = pd2.af;
				PF_ACPY(&key.lan.addr, pd2.dst, key.af_lan);
				PF_ACPY(&key.ext_lan.addr, pd2.src, key.af_lan);
				key.lan.xport.port = iih.icmp6_id;
				key.ext_lan.xport.port = 0;
			}

			STATE_LOOKUP();

			sk = (*state)->state_key;
			if (STATE_TRANSLATE(sk)) {
				if (direction == PF_IN) {
					pf_change_icmp(pd2.src, &iih.icmp6_id,
					    daddr, &sk->lan.addr,
					    sk->lan.xport.port, NULL,
					    pd2.ip_sum, icmpsum,
					    pd->ip_sum, 0, AF_INET6);
				} else {
					pf_change_icmp(pd2.dst, &iih.icmp6_id,
					    saddr, &sk->gwy.addr,
					    sk->gwy.xport.port, NULL,
					    pd2.ip_sum, icmpsum,
					    pd->ip_sum, 0, AF_INET6);
				}
				if (pf_lazy_makewritable(pd, pbuf, off2 +
				    sizeof (struct icmp6_hdr)) == NULL)
					return (PF_DROP);
				pbuf_copy_back(pbuf, off,
				    sizeof (struct icmp6_hdr), pd->hdr.icmp6);
				pbuf_copy_back(pbuf, ipoff2, sizeof (h2_6),
				    &h2_6);
				pbuf_copy_back(pbuf, off2,
				    sizeof (struct icmp6_hdr), &iih);
			}

			return (PF_PASS);
		}
#endif /* INET6 */
		default: {
			key.proto = pd2.proto;
			if (direction == PF_IN)	{
				key.af_gwy = pd2.af;
				PF_ACPY(&key.ext_gwy.addr, pd2.dst, key.af_gwy);
				PF_ACPY(&key.gwy.addr, pd2.src, key.af_gwy);
				key.ext_gwy.xport.port = 0;
				key.gwy.xport.port = 0;
			} else {
				key.af_lan = pd2.af;
				PF_ACPY(&key.lan.addr, pd2.dst, key.af_lan);
				PF_ACPY(&key.ext_lan.addr, pd2.src, key.af_lan);
				key.lan.xport.port = 0;
				key.ext_lan.xport.port = 0;
			}

			STATE_LOOKUP();

			sk = (*state)->state_key;
			if (STATE_TRANSLATE(sk)) {
				if (direction == PF_IN) {
					pf_change_icmp(pd2.src, NULL, daddr,
						&sk->lan.addr, 0, NULL,
						pd2.ip_sum, icmpsum,
						pd->ip_sum, 0, pd2.af);
				} else {
					pf_change_icmp(pd2.dst, NULL, saddr,
						&sk->gwy.addr, 0, NULL,
						pd2.ip_sum, icmpsum,
						pd->ip_sum, 0, pd2.af);
				}
				switch (pd2.af) {
#if INET
				case AF_INET:
					if (pf_lazy_makewritable(pd, pbuf,
					    ipoff2 + sizeof (h2)) == NULL)
						return (PF_DROP);
					/*
					 * <XXXSCW>
					 * Xnu was missing the following...
					 */
					pbuf_copy_back(pbuf, off, ICMP_MINLEN,
					    pd->hdr.icmp);
					pbuf_copy_back(pbuf, ipoff2,
					    sizeof(h2), &h2);
					break;
					/*
					 * </XXXSCW>
					 */
#endif /* INET */
#if INET6
				case AF_INET6:
					if (pf_lazy_makewritable(pd, pbuf,
					    ipoff2 + sizeof (h2_6)) == NULL)
						return (PF_DROP);
					pbuf_copy_back(pbuf, off,
					    sizeof (struct icmp6_hdr),
					    pd->hdr.icmp6);
					pbuf_copy_back(pbuf, ipoff2,
					    sizeof (h2_6), &h2_6);
					break;
#endif /* INET6 */
				}
			}

			return (PF_PASS);
		}
		}
	}
}