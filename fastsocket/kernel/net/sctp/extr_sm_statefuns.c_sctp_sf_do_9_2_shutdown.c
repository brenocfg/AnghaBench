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
struct sctp_ulpevent {int dummy; } ;
struct sctp_shutdown_chunk_t {int dummy; } ;
struct sctp_endpoint {int dummy; } ;
struct TYPE_4__ {TYPE_2__* shutdown_hdr; } ;
struct sctp_chunk {TYPE_1__ subh; TYPE_3__* skb; } ;
struct sctp_association {int /*<<< orphan*/  outqueue; int /*<<< orphan*/  next_tsn; int /*<<< orphan*/  ctsn_ack_point; } ;
typedef  int /*<<< orphan*/  sctp_subtype_t ;
struct TYPE_5__ {int /*<<< orphan*/  cum_tsn_ack; } ;
typedef  TYPE_2__ sctp_shutdownhdr_t ;
typedef  scalar_t__ sctp_disposition_t ;
typedef  int /*<<< orphan*/  sctp_cmd_seq_t ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_6__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  SCTP_BE32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_CMD_EVENT_ULP ; 
 int /*<<< orphan*/  SCTP_CMD_NEW_STATE ; 
 int /*<<< orphan*/  SCTP_CMD_PROCESS_CTSN ; 
 int /*<<< orphan*/  SCTP_DEBUG_PRINTK (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ SCTP_DISPOSITION_CONSUME ; 
 scalar_t__ SCTP_DISPOSITION_DISCARD ; 
 scalar_t__ SCTP_DISPOSITION_NOMEM ; 
 int /*<<< orphan*/  SCTP_STATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_STATE_SHUTDOWN_RECEIVED ; 
 int /*<<< orphan*/  SCTP_ULPEVENT (struct sctp_ulpevent*) ; 
 scalar_t__ TSN_lt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_add_cmd_sf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_chunk_length_valid (struct sctp_chunk*,int) ; 
 scalar_t__ sctp_outq_is_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ sctp_sf_do_9_2_shutdown_ack (struct sctp_endpoint const*,struct sctp_association const*,int /*<<< orphan*/  const,void*,int /*<<< orphan*/ *) ; 
 scalar_t__ sctp_sf_pdiscard (struct sctp_endpoint const*,struct sctp_association const*,int /*<<< orphan*/  const,void*,int /*<<< orphan*/ *) ; 
 scalar_t__ sctp_sf_violation_chunklen (struct sctp_endpoint const*,struct sctp_association const*,int /*<<< orphan*/  const,void*,int /*<<< orphan*/ *) ; 
 scalar_t__ sctp_sf_violation_ctsn (struct sctp_endpoint const*,struct sctp_association const*,int /*<<< orphan*/  const,void*,int /*<<< orphan*/ *) ; 
 struct sctp_ulpevent* sctp_ulpevent_make_shutdown_event (struct sctp_association const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_vtag_verify (struct sctp_chunk*,struct sctp_association const*) ; 
 int /*<<< orphan*/  skb_pull (TYPE_3__*,int) ; 

sctp_disposition_t sctp_sf_do_9_2_shutdown(const struct sctp_endpoint *ep,
					   const struct sctp_association *asoc,
					   const sctp_subtype_t type,
					   void *arg,
					   sctp_cmd_seq_t *commands)
{
	struct sctp_chunk *chunk = arg;
	sctp_shutdownhdr_t *sdh;
	sctp_disposition_t disposition;
	struct sctp_ulpevent *ev;
	__u32 ctsn;

	if (!sctp_vtag_verify(chunk, asoc))
		return sctp_sf_pdiscard(ep, asoc, type, arg, commands);

	/* Make sure that the SHUTDOWN chunk has a valid length. */
	if (!sctp_chunk_length_valid(chunk,
				      sizeof(struct sctp_shutdown_chunk_t)))
		return sctp_sf_violation_chunklen(ep, asoc, type, arg,
						  commands);

	/* Convert the elaborate header.  */
	sdh = (sctp_shutdownhdr_t *)chunk->skb->data;
	skb_pull(chunk->skb, sizeof(sctp_shutdownhdr_t));
	chunk->subh.shutdown_hdr = sdh;
	ctsn = ntohl(sdh->cum_tsn_ack);

	if (TSN_lt(ctsn, asoc->ctsn_ack_point)) {
		SCTP_DEBUG_PRINTK("ctsn %x\n", ctsn);
		SCTP_DEBUG_PRINTK("ctsn_ack_point %x\n", asoc->ctsn_ack_point);
		return SCTP_DISPOSITION_DISCARD;
	}

	/* If Cumulative TSN Ack beyond the max tsn currently
	 * send, terminating the association and respond to the
	 * sender with an ABORT.
	 */
	if (!TSN_lt(ctsn, asoc->next_tsn))
		return sctp_sf_violation_ctsn(ep, asoc, type, arg, commands);

	/* API 5.3.1.5 SCTP_SHUTDOWN_EVENT
	 * When a peer sends a SHUTDOWN, SCTP delivers this notification to
	 * inform the application that it should cease sending data.
	 */
	ev = sctp_ulpevent_make_shutdown_event(asoc, 0, GFP_ATOMIC);
	if (!ev) {
		disposition = SCTP_DISPOSITION_NOMEM;
		goto out;
	}
	sctp_add_cmd_sf(commands, SCTP_CMD_EVENT_ULP, SCTP_ULPEVENT(ev));

	/* Upon the reception of the SHUTDOWN, the peer endpoint shall
	 *  - enter the SHUTDOWN-RECEIVED state,
	 *  - stop accepting new data from its SCTP user
	 *
	 * [This is implicit in the new state.]
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_NEW_STATE,
			SCTP_STATE(SCTP_STATE_SHUTDOWN_RECEIVED));
	disposition = SCTP_DISPOSITION_CONSUME;

	if (sctp_outq_is_empty(&asoc->outqueue)) {
		disposition = sctp_sf_do_9_2_shutdown_ack(ep, asoc, type,
							  arg, commands);
	}

	if (SCTP_DISPOSITION_NOMEM == disposition)
		goto out;

	/*  - verify, by checking the Cumulative TSN Ack field of the
	 *    chunk, that all its outstanding DATA chunks have been
	 *    received by the SHUTDOWN sender.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_PROCESS_CTSN,
			SCTP_BE32(chunk->subh.shutdown_hdr->cum_tsn_ack));

out:
	return disposition;
}