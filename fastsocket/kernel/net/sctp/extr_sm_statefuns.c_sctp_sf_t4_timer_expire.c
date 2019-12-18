#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sctp_transport {int dummy; } ;
struct sctp_endpoint {int dummy; } ;
struct sctp_chunk {struct sctp_transport* transport; } ;
struct sctp_association {scalar_t__ overall_error_count; scalar_t__ max_retrans; struct sctp_chunk* addip_last_asconf; } ;
typedef  int /*<<< orphan*/  sctp_subtype_t ;
typedef  int /*<<< orphan*/  sctp_disposition_t ;
typedef  int /*<<< orphan*/  sctp_cmd_seq_t ;

/* Variables and functions */
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  SCTP_CHUNK (struct sctp_chunk*) ; 
 int /*<<< orphan*/  SCTP_CMD_ASSOC_FAILED ; 
 int /*<<< orphan*/  SCTP_CMD_REPLY ; 
 int /*<<< orphan*/  SCTP_CMD_SETUP_T4 ; 
 int /*<<< orphan*/  SCTP_CMD_SET_SK_ERR ; 
 int /*<<< orphan*/  SCTP_CMD_STRIKE ; 
 int /*<<< orphan*/  SCTP_CMD_TIMER_RESTART ; 
 int /*<<< orphan*/  SCTP_CMD_TIMER_STOP ; 
 int /*<<< orphan*/  SCTP_DEC_STATS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_DISPOSITION_ABORT ; 
 int /*<<< orphan*/  SCTP_DISPOSITION_CONSUME ; 
 int /*<<< orphan*/  SCTP_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_ERROR_NO_ERROR ; 
 int /*<<< orphan*/  SCTP_EVENT_TIMEOUT_T4_RTO ; 
 int /*<<< orphan*/  SCTP_INC_STATS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_MIB_ABORTEDS ; 
 int /*<<< orphan*/  SCTP_MIB_CURRESTAB ; 
 int /*<<< orphan*/  SCTP_MIB_T4_RTO_EXPIREDS ; 
 int /*<<< orphan*/  SCTP_PERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_TO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_TRANSPORT (struct sctp_transport*) ; 
 int /*<<< orphan*/  sctp_add_cmd_sf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_chunk_hold (struct sctp_chunk*) ; 

sctp_disposition_t sctp_sf_t4_timer_expire(
	const struct sctp_endpoint *ep,
	const struct sctp_association *asoc,
	const sctp_subtype_t type,
	void *arg,
	sctp_cmd_seq_t *commands)
{
	struct sctp_chunk *chunk = asoc->addip_last_asconf;
	struct sctp_transport *transport = chunk->transport;

	SCTP_INC_STATS(SCTP_MIB_T4_RTO_EXPIREDS);

	/* ADDIP 4.1 B1) Increment the error counters and perform path failure
	 * detection on the appropriate destination address as defined in
	 * RFC2960 [5] section 8.1 and 8.2.
	 */
	if (transport)
		sctp_add_cmd_sf(commands, SCTP_CMD_STRIKE,
				SCTP_TRANSPORT(transport));

	/* Reconfig T4 timer and transport. */
	sctp_add_cmd_sf(commands, SCTP_CMD_SETUP_T4, SCTP_CHUNK(chunk));

	/* ADDIP 4.1 B2) Increment the association error counters and perform
	 * endpoint failure detection on the association as defined in
	 * RFC2960 [5] section 8.1 and 8.2.
	 * association error counter is incremented in SCTP_CMD_STRIKE.
	 */
	if (asoc->overall_error_count >= asoc->max_retrans) {
		sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
				SCTP_TO(SCTP_EVENT_TIMEOUT_T4_RTO));
		sctp_add_cmd_sf(commands, SCTP_CMD_SET_SK_ERR,
				SCTP_ERROR(ETIMEDOUT));
		sctp_add_cmd_sf(commands, SCTP_CMD_ASSOC_FAILED,
				SCTP_PERR(SCTP_ERROR_NO_ERROR));
		SCTP_INC_STATS(SCTP_MIB_ABORTEDS);
		SCTP_DEC_STATS(SCTP_MIB_CURRESTAB);
		return SCTP_DISPOSITION_ABORT;
	}

	/* ADDIP 4.1 B3) Back-off the destination address RTO value to which
	 * the ASCONF chunk was sent by doubling the RTO timer value.
	 * This is done in SCTP_CMD_STRIKE.
	 */

	/* ADDIP 4.1 B4) Re-transmit the ASCONF Chunk last sent and if possible
	 * choose an alternate destination address (please refer to RFC2960
	 * [5] section 6.4.1). An endpoint MUST NOT add new parameters to this
	 * chunk, it MUST be the same (including its serial number) as the last
	 * ASCONF sent.
	 */
	sctp_chunk_hold(asoc->addip_last_asconf);
	sctp_add_cmd_sf(commands, SCTP_CMD_REPLY,
			SCTP_CHUNK(asoc->addip_last_asconf));

	/* ADDIP 4.1 B5) Restart the T-4 RTO timer. Note that if a different
	 * destination is selected, then the RTO used will be that of the new
	 * destination address.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_RESTART,
			SCTP_TO(SCTP_EVENT_TIMEOUT_T4_RTO));

	return SCTP_DISPOSITION_CONSUME;
}