#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sctp_transport {int param_flags; int sackfreq; int /*<<< orphan*/  sackdelay; } ;
struct sctp_chunk {int dummy; } ;
struct TYPE_2__ {int sack_needed; int sack_cnt; int /*<<< orphan*/  tsn_map; struct sctp_transport* last_data_from; } ;
struct sctp_association {int param_flags; int sackfreq; TYPE_1__ peer; int /*<<< orphan*/  rwnd; int /*<<< orphan*/  a_rwnd; int /*<<< orphan*/  sackdelay; int /*<<< orphan*/ * timeouts; } ;
typedef  int /*<<< orphan*/  sctp_cmd_seq_t ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SCTP_CHUNK (struct sctp_chunk*) ; 
 int /*<<< orphan*/  SCTP_CMD_REPLY ; 
 int /*<<< orphan*/  SCTP_CMD_TIMER_RESTART ; 
 int /*<<< orphan*/  SCTP_CMD_TIMER_STOP ; 
 size_t SCTP_EVENT_TIMEOUT_SACK ; 
 int /*<<< orphan*/  SCTP_TO (size_t) ; 
 int SPP_SACKDELAY_DISABLE ; 
 int /*<<< orphan*/  sctp_add_cmd_sf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sctp_chunk* sctp_make_sack (struct sctp_association*) ; 
 scalar_t__ sctp_tsnmap_get_ctsn (int /*<<< orphan*/ *) ; 
 scalar_t__ sctp_tsnmap_get_max_tsn_seen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sctp_gen_sack(struct sctp_association *asoc, int force,
			 sctp_cmd_seq_t *commands)
{
	__u32 ctsn, max_tsn_seen;
	struct sctp_chunk *sack;
	struct sctp_transport *trans = asoc->peer.last_data_from;
	int error = 0;

	if (force ||
	    (!trans && (asoc->param_flags & SPP_SACKDELAY_DISABLE)) ||
	    (trans && (trans->param_flags & SPP_SACKDELAY_DISABLE)))
		asoc->peer.sack_needed = 1;

	ctsn = sctp_tsnmap_get_ctsn(&asoc->peer.tsn_map);
	max_tsn_seen = sctp_tsnmap_get_max_tsn_seen(&asoc->peer.tsn_map);

	/* From 12.2 Parameters necessary per association (i.e. the TCB):
	 *
	 * Ack State : This flag indicates if the next received packet
	 * 	     : is to be responded to with a SACK. ...
	 *	     : When DATA chunks are out of order, SACK's
	 *           : are not delayed (see Section 6).
	 *
	 * [This is actually not mentioned in Section 6, but we
	 * implement it here anyway. --piggy]
	 */
	if (max_tsn_seen != ctsn)
		asoc->peer.sack_needed = 1;

	/* From 6.2  Acknowledgement on Reception of DATA Chunks:
	 *
	 * Section 4.2 of [RFC2581] SHOULD be followed. Specifically,
	 * an acknowledgement SHOULD be generated for at least every
	 * second packet (not every second DATA chunk) received, and
	 * SHOULD be generated within 200 ms of the arrival of any
	 * unacknowledged DATA chunk. ...
	 */
	if (!asoc->peer.sack_needed) {
		asoc->peer.sack_cnt++;

		/* Set the SACK delay timeout based on the
		 * SACK delay for the last transport
		 * data was received from, or the default
		 * for the association.
		 */
		if (trans) {
			/* We will need a SACK for the next packet.  */
			if (asoc->peer.sack_cnt >= trans->sackfreq - 1)
				asoc->peer.sack_needed = 1;

			asoc->timeouts[SCTP_EVENT_TIMEOUT_SACK] =
				trans->sackdelay;
		} else {
			/* We will need a SACK for the next packet.  */
			if (asoc->peer.sack_cnt >= asoc->sackfreq - 1)
				asoc->peer.sack_needed = 1;

			asoc->timeouts[SCTP_EVENT_TIMEOUT_SACK] =
				asoc->sackdelay;
		}

		/* Restart the SACK timer. */
		sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_RESTART,
				SCTP_TO(SCTP_EVENT_TIMEOUT_SACK));
	} else {
		asoc->a_rwnd = asoc->rwnd;
		sack = sctp_make_sack(asoc);
		if (!sack)
			goto nomem;

		asoc->peer.sack_needed = 0;
		asoc->peer.sack_cnt = 0;

		sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(sack));

		/* Stop the SACK timer.  */
		sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
				SCTP_TO(SCTP_EVENT_TIMEOUT_SACK));
	}

	return error;
nomem:
	error = -ENOMEM;
	return error;
}