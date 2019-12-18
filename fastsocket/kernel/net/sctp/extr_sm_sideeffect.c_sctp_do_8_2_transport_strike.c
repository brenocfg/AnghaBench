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
struct TYPE_4__ {int /*<<< orphan*/  sin_port; } ;
struct TYPE_6__ {TYPE_1__ v4; } ;
struct sctp_transport {scalar_t__ state; scalar_t__ error_count; scalar_t__ pathmaxrxt; int rto; TYPE_2__* asoc; scalar_t__ hb_sent; TYPE_3__ ipaddr; } ;
struct sctp_association {scalar_t__ pf_retrans; int /*<<< orphan*/  overall_error_count; } ;
typedef  int /*<<< orphan*/  sctp_cmd_seq_t ;
struct TYPE_5__ {int /*<<< orphan*/  rto_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_DEBUG_PRINTK_IPADDR (char*,char*,struct sctp_association*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_FAILED_THRESHOLD ; 
 scalar_t__ SCTP_INACTIVE ; 
 scalar_t__ SCTP_PF ; 
 int /*<<< orphan*/  SCTP_TRANSPORT_DOWN ; 
 int /*<<< orphan*/  SCTP_TRANSPORT_PF ; 
 scalar_t__ SCTP_UNCONFIRMED ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_assoc_control_transport (struct sctp_association*,struct sctp_transport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_cmd_hb_timer_update (int /*<<< orphan*/ *,struct sctp_transport*) ; 
 int /*<<< orphan*/  sctp_max_rto (struct sctp_association*,struct sctp_transport*) ; 

__attribute__((used)) static void sctp_do_8_2_transport_strike(sctp_cmd_seq_t *commands,
					 struct sctp_association *asoc,
					 struct sctp_transport *transport,
					 int is_hb)
{
	/* The check for association's overall error counter exceeding the
	 * threshold is done in the state function.
	 */
	/* We are here due to a timer expiration.  If the timer was
	 * not a HEARTBEAT, then normal error tracking is done.
	 * If the timer was a heartbeat, we only increment error counts
	 * when we already have an outstanding HEARTBEAT that has not
	 * been acknowledged.
	 * Additionaly, some tranport states inhibit error increments.
	 */
	if (!is_hb) {
		asoc->overall_error_count++;
		if (transport->state != SCTP_INACTIVE)
			transport->error_count++;
	 } else if (transport->hb_sent) {
		if (transport->state != SCTP_UNCONFIRMED)
			asoc->overall_error_count++;
		if (transport->state != SCTP_INACTIVE)
			transport->error_count++;
	}

	/* If the transport error count is greater than the pf_retrans
	 * threshold, and less than pathmaxrtx, then mark this transport
	 * as Partially Failed, ee SCTP Quick Failover Draft, secon 5.1,
	 * point 1
	 */
	if ((transport->state != SCTP_PF) &&
	   (asoc->pf_retrans < transport->pathmaxrxt) &&
	   (transport->error_count > asoc->pf_retrans)) {

		sctp_assoc_control_transport(asoc, transport,
					     SCTP_TRANSPORT_PF,
					     0);

		/* Update the hb timer to resend a heartbeat every rto */
		sctp_cmd_hb_timer_update(commands, transport);
	}

	if (transport->state != SCTP_INACTIVE &&
	    (transport->error_count > transport->pathmaxrxt)) {
		SCTP_DEBUG_PRINTK_IPADDR("transport_strike:association %p",
					 " transport IP: port:%d failed.\n",
					 asoc,
					 (&transport->ipaddr),
					 ntohs(transport->ipaddr.v4.sin_port));
		sctp_assoc_control_transport(asoc, transport,
					     SCTP_TRANSPORT_DOWN,
					     SCTP_FAILED_THRESHOLD);
	}

	/* E2) For the destination address for which the timer
	 * expires, set RTO <- RTO * 2 ("back off the timer").  The
	 * maximum value discussed in rule C7 above (RTO.max) may be
	 * used to provide an upper bound to this doubling operation.
	 *
	 * Special Case:  the first HB doesn't trigger exponential backoff.
	 * The first unacknowleged HB triggers it.  We do this with a flag
	 * that indicates that we have an outstanding HB.
	 */
	if (!is_hb || transport->hb_sent) {
		transport->rto = min((transport->rto * 2), transport->asoc->rto_max);
		sctp_max_rto(asoc, transport);
	}
}