#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int8_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct tcphdr {int th_flags; int th_off; } ;
struct pf_state_peer {TYPE_2__* scrub; } ;
struct pf_pdesc {int /*<<< orphan*/  af; } ;
struct ip6_hdr {int /*<<< orphan*/  ip6_hlim; int /*<<< orphan*/  ip_ttl; } ;
struct ip {int /*<<< orphan*/  ip6_hlim; int /*<<< orphan*/  ip_ttl; } ;
struct TYPE_6__ {struct ip6_hdr* pb_data; } ;
typedef  TYPE_1__ pbuf_t ;
struct TYPE_7__ {int /*<<< orphan*/  pfss_last; void* pfss_tsecr; void* pfss_tsval; void* pfss_tsval0; int /*<<< orphan*/  pfss_ts_mod; int /*<<< orphan*/  pfss_flags; int /*<<< orphan*/  pfss_ttl; } ;

/* Variables and functions */
#define  AF_INET 132 
#define  AF_INET6 131 
 int MAX (int,int) ; 
 int /*<<< orphan*/  PFSS_TIMESTAMP ; 
 int /*<<< orphan*/  PR_NOWAIT ; 
 int TCPOLEN_TIMESTAMP ; 
#define  TCPOPT_EOL 130 
#define  TCPOPT_NOP 129 
#define  TCPOPT_TIMESTAMP 128 
 int TH_SYN ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  getmicrouptime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ pf_pull_hdr (TYPE_1__*,int,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_state_scrub_pl ; 
 TYPE_2__* pool_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  random () ; 

int
pf_normalize_tcp_init(pbuf_t *pbuf, int off, struct pf_pdesc *pd,
    struct tcphdr *th, struct pf_state_peer *src, struct pf_state_peer *dst)
{
#pragma unused(dst)
	u_int32_t tsval, tsecr;
	u_int8_t hdr[60];
	u_int8_t *opt;

	VERIFY(src->scrub == NULL);

	src->scrub = pool_get(&pf_state_scrub_pl, PR_NOWAIT);
	if (src->scrub == NULL)
		return (1);
	bzero(src->scrub, sizeof (*src->scrub));

	switch (pd->af) {
#if INET
	case AF_INET: {
		struct ip *h = pbuf->pb_data;
		src->scrub->pfss_ttl = h->ip_ttl;
		break;
	}
#endif /* INET */
#if INET6
	case AF_INET6: {
		struct ip6_hdr *h = pbuf->pb_data;
		src->scrub->pfss_ttl = h->ip6_hlim;
		break;
	}
#endif /* INET6 */
	}


	/*
	 * All normalizations below are only begun if we see the start of
	 * the connections.  They must all set an enabled bit in pfss_flags
	 */
	if ((th->th_flags & TH_SYN) == 0)
		return (0);


	if (th->th_off > (sizeof (struct tcphdr) >> 2) && src->scrub &&
	    pf_pull_hdr(pbuf, off, hdr, th->th_off << 2, NULL, NULL, pd->af)) {
		/* Diddle with TCP options */
		int hlen;
		opt = hdr + sizeof (struct tcphdr);
		hlen = (th->th_off << 2) - sizeof (struct tcphdr);
		while (hlen >= TCPOLEN_TIMESTAMP) {
			switch (*opt) {
			case TCPOPT_EOL:	/* FALLTHROUGH */
			case TCPOPT_NOP:
				opt++;
				hlen--;
				break;
			case TCPOPT_TIMESTAMP:
				if (opt[1] >= TCPOLEN_TIMESTAMP) {
					src->scrub->pfss_flags |=
					    PFSS_TIMESTAMP;
					src->scrub->pfss_ts_mod =
					    htonl(random());

					/* note PFSS_PAWS not set yet */
					memcpy(&tsval, &opt[2],
					    sizeof (u_int32_t));
					memcpy(&tsecr, &opt[6],
					    sizeof (u_int32_t));
					src->scrub->pfss_tsval0 = ntohl(tsval);
					src->scrub->pfss_tsval = ntohl(tsval);
					src->scrub->pfss_tsecr = ntohl(tsecr);
					getmicrouptime(&src->scrub->pfss_last);
				}
				/* FALLTHROUGH */
			default:
				hlen -= MAX(opt[1], 2);
				opt += MAX(opt[1], 2);
				break;
			}
		}
	}

	return (0);
}