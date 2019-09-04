#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_14__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_short ;
typedef  int u_int8_t ;
typedef  int u_int32_t ;
typedef  void* u_int16_t ;
struct tcphdr {int th_flags; int th_off; int /*<<< orphan*/  th_sum; int /*<<< orphan*/  th_dport; int /*<<< orphan*/  th_sport; int /*<<< orphan*/  th_ack; int /*<<< orphan*/  th_seq; int /*<<< orphan*/  th_win; } ;
struct pfi_kif {int /*<<< orphan*/ * pfik_ifp; } ;
struct pf_state_peer {scalar_t__ state; int seqlo; int seqhi; int max_win; scalar_t__ seqdiff; int wscale; int /*<<< orphan*/ * scrub; int /*<<< orphan*/  mss; } ;
struct TYPE_27__ {int /*<<< orphan*/  port; } ;
struct TYPE_28__ {TYPE_8__ xport; int /*<<< orphan*/  addr; } ;
struct TYPE_25__ {int /*<<< orphan*/  port; } ;
struct TYPE_26__ {TYPE_6__ xport; int /*<<< orphan*/  addr; } ;
struct TYPE_23__ {int /*<<< orphan*/  port; } ;
struct TYPE_24__ {TYPE_4__ xport; int /*<<< orphan*/  addr; } ;
struct TYPE_21__ {int /*<<< orphan*/  port; } ;
struct TYPE_22__ {TYPE_2__ xport; int /*<<< orphan*/  addr; } ;
struct pf_state_key_cmp {scalar_t__ af_lan; scalar_t__ af_gwy; TYPE_9__ ext_lan; TYPE_7__ lan; TYPE_5__ gwy; TYPE_3__ ext_gwy; int /*<<< orphan*/  proto; scalar_t__ app_state; } ;
struct TYPE_17__ {int /*<<< orphan*/  port; } ;
struct pf_state_host {TYPE_12__ xport; int /*<<< orphan*/  addr; } ;
struct pf_state_key {int direction; scalar_t__ af_lan; scalar_t__ af_gwy; struct pf_state_host lan; struct pf_state_host gwy; struct pf_state_host ext_gwy; struct pf_state_host ext_lan; TYPE_11__* app_state; } ;
struct TYPE_15__ {TYPE_14__* ptr; } ;
struct pf_state {int /*<<< orphan*/ * packets; TYPE_10__ rule; int /*<<< orphan*/  timeout; int /*<<< orphan*/  expire; int /*<<< orphan*/ * src_node; int /*<<< orphan*/  tag; struct pf_state_peer src; struct pf_state_peer dst; struct pf_state_key* state_key; } ;
struct TYPE_20__ {struct tcphdr* tcp; } ;
struct pf_pdesc {scalar_t__ af; int flags; int p_len; scalar_t__ lmw; scalar_t__ naf; int /*<<< orphan*/  ip_sum; int /*<<< orphan*/ * dst; int /*<<< orphan*/ * mp; int /*<<< orphan*/ * src; int /*<<< orphan*/ * eh; TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  pbuf_t ;
struct TYPE_19__ {int /*<<< orphan*/  return_ttl; } ;
struct TYPE_18__ {scalar_t__ debug; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* handler ) (struct pf_state*,int,int,struct pf_pdesc*,struct pfi_kif*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int MAX (int,int) ; 
 int MIN (int,int) ; 
 int PFDESC_IP_REAS ; 
 int PFDESC_TCP_NORM ; 
 int /*<<< orphan*/  PFRES_BADSTATE ; 
 int /*<<< orphan*/  PFRES_MEMORY ; 
 int /*<<< orphan*/  PFRES_SRCLIMIT ; 
 int /*<<< orphan*/  PFRES_SYNPROXY ; 
 int /*<<< orphan*/  PFTM_TCP_CLOSED ; 
 int /*<<< orphan*/  PFTM_TCP_CLOSING ; 
 int /*<<< orphan*/  PFTM_TCP_ESTABLISHED ; 
 int /*<<< orphan*/  PFTM_TCP_FIN_WAIT ; 
 int /*<<< orphan*/  PFTM_TCP_OPENING ; 
 int /*<<< orphan*/  PF_ACPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ PF_DEBUG_MISC ; 
 int PF_DROP ; 
 int PF_IN ; 
 int PF_OUT ; 
 int PF_PASS ; 
 int PF_SYNPROXY_DROP ; 
 scalar_t__ PF_TCPS_PROXY_DST ; 
 scalar_t__ PF_TCPS_PROXY_SRC ; 
 int PF_WSCALE_FLAG ; 
 int PF_WSCALE_MASK ; 
 int /*<<< orphan*/  REASON_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ SEQ_GEQ (int,int) ; 
 scalar_t__ SEQ_GT (int,int) ; 
 int /*<<< orphan*/  STATE_LOOKUP () ; 
 scalar_t__ STATE_TRANSLATE (struct pf_state_key*) ; 
 scalar_t__ TCPS_CLOSED ; 
 scalar_t__ TCPS_CLOSING ; 
 scalar_t__ TCPS_ESTABLISHED ; 
 scalar_t__ TCPS_FIN_WAIT_2 ; 
 scalar_t__ TCPS_SYN_SENT ; 
 void* TCPS_TIME_WAIT ; 
 int TCP_MAX_WINSHIFT ; 
 int TH_ACK ; 
 int TH_FIN ; 
 int TH_RST ; 
 int TH_SYN ; 
 int htonl (int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pbuf_copy_back (int /*<<< orphan*/ *,int,int,struct tcphdr*) ; 
 int /*<<< orphan*/  pf_change_a (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_change_ap (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 int pf_do_nat64 (struct pf_state_key*,struct pf_pdesc*,int /*<<< orphan*/ *,int) ; 
 int pf_get_wscale (int /*<<< orphan*/ *,int,int,scalar_t__) ; 
 int /*<<< orphan*/ * pf_lazy_makewritable (struct pf_pdesc*,int /*<<< orphan*/ *,int) ; 
 int pf_modulate_sack (int /*<<< orphan*/ *,int,struct pf_pdesc*,struct tcphdr*,struct pf_state_peer*) ; 
 scalar_t__ pf_normalize_tcp_init (int /*<<< orphan*/ *,int,struct pf_pdesc*,struct tcphdr*,struct pf_state_peer*,struct pf_state_peer*) ; 
 scalar_t__ pf_normalize_tcp_stateful (int /*<<< orphan*/ *,int,struct pf_pdesc*,int /*<<< orphan*/ *,struct tcphdr*,struct pf_state*,struct pf_state_peer*,struct pf_state_peer*,int*) ; 
 int /*<<< orphan*/  pf_print_flags (int) ; 
 int /*<<< orphan*/  pf_print_state (struct pf_state*) ; 
 int /*<<< orphan*/  pf_send_tcp (TYPE_14__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pf_src_connlimit (struct pf_state**) ; 
 TYPE_13__ pf_status ; 
 int /*<<< orphan*/  pf_time_second () ; 
 int /*<<< orphan*/  pf_unlink_state (struct pf_state*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int random () ; 
 int /*<<< orphan*/  stub1 (struct pf_state*,int,int,struct pf_pdesc*,struct pfi_kif*) ; 

__attribute__((used)) static int
pf_test_state_tcp(struct pf_state **state, int direction, struct pfi_kif *kif,
    pbuf_t *pbuf, int off, void *h, struct pf_pdesc *pd,
    u_short *reason)
{
#pragma unused(h)
	struct pf_state_key_cmp	 key;
	struct tcphdr		*th = pd->hdr.tcp;
	u_int16_t		 win = ntohs(th->th_win);
	u_int32_t		 ack, end, seq, orig_seq;
	u_int8_t		 sws, dws;
	int			 ackskew;
	int			 copyback = 0;
	struct pf_state_peer	*src, *dst;
	struct pf_state_key	*sk;

	key.app_state = 0;
	key.proto = IPPROTO_TCP;
	key.af_lan = key.af_gwy = pd->af;

	/*
	 * For NAT64 the first time rule search and state creation
	 * is done on the incoming side only.
	 * Once the state gets created, NAT64's LAN side (ipv6) will
	 * not be able to find the state in ext-gwy tree as that normally
	 * is intended to be looked up for incoming traffic from the
	 * WAN side.
	 * Therefore to handle NAT64 case we init keys here for both
	 * lan-ext as well as ext-gwy trees.
	 * In the state lookup we attempt a lookup on both trees if
	 * first one does not return any result and return a match if
	 * the match state's was created by NAT64 rule.
	 */
	PF_ACPY(&key.ext_gwy.addr, pd->src, key.af_gwy);
	PF_ACPY(&key.gwy.addr, pd->dst, key.af_gwy);
	key.ext_gwy.xport.port = th->th_sport;
	key.gwy.xport.port = th->th_dport;

	PF_ACPY(&key.lan.addr, pd->src, key.af_lan);
	PF_ACPY(&key.ext_lan.addr, pd->dst, key.af_lan);
	key.lan.xport.port = th->th_sport;
	key.ext_lan.xport.port = th->th_dport;

	STATE_LOOKUP();

	sk = (*state)->state_key;
	/*
	 * In case of NAT64 the translation is first applied on the LAN
	 * side. Therefore for stack's address family comparison
	 * we use sk->af_lan.
	 */
	if ((direction == sk->direction) && (pd->af == sk->af_lan)) {
		src = &(*state)->src;
		dst = &(*state)->dst;
	} else {
		src = &(*state)->dst;
		dst = &(*state)->src;
	}

	if (src->state == PF_TCPS_PROXY_SRC) {
		if (direction != sk->direction) {
			REASON_SET(reason, PFRES_SYNPROXY);
			return (PF_SYNPROXY_DROP);
		}
		if (th->th_flags & TH_SYN) {
			if (ntohl(th->th_seq) != src->seqlo) {
				REASON_SET(reason, PFRES_SYNPROXY);
				return (PF_DROP);
			}
			pf_send_tcp((*state)->rule.ptr, pd->af, pd->dst,
			    pd->src, th->th_dport, th->th_sport,
			    src->seqhi, ntohl(th->th_seq) + 1,
			    TH_SYN|TH_ACK, 0, src->mss, 0, 1,
			    0, NULL, NULL);
			REASON_SET(reason, PFRES_SYNPROXY);
			return (PF_SYNPROXY_DROP);
		} else if (!(th->th_flags & TH_ACK) ||
		    (ntohl(th->th_ack) != src->seqhi + 1) ||
		    (ntohl(th->th_seq) != src->seqlo + 1)) {
			REASON_SET(reason, PFRES_SYNPROXY);
			return (PF_DROP);
		} else if ((*state)->src_node != NULL &&
		    pf_src_connlimit(state)) {
			REASON_SET(reason, PFRES_SRCLIMIT);
			return (PF_DROP);
		} else
			src->state = PF_TCPS_PROXY_DST;
	}
	if (src->state == PF_TCPS_PROXY_DST) {
		struct pf_state_host *psrc, *pdst;

		if (direction == PF_OUT) {
			psrc = &sk->gwy;
			pdst = &sk->ext_gwy;
		} else {
			psrc = &sk->ext_lan;
			pdst = &sk->lan;
		}
		if (direction == sk->direction) {
			if (((th->th_flags & (TH_SYN|TH_ACK)) != TH_ACK) ||
			    (ntohl(th->th_ack) != src->seqhi + 1) ||
			    (ntohl(th->th_seq) != src->seqlo + 1)) {
				REASON_SET(reason, PFRES_SYNPROXY);
				return (PF_DROP);
			}
			src->max_win = MAX(ntohs(th->th_win), 1);
			if (dst->seqhi == 1)
				dst->seqhi = htonl(random());
			pf_send_tcp((*state)->rule.ptr, pd->af, &psrc->addr,
			    &pdst->addr, psrc->xport.port, pdst->xport.port,
			    dst->seqhi, 0, TH_SYN, 0,
			    src->mss, 0, 0, (*state)->tag, NULL, NULL);
			REASON_SET(reason, PFRES_SYNPROXY);
			return (PF_SYNPROXY_DROP);
		} else if (((th->th_flags & (TH_SYN|TH_ACK)) !=
		    (TH_SYN|TH_ACK)) ||
		    (ntohl(th->th_ack) != dst->seqhi + 1)) {
			REASON_SET(reason, PFRES_SYNPROXY);
			return (PF_DROP);
		} else {
			dst->max_win = MAX(ntohs(th->th_win), 1);
			dst->seqlo = ntohl(th->th_seq);
			pf_send_tcp((*state)->rule.ptr, pd->af, pd->dst,
			    pd->src, th->th_dport, th->th_sport,
			    ntohl(th->th_ack), ntohl(th->th_seq) + 1,
			    TH_ACK, src->max_win, 0, 0, 0,
			    (*state)->tag, NULL, NULL);
			pf_send_tcp((*state)->rule.ptr, pd->af, &psrc->addr,
			    &pdst->addr, psrc->xport.port, pdst->xport.port,
			    src->seqhi + 1, src->seqlo + 1,
			    TH_ACK, dst->max_win, 0, 0, 1,
			    0, NULL, NULL);
			src->seqdiff = dst->seqhi -
			    src->seqlo;
			dst->seqdiff = src->seqhi -
			    dst->seqlo;
			src->seqhi = src->seqlo +
			    dst->max_win;
			dst->seqhi = dst->seqlo +
			    src->max_win;
			src->wscale = dst->wscale = 0;
			src->state = dst->state =
			    TCPS_ESTABLISHED;
			REASON_SET(reason, PFRES_SYNPROXY);
			return (PF_SYNPROXY_DROP);
		}
	}

	if (((th->th_flags & (TH_SYN|TH_ACK)) == TH_SYN) &&
	    dst->state >= TCPS_FIN_WAIT_2 &&
	    src->state >= TCPS_FIN_WAIT_2) {
		if (pf_status.debug >= PF_DEBUG_MISC) {
			printf("pf: state reuse ");
			pf_print_state(*state);
			pf_print_flags(th->th_flags);
			printf("\n");
		}
		/* XXX make sure it's the same direction ?? */
		src->state = dst->state = TCPS_CLOSED;
		pf_unlink_state(*state);
		*state = NULL;
		return (PF_DROP);
	}

	if ((th->th_flags & TH_SYN) == 0) {
		sws = (src->wscale & PF_WSCALE_FLAG) ?
		    (src->wscale & PF_WSCALE_MASK) : TCP_MAX_WINSHIFT;
		dws = (dst->wscale & PF_WSCALE_FLAG) ?
		    (dst->wscale & PF_WSCALE_MASK) : TCP_MAX_WINSHIFT;
	}
	else
		sws = dws = 0;

	/*
	 * Sequence tracking algorithm from Guido van Rooij's paper:
	 *   http://www.madison-gurkha.com/publications/tcp_filtering/
	 *	tcp_filtering.ps
	 */

	orig_seq = seq = ntohl(th->th_seq);
	if (src->seqlo == 0) {
		/* First packet from this end. Set its state */

		if ((pd->flags & PFDESC_TCP_NORM || dst->scrub) &&
		    src->scrub == NULL) {
			if (pf_normalize_tcp_init(pbuf, off, pd, th, src, dst)) {
				REASON_SET(reason, PFRES_MEMORY);
				return (PF_DROP);
			}
		}

		/* Deferred generation of sequence number modulator */
		if (dst->seqdiff && !src->seqdiff) {
			/* use random iss for the TCP server */
			while ((src->seqdiff = random() - seq) == 0)
				;
			ack = ntohl(th->th_ack) - dst->seqdiff;
			pf_change_a(&th->th_seq, &th->th_sum, htonl(seq +
			    src->seqdiff), 0);
			pf_change_a(&th->th_ack, &th->th_sum, htonl(ack), 0);
			copyback = off + sizeof (*th);
		} else {
			ack = ntohl(th->th_ack);
		}

		end = seq + pd->p_len;
		if (th->th_flags & TH_SYN) {
			end++;
			if (dst->wscale & PF_WSCALE_FLAG) {
				src->wscale = pf_get_wscale(pbuf, off,
				    th->th_off, pd->af);
				if (src->wscale & PF_WSCALE_FLAG) {
					/*
					 * Remove scale factor from initial
					 * window
					 */
					sws = src->wscale & PF_WSCALE_MASK;
					win = ((u_int32_t)win + (1 << sws) - 1)
					    >> sws;
					dws = dst->wscale & PF_WSCALE_MASK;
				} else {
					/*
					 * Window scale negotiation has failed,
					 * therefore we must restore the window
					 * scale in the state record that we
					 * optimistically removed in
					 * pf_test_rule().  Care is required to
					 * prevent arithmetic overflow from
					 * zeroing the window when it's
					 * truncated down to 16-bits.
					 */
					u_int32_t max_win = dst->max_win;
					max_win <<=
					    dst->wscale & PF_WSCALE_MASK;
					dst->max_win = MIN(0xffff, max_win);
					/* in case of a retrans SYN|ACK */
					dst->wscale = 0;
				}
			}
		}
		if (th->th_flags & TH_FIN)
			end++;

		src->seqlo = seq;
		if (src->state < TCPS_SYN_SENT)
			src->state = TCPS_SYN_SENT;

		/*
		 * May need to slide the window (seqhi may have been set by
		 * the crappy stack check or if we picked up the connection
		 * after establishment)
		 */
		if (src->seqhi == 1 ||
		    SEQ_GEQ(end + MAX(1, (u_int32_t)dst->max_win << dws),
		    src->seqhi))
			src->seqhi = end + MAX(1, (u_int32_t)dst->max_win << dws);
		if (win > src->max_win)
			src->max_win = win;

	} else {
		ack = ntohl(th->th_ack) - dst->seqdiff;
		if (src->seqdiff) {
			/* Modulate sequence numbers */
			pf_change_a(&th->th_seq, &th->th_sum, htonl(seq +
			    src->seqdiff), 0);
			pf_change_a(&th->th_ack, &th->th_sum, htonl(ack), 0);
			copyback = off+ sizeof (*th);
		}
		end = seq + pd->p_len;
		if (th->th_flags & TH_SYN)
			end++;
		if (th->th_flags & TH_FIN)
			end++;
	}

	if ((th->th_flags & TH_ACK) == 0) {
		/* Let it pass through the ack skew check */
		ack = dst->seqlo;
	} else if ((ack == 0 &&
	    (th->th_flags & (TH_ACK|TH_RST)) == (TH_ACK|TH_RST)) ||
	    /* broken tcp stacks do not set ack */
	    (dst->state < TCPS_SYN_SENT)) {
		/*
		 * Many stacks (ours included) will set the ACK number in an
		 * FIN|ACK if the SYN times out -- no sequence to ACK.
		 */
		ack = dst->seqlo;
	}

	if (seq == end) {
		/* Ease sequencing restrictions on no data packets */
		seq = src->seqlo;
		end = seq;
	}

	ackskew = dst->seqlo - ack;


	/*
	 * Need to demodulate the sequence numbers in any TCP SACK options
	 * (Selective ACK). We could optionally validate the SACK values
	 * against the current ACK window, either forwards or backwards, but
	 * I'm not confident that SACK has been implemented properly
	 * everywhere. It wouldn't surprise me if several stacks accidently
	 * SACK too far backwards of previously ACKed data. There really aren't
	 * any security implications of bad SACKing unless the target stack
	 * doesn't validate the option length correctly. Someone trying to
	 * spoof into a TCP connection won't bother blindly sending SACK
	 * options anyway.
	 */
	if (dst->seqdiff && (th->th_off << 2) > (int)sizeof (struct tcphdr)) {
		copyback = pf_modulate_sack(pbuf, off, pd, th, dst);
		if (copyback == -1) {
			REASON_SET(reason, PFRES_MEMORY);
			return (PF_DROP);
		}

		pbuf = pd->mp;	// XXXSCW: Why?
	}


#define MAXACKWINDOW (0xffff + 1500)	/* 1500 is an arbitrary fudge factor */
	if (SEQ_GEQ(src->seqhi, end) &&
	    /* Last octet inside other's window space */
	    SEQ_GEQ(seq, src->seqlo - ((u_int32_t)dst->max_win << dws)) &&
	    /* Retrans: not more than one window back */
	    (ackskew >= -MAXACKWINDOW) &&
	    /* Acking not more than one reassembled fragment backwards */
	    (ackskew <= (MAXACKWINDOW << sws)) &&
	    /* Acking not more than one window forward */
	    ((th->th_flags & TH_RST) == 0 || orig_seq == src->seqlo ||
	    (orig_seq == src->seqlo + 1) || (orig_seq + 1 == src->seqlo) ||
	    (pd->flags & PFDESC_IP_REAS) == 0)) {
	    /* Require an exact/+1 sequence match on resets when possible */

		if (dst->scrub || src->scrub) {
			if (pf_normalize_tcp_stateful(pbuf, off, pd, reason, th,
			    *state, src, dst, &copyback))
				return (PF_DROP);

			pbuf = pd->mp;	// XXXSCW: Why?
		}

		/* update max window */
		if (src->max_win < win)
			src->max_win = win;
		/* synchronize sequencing */
		if (SEQ_GT(end, src->seqlo))
			src->seqlo = end;
		/* slide the window of what the other end can send */
		if (SEQ_GEQ(ack + ((u_int32_t)win << sws), dst->seqhi))
			dst->seqhi = ack + MAX(((u_int32_t)win << sws), 1);

		/* update states */
		if (th->th_flags & TH_SYN)
			if (src->state < TCPS_SYN_SENT)
				src->state = TCPS_SYN_SENT;
		if (th->th_flags & TH_FIN)
			if (src->state < TCPS_CLOSING)
				src->state = TCPS_CLOSING;
		if (th->th_flags & TH_ACK) {
			if (dst->state == TCPS_SYN_SENT) {
				dst->state = TCPS_ESTABLISHED;
				if (src->state == TCPS_ESTABLISHED &&
				    (*state)->src_node != NULL &&
				    pf_src_connlimit(state)) {
					REASON_SET(reason, PFRES_SRCLIMIT);
					return (PF_DROP);
				}
			} else if (dst->state == TCPS_CLOSING)
				dst->state = TCPS_FIN_WAIT_2;
		}
		if (th->th_flags & TH_RST)
			src->state = dst->state = TCPS_TIME_WAIT;

		/* update expire time */
		(*state)->expire = pf_time_second();
		if (src->state >= TCPS_FIN_WAIT_2 &&
		    dst->state >= TCPS_FIN_WAIT_2)
			(*state)->timeout = PFTM_TCP_CLOSED;
		else if (src->state >= TCPS_CLOSING &&
		    dst->state >= TCPS_CLOSING)
			(*state)->timeout = PFTM_TCP_FIN_WAIT;
		else if (src->state < TCPS_ESTABLISHED ||
		    dst->state < TCPS_ESTABLISHED)
			(*state)->timeout = PFTM_TCP_OPENING;
		else if (src->state >= TCPS_CLOSING ||
		    dst->state >= TCPS_CLOSING)
			(*state)->timeout = PFTM_TCP_CLOSING;
		else
			(*state)->timeout = PFTM_TCP_ESTABLISHED;

		/* Fall through to PASS packet */

	} else if ((dst->state < TCPS_SYN_SENT ||
	    dst->state >= TCPS_FIN_WAIT_2 || src->state >= TCPS_FIN_WAIT_2) &&
	    SEQ_GEQ(src->seqhi + MAXACKWINDOW, end) &&
	    /* Within a window forward of the originating packet */
	    SEQ_GEQ(seq, src->seqlo - MAXACKWINDOW)) {
	    /* Within a window backward of the originating packet */

		/*
		 * This currently handles three situations:
		 *  1) Stupid stacks will shotgun SYNs before their peer
		 *     replies.
		 *  2) When PF catches an already established stream (the
		 *     firewall rebooted, the state table was flushed, routes
		 *     changed...)
		 *  3) Packets get funky immediately after the connection
		 *     closes (this should catch Solaris spurious ACK|FINs
		 *     that web servers like to spew after a close)
		 *
		 * This must be a little more careful than the above code
		 * since packet floods will also be caught here. We don't
		 * update the TTL here to mitigate the damage of a packet
		 * flood and so the same code can handle awkward establishment
		 * and a loosened connection close.
		 * In the establishment case, a correct peer response will
		 * validate the connection, go through the normal state code
		 * and keep updating the state TTL.
		 */

		if (pf_status.debug >= PF_DEBUG_MISC) {
			printf("pf: loose state match: ");
			pf_print_state(*state);
			pf_print_flags(th->th_flags);
			printf(" seq=%u (%u) ack=%u len=%u ackskew=%d "
			    "pkts=%llu:%llu dir=%s,%s\n", seq, orig_seq, ack,
			    pd->p_len, ackskew, (*state)->packets[0],
			    (*state)->packets[1],
			    direction == PF_IN ? "in" : "out",
			    direction == sk->direction ?
			    "fwd" : "rev");
		}

		if (dst->scrub || src->scrub) {
			if (pf_normalize_tcp_stateful(pbuf, off, pd, reason, th,
			    *state, src, dst, &copyback))
				return (PF_DROP);
			pbuf = pd->mp;	// XXXSCW: Why?
		}

		/* update max window */
		if (src->max_win < win)
			src->max_win = win;
		/* synchronize sequencing */
		if (SEQ_GT(end, src->seqlo))
			src->seqlo = end;
		/* slide the window of what the other end can send */
		if (SEQ_GEQ(ack + ((u_int32_t)win << sws), dst->seqhi))
			dst->seqhi = ack + MAX(((u_int32_t)win << sws), 1);

		/*
		 * Cannot set dst->seqhi here since this could be a shotgunned
		 * SYN and not an already established connection.
		 */

		if (th->th_flags & TH_FIN)
			if (src->state < TCPS_CLOSING)
				src->state = TCPS_CLOSING;
		if (th->th_flags & TH_RST)
			src->state = dst->state = TCPS_TIME_WAIT;

		/* Fall through to PASS packet */

	} else {
		if (dst->state == TCPS_SYN_SENT &&
		    src->state == TCPS_SYN_SENT) {
			/* Send RST for state mismatches during handshake */
			if (!(th->th_flags & TH_RST))
				pf_send_tcp((*state)->rule.ptr, pd->af,
				    pd->dst, pd->src, th->th_dport,
				    th->th_sport, ntohl(th->th_ack), 0,
				    TH_RST, 0, 0,
				    (*state)->rule.ptr->return_ttl, 1, 0,
				    pd->eh, kif->pfik_ifp);
			src->seqlo = 0;
			src->seqhi = 1;
			src->max_win = 1;
		} else if (pf_status.debug >= PF_DEBUG_MISC) {
			printf("pf: BAD state: ");
			pf_print_state(*state);
			pf_print_flags(th->th_flags);
			printf("\n   seq=%u (%u) ack=%u len=%u ackskew=%d "
			    "sws=%u dws=%u pkts=%llu:%llu dir=%s,%s\n",
			    seq, orig_seq, ack, pd->p_len, ackskew,
			    (unsigned int)sws, (unsigned int)dws,
			    (*state)->packets[0], (*state)->packets[1],
			    direction == PF_IN ? "in" : "out",
			    direction == sk->direction ?
			    "fwd" : "rev");
			printf("pf: State failure on: %c %c %c %c | %c %c\n",
			    SEQ_GEQ(src->seqhi, end) ? ' ' : '1',
			    SEQ_GEQ(seq,
			    src->seqlo - ((u_int32_t)dst->max_win << dws)) ?
			    ' ': '2',
			    (ackskew >= -MAXACKWINDOW) ? ' ' : '3',
			    (ackskew <= (MAXACKWINDOW << sws)) ? ' ' : '4',
			    SEQ_GEQ(src->seqhi + MAXACKWINDOW, end) ?' ' :'5',
			    SEQ_GEQ(seq, src->seqlo - MAXACKWINDOW) ?' ' :'6');
		}
		REASON_SET(reason, PFRES_BADSTATE);
		return (PF_DROP);
	}

	/* Any packets which have gotten here are to be passed */

	if (sk->app_state &&
	    sk->app_state->handler) {
		sk->app_state->handler(*state, direction,
		    off + (th->th_off << 2), pd, kif);
		if (pd->lmw < 0) {
			REASON_SET(reason, PFRES_MEMORY);
			return (PF_DROP);
		}
		pbuf = pd->mp;	// XXXSCW: Why?
	}

	/* translate source/destination address, if necessary */
	if (STATE_TRANSLATE(sk)) {
		pd->naf = (pd->af == sk->af_lan) ? sk->af_gwy : sk->af_lan;

		if (direction == PF_OUT) {
			pf_change_ap(direction, pd->mp, pd->src, &th->th_sport,
				     pd->ip_sum, &th->th_sum, &sk->gwy.addr,
				     sk->gwy.xport.port, 0, pd->af, pd->naf, 1);
		} else {
			if (pd->af != pd->naf) {
				if (pd->af == sk->af_gwy) {
					pf_change_ap(direction, pd->mp, pd->dst,
						&th->th_dport, pd->ip_sum,
						&th->th_sum, &sk->lan.addr,
						sk->lan.xport.port, 0,
						pd->af, pd->naf, 0);

					pf_change_ap(direction, pd->mp, pd->src,
						&th->th_sport, pd->ip_sum,
						&th->th_sum, &sk->ext_lan.addr,
						th->th_sport, 0, pd->af,
						pd->naf, 0);

				} else {
					pf_change_ap(direction, pd->mp, pd->dst,
						&th->th_dport, pd->ip_sum,
						&th->th_sum, &sk->ext_gwy.addr,
						th->th_dport, 0, pd->af,
						pd->naf, 0);

					pf_change_ap(direction, pd->mp, pd->src,
						&th->th_sport, pd->ip_sum,
						&th->th_sum, &sk->gwy.addr,
						sk->gwy.xport.port, 0, pd->af,
						pd->naf, 0);
				}
			} else {
				pf_change_ap(direction, pd->mp, pd->dst,
					     &th->th_dport, pd->ip_sum,
					     &th->th_sum, &sk->lan.addr,
					     sk->lan.xport.port, 0, pd->af,
					     pd->naf, 1);
			}
		}

		copyback = off + sizeof (*th);
	}

	if (copyback) {
		if (pf_lazy_makewritable(pd, pbuf, copyback) == NULL) {
			REASON_SET(reason, PFRES_MEMORY);
			return (PF_DROP);
		}

		/* Copyback sequence modulation or stateful scrub changes */
		pbuf_copy_back(pbuf, off, sizeof (*th), th);

		if (sk->af_lan != sk->af_gwy)
			return (pf_do_nat64(sk, pd, pbuf, off));
	}
	return (PF_PASS);
}