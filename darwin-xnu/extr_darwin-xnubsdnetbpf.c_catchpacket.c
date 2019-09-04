#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct timeval {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_7__ {int pkt_flags; scalar_t__ pkt_flowsrc; int /*<<< orphan*/  bufstatus_sndbuf; int /*<<< orphan*/  bufstatus_if; int /*<<< orphan*/  pkt_svc; int /*<<< orphan*/  pkt_proto; int /*<<< orphan*/  pkt_flowid; } ;
struct mbuf {TYPE_3__ m_pkthdr; } ;
struct bpf_packet {scalar_t__ bpfp_type; int /*<<< orphan*/  bpfp_total_length; struct mbuf* bpfp_mbuf; } ;
struct TYPE_6__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct bpf_hdr_ext {int bh_hdrlen; int bh_caplen; int /*<<< orphan*/  bh_flags; int /*<<< orphan*/  bh_unsent_snd; int /*<<< orphan*/  bh_unsent_bytes; int /*<<< orphan*/  bh_pktflags; int /*<<< orphan*/  bh_svc; int /*<<< orphan*/  bh_proto; int /*<<< orphan*/  bh_flowid; int /*<<< orphan*/  bh_datalen; TYPE_2__ bh_tstamp; } ;
struct TYPE_8__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct bpf_hdr {int bh_hdrlen; int bh_caplen; int /*<<< orphan*/  bh_datalen; TYPE_4__ bh_tstamp; } ;
struct bpf_d {int bd_flags; int bd_bufsize; int bd_slen; scalar_t__ bd_hbuf_read; scalar_t__ bd_headdrop; scalar_t__ bd_state; int bd_scnt; scalar_t__ bd_sbuf; scalar_t__ bd_immediate; int /*<<< orphan*/ * bd_hbuf; int /*<<< orphan*/ * bd_fbuf; scalar_t__ bd_hcnt; scalar_t__ bd_dcount; TYPE_1__* bd_bif; } ;
struct TYPE_5__ {int bif_exthdrlen; int bif_hdrlen; } ;

