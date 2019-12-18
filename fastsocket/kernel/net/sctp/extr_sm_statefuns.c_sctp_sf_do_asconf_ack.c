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
struct sctp_paramhdr {int dummy; } ;
struct sctp_endpoint {int dummy; } ;
struct TYPE_5__ {scalar_t__ addip_hdr; } ;
struct sctp_chunk {TYPE_2__ subh; scalar_t__ chunk_end; TYPE_1__* skb; int /*<<< orphan*/  auth; } ;
struct sctp_association {scalar_t__ addip_serial; struct sctp_chunk* addip_last_asconf; } ;
typedef  int /*<<< orphan*/  sctp_subtype_t ;
typedef  int /*<<< orphan*/  sctp_paramhdr_t ;
typedef  int /*<<< orphan*/  sctp_errhdr_t ;
typedef  int /*<<< orphan*/  sctp_disposition_t ;
typedef  int /*<<< orphan*/  sctp_cmd_seq_t ;
struct TYPE_6__ {int /*<<< orphan*/  serial; scalar_t__ params; } ;
typedef  TYPE_3__ sctp_addiphdr_t ;
typedef  int /*<<< orphan*/  sctp_addip_chunk_t ;
typedef  scalar_t__ __u32 ;
struct TYPE_4__ {scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ ADDIP_SERIAL_gte (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ECONNABORTED ; 
 int /*<<< orphan*/  SCTP_CHUNK (struct sctp_chunk*) ; 
 int /*<<< orphan*/  SCTP_CMD_ASSOC_FAILED ; 
 int /*<<< orphan*/  SCTP_CMD_DISCARD_PACKET ; 
 int /*<<< orphan*/  SCTP_CMD_REPLY ; 
 int /*<<< orphan*/  SCTP_CMD_REPORT_BAD_TAG ; 
 int /*<<< orphan*/  SCTP_CMD_SEND_NEXT_ASCONF ; 
 int /*<<< orphan*/  SCTP_CMD_SET_SK_ERR ; 
 int /*<<< orphan*/  SCTP_CMD_TIMER_STOP ; 
 int /*<<< orphan*/  SCTP_DEC_STATS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_DISPOSITION_ABORT ; 
 int /*<<< orphan*/  SCTP_DISPOSITION_CONSUME ; 
 int /*<<< orphan*/  SCTP_DISPOSITION_DISCARD ; 
 int /*<<< orphan*/  SCTP_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_ERROR_ASCONF_ACK ; 
 int /*<<< orphan*/  SCTP_ERROR_RSRC_LOW ; 
 int /*<<< orphan*/  SCTP_EVENT_TIMEOUT_T4_RTO ; 
 int /*<<< orphan*/  SCTP_INC_STATS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_MIB_ABORTEDS ; 
 int /*<<< orphan*/  SCTP_MIB_CURRESTAB ; 
 int /*<<< orphan*/  SCTP_NULL () ; 
 int /*<<< orphan*/  SCTP_PERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_TO (int /*<<< orphan*/ ) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_add_cmd_sf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_addip_noauth ; 
 int /*<<< orphan*/  sctp_chunk_length_valid (struct sctp_chunk*,int) ; 
 int /*<<< orphan*/  sctp_init_cause (struct sctp_chunk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sctp_chunk* sctp_make_abort (struct sctp_association const*,struct sctp_chunk*,int) ; 
 int /*<<< orphan*/  sctp_process_asconf_ack (struct sctp_association*,struct sctp_chunk*) ; 
 int /*<<< orphan*/  sctp_sf_discard_chunk (struct sctp_endpoint const*,struct sctp_association const*,int /*<<< orphan*/  const,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_sf_pdiscard (struct sctp_endpoint const*,struct sctp_association const*,int /*<<< orphan*/  const,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_sf_violation_chunklen (struct sctp_endpoint const*,struct sctp_association const*,int /*<<< orphan*/  const,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_sf_violation_paramlen (struct sctp_endpoint const*,struct sctp_association const*,int /*<<< orphan*/  const,void*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_verify_asconf (struct sctp_association const*,int /*<<< orphan*/ *,void*,struct sctp_paramhdr**) ; 
 int /*<<< orphan*/  sctp_vtag_verify (struct sctp_chunk*,struct sctp_association const*) ; 

sctp_disposition_t sctp_sf_do_asconf_ack(const struct sctp_endpoint *ep,
					 const struct sctp_association *asoc,
					 const sctp_subtype_t type, void *arg,
					 sctp_cmd_seq_t *commands)
{
	struct sctp_chunk	*asconf_ack = arg;
	struct sctp_chunk	*last_asconf = asoc->addip_last_asconf;
	struct sctp_chunk	*abort;
	struct sctp_paramhdr	*err_param = NULL;
	sctp_addiphdr_t		*addip_hdr;
	__u32			sent_serial, rcvd_serial;

	if (!sctp_vtag_verify(asconf_ack, asoc)) {
		sctp_add_cmd_sf(commands, SCTP_CMD_REPORT_BAD_TAG,
				SCTP_NULL());
		return sctp_sf_pdiscard(ep, asoc, type, arg, commands);
	}

	/* ADD-IP, Section 4.1.2:
	 * This chunk MUST be sent in an authenticated way by using
	 * the mechanism defined in [I-D.ietf-tsvwg-sctp-auth]. If this chunk
	 * is received unauthenticated it MUST be silently discarded as
	 * described in [I-D.ietf-tsvwg-sctp-auth].
	 */
	if (!sctp_addip_noauth && !asconf_ack->auth)
		return sctp_sf_discard_chunk(ep, asoc, type, arg, commands);

	/* Make sure that the ADDIP chunk has a valid length.  */
	if (!sctp_chunk_length_valid(asconf_ack, sizeof(sctp_addip_chunk_t)))
		return sctp_sf_violation_chunklen(ep, asoc, type, arg,
						  commands);

	addip_hdr = (sctp_addiphdr_t *)asconf_ack->skb->data;
	rcvd_serial = ntohl(addip_hdr->serial);

	/* Verify the ASCONF-ACK chunk before processing it. */
	if (!sctp_verify_asconf(asoc,
	    (sctp_paramhdr_t *)addip_hdr->params,
	    (void *)asconf_ack->chunk_end,
	    &err_param))
		return sctp_sf_violation_paramlen(ep, asoc, type, arg,
			   (void *)err_param, commands);

	if (last_asconf) {
		addip_hdr = (sctp_addiphdr_t *)last_asconf->subh.addip_hdr;
		sent_serial = ntohl(addip_hdr->serial);
	} else {
		sent_serial = asoc->addip_serial - 1;
	}

	/* D0) If an endpoint receives an ASCONF-ACK that is greater than or
	 * equal to the next serial number to be used but no ASCONF chunk is
	 * outstanding the endpoint MUST ABORT the association. Note that a
	 * sequence number is greater than if it is no more than 2^^31-1
	 * larger than the current sequence number (using serial arithmetic).
	 */
	if (ADDIP_SERIAL_gte(rcvd_serial, sent_serial + 1) &&
	    !(asoc->addip_last_asconf)) {
		abort = sctp_make_abort(asoc, asconf_ack,
					sizeof(sctp_errhdr_t));
		if (abort) {
			sctp_init_cause(abort, SCTP_ERROR_ASCONF_ACK, 0);
			sctp_add_cmd_sf(commands, SCTP_CMD_REPLY,
					SCTP_CHUNK(abort));
		}
		/* We are going to ABORT, so we might as well stop
		 * processing the rest of the chunks in the packet.
		 */
		sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
				SCTP_TO(SCTP_EVENT_TIMEOUT_T4_RTO));
		sctp_add_cmd_sf(commands, SCTP_CMD_DISCARD_PACKET,SCTP_NULL());
		sctp_add_cmd_sf(commands, SCTP_CMD_SET_SK_ERR,
				SCTP_ERROR(ECONNABORTED));
		sctp_add_cmd_sf(commands, SCTP_CMD_ASSOC_FAILED,
				SCTP_PERR(SCTP_ERROR_ASCONF_ACK));
		SCTP_INC_STATS(SCTP_MIB_ABORTEDS);
		SCTP_DEC_STATS(SCTP_MIB_CURRESTAB);
		return SCTP_DISPOSITION_ABORT;
	}

	if ((rcvd_serial == sent_serial) && asoc->addip_last_asconf) {
		sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
				SCTP_TO(SCTP_EVENT_TIMEOUT_T4_RTO));

		if (!sctp_process_asconf_ack((struct sctp_association *)asoc,
					     asconf_ack)) {
			/* Successfully processed ASCONF_ACK.  We can
			 * release the next asconf if we have one.
			 */
			sctp_add_cmd_sf(commands, SCTP_CMD_SEND_NEXT_ASCONF,
					SCTP_NULL());
			return SCTP_DISPOSITION_CONSUME;
		}

		abort = sctp_make_abort(asoc, asconf_ack,
					sizeof(sctp_errhdr_t));
		if (abort) {
			sctp_init_cause(abort, SCTP_ERROR_RSRC_LOW, 0);
			sctp_add_cmd_sf(commands, SCTP_CMD_REPLY,
					SCTP_CHUNK(abort));
		}
		/* We are going to ABORT, so we might as well stop
		 * processing the rest of the chunks in the packet.
		 */
		sctp_add_cmd_sf(commands, SCTP_CMD_DISCARD_PACKET,SCTP_NULL());
		sctp_add_cmd_sf(commands, SCTP_CMD_SET_SK_ERR,
				SCTP_ERROR(ECONNABORTED));
		sctp_add_cmd_sf(commands, SCTP_CMD_ASSOC_FAILED,
				SCTP_PERR(SCTP_ERROR_ASCONF_ACK));
		SCTP_INC_STATS(SCTP_MIB_ABORTEDS);
		SCTP_DEC_STATS(SCTP_MIB_CURRESTAB);
		return SCTP_DISPOSITION_ABORT;
	}

	return SCTP_DISPOSITION_DISCARD;
}