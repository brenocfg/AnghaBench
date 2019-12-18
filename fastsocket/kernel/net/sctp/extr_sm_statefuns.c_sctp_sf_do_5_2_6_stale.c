#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int time_t ;
struct sctp_endpoint {int dummy; } ;
struct sctp_chunk {TYPE_1__* skb; } ;
struct sctp_bind_addr {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  primary_path; } ;
struct TYPE_9__ {int /*<<< orphan*/  bind_addr; } ;
struct sctp_association {int init_err_counter; int max_init_attempts; TYPE_4__ peer; TYPE_3__ base; } ;
typedef  int /*<<< orphan*/  sctp_subtype_t ;
typedef  int /*<<< orphan*/  sctp_errhdr_t ;
typedef  int /*<<< orphan*/  sctp_disposition_t ;
struct TYPE_8__ {int /*<<< orphan*/  length; int /*<<< orphan*/  type; } ;
struct TYPE_11__ {int /*<<< orphan*/  lifespan_increment; TYPE_2__ param_hdr; } ;
typedef  TYPE_5__ sctp_cookie_preserve_param_t ;
typedef  int /*<<< orphan*/  sctp_cmd_seq_t ;
typedef  int /*<<< orphan*/  bht ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_7__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  SCTP_CHUNK (struct sctp_chunk*) ; 
 int /*<<< orphan*/  SCTP_CMD_CLEAR_INIT_TAG ; 
 int /*<<< orphan*/  SCTP_CMD_DEL_NON_PRIMARY ; 
 int /*<<< orphan*/  SCTP_CMD_HB_TIMERS_STOP ; 
 int /*<<< orphan*/  SCTP_CMD_INIT_COUNTER_INC ; 
 int /*<<< orphan*/  SCTP_CMD_INIT_FAILED ; 
 int /*<<< orphan*/  SCTP_CMD_NEW_STATE ; 
 int /*<<< orphan*/  SCTP_CMD_REPLY ; 
 int /*<<< orphan*/  SCTP_CMD_SET_SK_ERR ; 
 int /*<<< orphan*/  SCTP_CMD_T1_RETRAN ; 
 int /*<<< orphan*/  SCTP_CMD_T3_RTX_TIMERS_STOP ; 
 int /*<<< orphan*/  SCTP_CMD_TIMER_START ; 
 int /*<<< orphan*/  SCTP_CMD_TIMER_STOP ; 
 int /*<<< orphan*/  SCTP_DISPOSITION_CONSUME ; 
 int /*<<< orphan*/  SCTP_DISPOSITION_DELETE_TCB ; 
 int /*<<< orphan*/  SCTP_DISPOSITION_NOMEM ; 
 int /*<<< orphan*/  SCTP_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_ERROR_STALE_COOKIE ; 
 int /*<<< orphan*/  SCTP_EVENT_TIMEOUT_T1_COOKIE ; 
 int /*<<< orphan*/  SCTP_EVENT_TIMEOUT_T1_INIT ; 
 int /*<<< orphan*/  SCTP_NULL () ; 
 int /*<<< orphan*/  SCTP_PARAM_COOKIE_PRESERVATIVE ; 
 int /*<<< orphan*/  SCTP_PERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_STATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_STATE_COOKIE_WAIT ; 
 int /*<<< orphan*/  SCTP_TO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_TRANSPORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  htons (int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_add_cmd_sf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_addto_chunk (struct sctp_chunk*,int,TYPE_5__*) ; 
 struct sctp_chunk* sctp_make_init (struct sctp_association const*,struct sctp_bind_addr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static sctp_disposition_t sctp_sf_do_5_2_6_stale(const struct sctp_endpoint *ep,
						 const struct sctp_association *asoc,
						 const sctp_subtype_t type,
						 void *arg,
						 sctp_cmd_seq_t *commands)
{
	struct sctp_chunk *chunk = arg;
	time_t stale;
	sctp_cookie_preserve_param_t bht;
	sctp_errhdr_t *err;
	struct sctp_chunk *reply;
	struct sctp_bind_addr *bp;
	int attempts = asoc->init_err_counter + 1;

	if (attempts > asoc->max_init_attempts) {
		sctp_add_cmd_sf(commands, SCTP_CMD_SET_SK_ERR,
				SCTP_ERROR(ETIMEDOUT));
		sctp_add_cmd_sf(commands, SCTP_CMD_INIT_FAILED,
				SCTP_PERR(SCTP_ERROR_STALE_COOKIE));
		return SCTP_DISPOSITION_DELETE_TCB;
	}

	err = (sctp_errhdr_t *)(chunk->skb->data);

	/* When calculating the time extension, an implementation
	 * SHOULD use the RTT information measured based on the
	 * previous COOKIE ECHO / ERROR exchange, and should add no
	 * more than 1 second beyond the measured RTT, due to long
	 * State Cookie lifetimes making the endpoint more subject to
	 * a replay attack.
	 * Measure of Staleness's unit is usec. (1/1000000 sec)
	 * Suggested Cookie Life-span Increment's unit is msec.
	 * (1/1000 sec)
	 * In general, if you use the suggested cookie life, the value
	 * found in the field of measure of staleness should be doubled
	 * to give ample time to retransmit the new cookie and thus
	 * yield a higher probability of success on the reattempt.
	 */
	stale = ntohl(*(__be32 *)((u8 *)err + sizeof(sctp_errhdr_t)));
	stale = (stale * 2) / 1000;

	bht.param_hdr.type = SCTP_PARAM_COOKIE_PRESERVATIVE;
	bht.param_hdr.length = htons(sizeof(bht));
	bht.lifespan_increment = htonl(stale);

	/* Build that new INIT chunk.  */
	bp = (struct sctp_bind_addr *) &asoc->base.bind_addr;
	reply = sctp_make_init(asoc, bp, GFP_ATOMIC, sizeof(bht));
	if (!reply)
		goto nomem;

	sctp_addto_chunk(reply, sizeof(bht), &bht);

	/* Clear peer's init_tag cached in assoc as we are sending a new INIT */
	sctp_add_cmd_sf(commands, SCTP_CMD_CLEAR_INIT_TAG, SCTP_NULL());

	/* Stop pending T3-rtx and heartbeat timers */
	sctp_add_cmd_sf(commands, SCTP_CMD_T3_RTX_TIMERS_STOP, SCTP_NULL());
	sctp_add_cmd_sf(commands, SCTP_CMD_HB_TIMERS_STOP, SCTP_NULL());

	/* Delete non-primary peer ip addresses since we are transitioning
	 * back to the COOKIE-WAIT state
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_DEL_NON_PRIMARY, SCTP_NULL());

	/* If we've sent any data bundled with COOKIE-ECHO we will need to
	 * resend
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_T1_RETRAN,
			SCTP_TRANSPORT(asoc->peer.primary_path));

	/* Cast away the const modifier, as we want to just
	 * rerun it through as a sideffect.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_INIT_COUNTER_INC, SCTP_NULL());

	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
			SCTP_TO(SCTP_EVENT_TIMEOUT_T1_COOKIE));
	sctp_add_cmd_sf(commands, SCTP_CMD_NEW_STATE,
			SCTP_STATE(SCTP_STATE_COOKIE_WAIT));
	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_START,
			SCTP_TO(SCTP_EVENT_TIMEOUT_T1_INIT));

	sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(reply));

	return SCTP_DISPOSITION_CONSUME;

nomem:
	return SCTP_DISPOSITION_NOMEM;
}