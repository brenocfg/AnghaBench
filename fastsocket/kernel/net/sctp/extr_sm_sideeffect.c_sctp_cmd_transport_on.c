#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sctp_transport {scalar_t__ state; int rto_pending; int /*<<< orphan*/  hb_timer; scalar_t__ dst; scalar_t__ hb_sent; TYPE_1__* asoc; scalar_t__ error_count; } ;
struct sctp_chunk {TYPE_2__* skb; } ;
struct sctp_association {int dummy; } ;
struct TYPE_6__ {scalar_t__ sent_at; } ;
typedef  TYPE_3__ sctp_sender_hb_info_t ;
typedef  int /*<<< orphan*/  sctp_cmd_seq_t ;
struct TYPE_5__ {scalar_t__ data; } ;
struct TYPE_4__ {scalar_t__ state; scalar_t__ overall_error_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_HEARTBEAT_SUCCESS ; 
 scalar_t__ SCTP_INACTIVE ; 
 scalar_t__ SCTP_PF ; 
 scalar_t__ SCTP_STATE_SHUTDOWN_PENDING ; 
 int /*<<< orphan*/  SCTP_TRANSPORT_UP ; 
 scalar_t__ SCTP_UNCONFIRMED ; 
 int /*<<< orphan*/  dst_confirm (scalar_t__) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_assoc_control_transport (struct sctp_association*,struct sctp_transport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_transport_hold (struct sctp_transport*) ; 
 int /*<<< orphan*/  sctp_transport_timeout (struct sctp_transport*) ; 
 int /*<<< orphan*/  sctp_transport_update_rto (struct sctp_transport*,scalar_t__) ; 

__attribute__((used)) static void sctp_cmd_transport_on(sctp_cmd_seq_t *cmds,
				  struct sctp_association *asoc,
				  struct sctp_transport *t,
				  struct sctp_chunk *chunk)
{
	sctp_sender_hb_info_t *hbinfo;

	/* 8.3 Upon the receipt of the HEARTBEAT ACK, the sender of the
	 * HEARTBEAT should clear the error counter of the destination
	 * transport address to which the HEARTBEAT was sent.
	 */
	t->error_count = 0;

	/*
	 * Although RFC4960 specifies that the overall error count must
	 * be cleared when a HEARTBEAT ACK is received, we make an
	 * exception while in SHUTDOWN PENDING. If the peer keeps its
	 * window shut forever, we may never be able to transmit our
	 * outstanding data and rely on the retransmission limit be reached
	 * to shutdown the association.
	 */
	if (t->asoc->state != SCTP_STATE_SHUTDOWN_PENDING)
		t->asoc->overall_error_count = 0;

	/* Clear the hb_sent flag to signal that we had a good
	 * acknowledgement.
	 */
	t->hb_sent = 0;

	/* Mark the destination transport address as active if it is not so
	 * marked.
	 */
	if ((t->state == SCTP_INACTIVE) || (t->state == SCTP_UNCONFIRMED))
		sctp_assoc_control_transport(asoc, t, SCTP_TRANSPORT_UP,
					     SCTP_HEARTBEAT_SUCCESS);

	if (t->state == SCTP_PF)
		sctp_assoc_control_transport(asoc, t, SCTP_TRANSPORT_UP,
					     SCTP_HEARTBEAT_SUCCESS);

	/* HB-ACK was received for a the proper HB.  Consider this
	 * forward progress.
	 */
	if (t->dst)
		dst_confirm(t->dst);

	/* The receiver of the HEARTBEAT ACK should also perform an
	 * RTT measurement for that destination transport address
	 * using the time value carried in the HEARTBEAT ACK chunk.
	 * If the transport's rto_pending variable has been cleared,
	 * it was most likely due to a retransmit.  However, we want
	 * to re-enable it to properly update the rto.
	 */
	if (t->rto_pending == 0)
		t->rto_pending = 1;

	hbinfo = (sctp_sender_hb_info_t *) chunk->skb->data;
	sctp_transport_update_rto(t, (jiffies - hbinfo->sent_at));

	/* Update the heartbeat timer.  */
	if (!mod_timer(&t->hb_timer, sctp_transport_timeout(t)))
		sctp_transport_hold(t);
}