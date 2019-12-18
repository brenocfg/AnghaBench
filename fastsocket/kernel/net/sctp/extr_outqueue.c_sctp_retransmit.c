#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sctp_transport {TYPE_5__* asoc; } ;
struct sctp_outq {int fast_rtx; TYPE_4__* asoc; } ;
typedef  int sctp_retransmit_reason_t ;
struct TYPE_6__ {struct sctp_transport* retran_path; } ;
struct TYPE_10__ {int /*<<< orphan*/  init_retries; int /*<<< orphan*/  unack_data; int /*<<< orphan*/  rtx_data_chunks; TYPE_1__ peer; } ;
struct TYPE_8__ {TYPE_2__* sk; } ;
struct TYPE_9__ {TYPE_3__ base; int /*<<< orphan*/  ctsn_ack_point; } ;
struct TYPE_7__ {int sk_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  SCTP_INC_STATS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_LOWER_CWND_FAST_RTX ; 
 int /*<<< orphan*/  SCTP_LOWER_CWND_T3_RTX ; 
 int /*<<< orphan*/  SCTP_MIB_FAST_RETRANSMITS ; 
 int /*<<< orphan*/  SCTP_MIB_PMTUD_RETRANSMITS ; 
 int /*<<< orphan*/  SCTP_MIB_T1_RETRANSMITS ; 
 int /*<<< orphan*/  SCTP_MIB_T3_RETRANSMITS ; 
#define  SCTP_RTXR_FAST_RTX 131 
#define  SCTP_RTXR_PMTUD 130 
#define  SCTP_RTXR_T1_RTX 129 
#define  SCTP_RTXR_T3_RTX 128 
 int /*<<< orphan*/  sctp_assoc_update_retran_path (TYPE_5__*) ; 
 int /*<<< orphan*/  sctp_generate_fwdtsn (struct sctp_outq*,int /*<<< orphan*/ ) ; 
 int sctp_outq_flush (struct sctp_outq*,int) ; 
 int /*<<< orphan*/  sctp_retransmit_mark (struct sctp_outq*,struct sctp_transport*,int) ; 
 int /*<<< orphan*/  sctp_transport_lower_cwnd (struct sctp_transport*,int /*<<< orphan*/ ) ; 

void sctp_retransmit(struct sctp_outq *q, struct sctp_transport *transport,
		     sctp_retransmit_reason_t reason)
{
	int error = 0;

	switch(reason) {
	case SCTP_RTXR_T3_RTX:
		SCTP_INC_STATS(SCTP_MIB_T3_RETRANSMITS);
		sctp_transport_lower_cwnd(transport, SCTP_LOWER_CWND_T3_RTX);
		/* Update the retran path if the T3-rtx timer has expired for
		 * the current retran path.
		 */
		if (transport == transport->asoc->peer.retran_path)
			sctp_assoc_update_retran_path(transport->asoc);
		transport->asoc->rtx_data_chunks +=
			transport->asoc->unack_data;
		break;
	case SCTP_RTXR_FAST_RTX:
		SCTP_INC_STATS(SCTP_MIB_FAST_RETRANSMITS);
		sctp_transport_lower_cwnd(transport, SCTP_LOWER_CWND_FAST_RTX);
		q->fast_rtx = 1;
		break;
	case SCTP_RTXR_PMTUD:
		SCTP_INC_STATS(SCTP_MIB_PMTUD_RETRANSMITS);
		break;
	case SCTP_RTXR_T1_RTX:
		SCTP_INC_STATS(SCTP_MIB_T1_RETRANSMITS);
		transport->asoc->init_retries++;
		break;
	default:
		BUG();
	}

	sctp_retransmit_mark(q, transport, reason);

	/* PR-SCTP A5) Any time the T3-rtx timer expires, on any destination,
	 * the sender SHOULD try to advance the "Advanced.Peer.Ack.Point" by
	 * following the procedures outlined in C1 - C5.
	 */
	if (reason == SCTP_RTXR_T3_RTX)
		sctp_generate_fwdtsn(q, q->asoc->ctsn_ack_point);

	/* Flush the queues only on timeout, since fast_rtx is only
	 * triggered during sack processing and the queue
	 * will be flushed at the end.
	 */
	if (reason != SCTP_RTXR_FAST_RTX)
		error = sctp_outq_flush(q, /* rtx_timeout */ 1);

	if (error)
		q->asoc->base.sk->sk_err = -error;
}