/* Variables and functions */
 int BPF_EXTENDED_HDR ; 
 int /*<<< orphan*/  BPF_HDR_EXT_FLAGS_DIR_IN ; 
 int /*<<< orphan*/  BPF_HDR_EXT_FLAGS_DIR_OUT ; 
 scalar_t__ BPF_PACKET_TYPE_MBUF ; 
 int /*<<< orphan*/  BPF_PKTFLAGS_LAST_PKT ; 
 int /*<<< orphan*/  BPF_PKTFLAGS_START_SEQ ; 
 int /*<<< orphan*/  BPF_PKTFLAGS_TCP_REXMT ; 
 scalar_t__ BPF_TIMED_OUT ; 
 int BPF_WORDALIGN (int) ; 
 scalar_t__ FLOWSRC_INPCB ; 
 int PKTF_FLOW_ID ; 
 int PKTF_FLOW_LOCALSRC ; 
 int PKTF_FLOW_RAWSOCK ; 
 int PKTF_LAST_PKT ; 
 int PKTF_START_SEQ ; 
 int PKTF_TCP_REXMT ; 
 int PKTF_VALID_UNSENT_DATA ; 
 int /*<<< orphan*/  ROTATE_BUFFERS (struct bpf_d*) ; 
 int /*<<< orphan*/  bpf_wakeup (struct bpf_d*) ; 
 int /*<<< orphan*/  copy_bpf_packet (struct bpf_packet*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct bpf_hdr_ext*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  microtime (struct timeval*) ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  so_svc2tc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
catchpacket(struct bpf_d *d, struct bpf_packet * pkt,
	u_int snaplen, int outbound)
{
	struct bpf_hdr *hp;
	struct bpf_hdr_ext *ehp;
	int totlen, curlen;
	int hdrlen, caplen;
	int do_wakeup = 0;
	u_char *payload;
	struct timeval tv;

	hdrlen = (d->bd_flags & BPF_EXTENDED_HDR) ? d->bd_bif->bif_exthdrlen :
	    d->bd_bif->bif_hdrlen;
	/*
	 * Figure out how many bytes to move.  If the packet is
	 * greater or equal to the snapshot length, transfer that
	 * much.  Otherwise, transfer the whole packet (unless
	 * we hit the buffer size limit).
	 */
	totlen = hdrlen + min(snaplen, pkt->bpfp_total_length);
	if (totlen > d->bd_bufsize)
		totlen = d->bd_bufsize;

	if (hdrlen > totlen)
		return;

	/*
	 * Round up the end of the previous packet to the next longword.
	 */
	curlen = BPF_WORDALIGN(d->bd_slen);
	if (curlen + totlen > d->bd_bufsize) {
		/*
		 * This packet will overflow the storage buffer.
		 * Rotate the buffers if we can, then wakeup any
		 * pending reads.
		 *
		 * We cannot rotate buffers if a read is in progress
		 * so drop the packet
		 */
		if (d->bd_hbuf_read != 0) {
			++d->bd_dcount;
			return;
		}

		if (d->bd_fbuf == NULL) {
			if (d->bd_headdrop == 0) {
				/*
				 * We haven't completed the previous read yet,
				 * so drop the packet.
				 */
				++d->bd_dcount;
				return;
			}
			/*
			 * Drop the hold buffer as it contains older packets
			 */
			d->bd_dcount += d->bd_hcnt;
			d->bd_fbuf = d->bd_hbuf;
			ROTATE_BUFFERS(d);
		} else {
			ROTATE_BUFFERS(d);
		}
		do_wakeup = 1;
		curlen = 0;
	} else if (d->bd_immediate || d->bd_state == BPF_TIMED_OUT)
		/*
		 * Immediate mode is set, or the read timeout has
		 * already expired during a select call. A packet
		 * arrived, so the reader should be woken up.
		 */
		do_wakeup = 1;

	/*
	 * Append the bpf header.
	 */
	microtime(&tv);
	if (d->bd_flags & BPF_EXTENDED_HDR) {
		struct mbuf *m;

		m = (pkt->bpfp_type == BPF_PACKET_TYPE_MBUF)
			? pkt->bpfp_mbuf : NULL;
		ehp = (struct bpf_hdr_ext *)(void *)(d->bd_sbuf + curlen);
		memset(ehp, 0, sizeof(*ehp));
		ehp->bh_tstamp.tv_sec = tv.tv_sec;
		ehp->bh_tstamp.tv_usec = tv.tv_usec;

		ehp->bh_datalen = pkt->bpfp_total_length;
		ehp->bh_hdrlen = hdrlen;
		caplen = ehp->bh_caplen = totlen - hdrlen;
		if (m == NULL) {
			if (outbound) {
				ehp->bh_flags |= BPF_HDR_EXT_FLAGS_DIR_OUT;
			} else {
				ehp->bh_flags |= BPF_HDR_EXT_FLAGS_DIR_IN;
			}
		} else if (outbound) {
			ehp->bh_flags |= BPF_HDR_EXT_FLAGS_DIR_OUT;

			/* only do lookups on non-raw INPCB */
			if ((m->m_pkthdr.pkt_flags & (PKTF_FLOW_ID|
			    PKTF_FLOW_LOCALSRC|PKTF_FLOW_RAWSOCK)) ==
			    (PKTF_FLOW_ID|PKTF_FLOW_LOCALSRC) &&
			    m->m_pkthdr.pkt_flowsrc == FLOWSRC_INPCB) {
				ehp->bh_flowid = m->m_pkthdr.pkt_flowid;
				ehp->bh_proto = m->m_pkthdr.pkt_proto;
			}
			ehp->bh_svc = so_svc2tc(m->m_pkthdr.pkt_svc);
			if (m->m_pkthdr.pkt_flags & PKTF_TCP_REXMT)
				ehp->bh_pktflags |= BPF_PKTFLAGS_TCP_REXMT;
			if (m->m_pkthdr.pkt_flags & PKTF_START_SEQ)
				ehp->bh_pktflags |= BPF_PKTFLAGS_START_SEQ;
			if (m->m_pkthdr.pkt_flags & PKTF_LAST_PKT)
				ehp->bh_pktflags |= BPF_PKTFLAGS_LAST_PKT;
			if (m->m_pkthdr.pkt_flags & PKTF_VALID_UNSENT_DATA) {
				ehp->bh_unsent_bytes =
				    m->m_pkthdr.bufstatus_if;
				ehp->bh_unsent_snd =
				    m->m_pkthdr.bufstatus_sndbuf;
			}
		} else
			ehp->bh_flags |= BPF_HDR_EXT_FLAGS_DIR_IN;
		payload = (u_char *)ehp + hdrlen;
	} else {
		hp = (struct bpf_hdr *)(void *)(d->bd_sbuf + curlen);
		hp->bh_tstamp.tv_sec = tv.tv_sec;
		hp->bh_tstamp.tv_usec = tv.tv_usec;
		hp->bh_datalen = pkt->bpfp_total_length;
		hp->bh_hdrlen = hdrlen;
		caplen = hp->bh_caplen = totlen - hdrlen;
		payload = (u_char *)hp + hdrlen;
	}
	/*
	 * Copy the packet data into the store buffer and update its length.
	 */
	copy_bpf_packet(pkt, payload, caplen);
	d->bd_slen = curlen + totlen;
	d->bd_scnt += 1;

	if (do_wakeup)
		bpf_wakeup(d);
}