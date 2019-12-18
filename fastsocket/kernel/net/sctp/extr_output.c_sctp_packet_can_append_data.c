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
struct sctp_transport {size_t flight_size; size_t cwnd; unsigned int pathmtu; struct sctp_association* asoc; } ;
struct sctp_packet {unsigned int overhead; struct sctp_transport* transport; } ;
struct sctp_outq {size_t outstanding_bytes; unsigned int out_qlen; } ;
struct sctp_chunk {scalar_t__ fast_retransmit; TYPE_4__* msg; TYPE_3__* skb; } ;
struct TYPE_7__ {int /*<<< orphan*/  sk; } ;
struct TYPE_6__ {size_t rwnd; } ;
struct sctp_association {TYPE_2__ base; TYPE_1__ peer; struct sctp_outq outqueue; } ;
typedef  int /*<<< orphan*/  sctp_xmit_t ;
struct TYPE_10__ {int /*<<< orphan*/  nodelay; } ;
struct TYPE_9__ {scalar_t__ can_delay; } ;
struct TYPE_8__ {unsigned int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESTABLISHED ; 
 scalar_t__ SCTP_NEED_FRTX ; 
 int /*<<< orphan*/  SCTP_XMIT_NAGLE_DELAY ; 
 int /*<<< orphan*/  SCTP_XMIT_OK ; 
 int /*<<< orphan*/  SCTP_XMIT_RWND_FULL ; 
 size_t sctp_data_size (struct sctp_chunk*) ; 
 scalar_t__ sctp_packet_empty (struct sctp_packet*) ; 
 TYPE_5__* sctp_sk (int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_state (struct sctp_association*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static sctp_xmit_t sctp_packet_can_append_data(struct sctp_packet *packet,
					   struct sctp_chunk *chunk)
{
	sctp_xmit_t retval = SCTP_XMIT_OK;
	size_t datasize, rwnd, inflight, flight_size;
	struct sctp_transport *transport = packet->transport;
	struct sctp_association *asoc = transport->asoc;
	struct sctp_outq *q = &asoc->outqueue;

	/* RFC 2960 6.1  Transmission of DATA Chunks
	 *
	 * A) At any given time, the data sender MUST NOT transmit new data to
	 * any destination transport address if its peer's rwnd indicates
	 * that the peer has no buffer space (i.e. rwnd is 0, see Section
	 * 6.2.1).  However, regardless of the value of rwnd (including if it
	 * is 0), the data sender can always have one DATA chunk in flight to
	 * the receiver if allowed by cwnd (see rule B below).  This rule
	 * allows the sender to probe for a change in rwnd that the sender
	 * missed due to the SACK having been lost in transit from the data
	 * receiver to the data sender.
	 */

	rwnd = asoc->peer.rwnd;
	inflight = q->outstanding_bytes;
	flight_size = transport->flight_size;

	datasize = sctp_data_size(chunk);

	if (datasize > rwnd) {
		if (inflight > 0) {
			/* We have (at least) one data chunk in flight,
			 * so we can't fall back to rule 6.1 B).
			 */
			retval = SCTP_XMIT_RWND_FULL;
			goto finish;
		}
	}

	/* RFC 2960 6.1  Transmission of DATA Chunks
	 *
	 * B) At any given time, the sender MUST NOT transmit new data
	 * to a given transport address if it has cwnd or more bytes
	 * of data outstanding to that transport address.
	 */
	/* RFC 7.2.4 & the Implementers Guide 2.8.
	 *
	 * 3) ...
	 *    When a Fast Retransmit is being performed the sender SHOULD
	 *    ignore the value of cwnd and SHOULD NOT delay retransmission.
	 */
	if (chunk->fast_retransmit != SCTP_NEED_FRTX)
		if (flight_size >= transport->cwnd) {
			retval = SCTP_XMIT_RWND_FULL;
			goto finish;
		}

	/* Nagle's algorithm to solve small-packet problem:
	 * Inhibit the sending of new chunks when new outgoing data arrives
	 * if any previously transmitted data on the connection remains
	 * unacknowledged.
	 */
	if (!sctp_sk(asoc->base.sk)->nodelay && sctp_packet_empty(packet) &&
	    inflight && sctp_state(asoc, ESTABLISHED)) {
		unsigned max = transport->pathmtu - packet->overhead;
		unsigned len = chunk->skb->len + q->out_qlen;

		/* Check whether this chunk and all the rest of pending
		 * data will fit or delay in hopes of bundling a full
		 * sized packet.
		 * Don't delay large message writes that may have been
		 * fragmeneted into small peices.
		 */
		if ((len < max) && chunk->msg->can_delay) {
			retval = SCTP_XMIT_NAGLE_DELAY;
			goto finish;
		}
	}

finish:
	return retval;
}