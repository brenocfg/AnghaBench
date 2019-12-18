#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sa_family; } ;
union sctp_addr {TYPE_1__ sa; } ;
struct TYPE_5__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct sctp_transport {int param_flags; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  hb_nonce; TYPE_2__ proto_unreach_timer; TYPE_2__ hb_timer; TYPE_2__ T3_rtx_timer; int /*<<< orphan*/  transports; int /*<<< orphan*/  send_ready; int /*<<< orphan*/  transmitted; int /*<<< orphan*/  pf_retrans; int /*<<< orphan*/  pathmaxrxt; void* last_time_ecne_reduced; void* last_time_heard; int /*<<< orphan*/  rto; scalar_t__ sack_generation; int /*<<< orphan*/  saddr; int /*<<< orphan*/  af_specific; union sctp_addr ipaddr; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int SPP_HB_DISABLE ; 
 int SPP_PMTUD_ENABLE ; 
 int SPP_SACKDELAY_ENABLE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_timer (TYPE_2__*) ; 
 void* jiffies ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_generate_heartbeat_event ; 
 int /*<<< orphan*/  sctp_generate_proto_unreach_event ; 
 int /*<<< orphan*/  sctp_generate_t3_rtx_event ; 
 int /*<<< orphan*/  sctp_get_af_specific (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_max_retrans_path ; 
 int /*<<< orphan*/  sctp_pf_retrans ; 
 int /*<<< orphan*/  sctp_rto_initial ; 
 int /*<<< orphan*/  setup_timer (TYPE_2__*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static struct sctp_transport *sctp_transport_init(struct sctp_transport *peer,
						  const union sctp_addr *addr,
						  gfp_t gfp)
{
	/* Copy in the address.  */
	peer->ipaddr = *addr;
	peer->af_specific = sctp_get_af_specific(addr->sa.sa_family);
	memset(&peer->saddr, 0, sizeof(union sctp_addr));

	peer->sack_generation = 0;

	/* From 6.3.1 RTO Calculation:
	 *
	 * C1) Until an RTT measurement has been made for a packet sent to the
	 * given destination transport address, set RTO to the protocol
	 * parameter 'RTO.Initial'.
	 */
	peer->rto = msecs_to_jiffies(sctp_rto_initial);

	peer->last_time_heard = jiffies;
	peer->last_time_ecne_reduced = jiffies;

	peer->param_flags = SPP_HB_DISABLE |
			    SPP_PMTUD_ENABLE |
			    SPP_SACKDELAY_ENABLE;

	/* Initialize the default path max_retrans.  */
	peer->pathmaxrxt  = sctp_max_retrans_path;
	peer->pf_retrans  = sctp_pf_retrans;

	INIT_LIST_HEAD(&peer->transmitted);
	INIT_LIST_HEAD(&peer->send_ready);
	INIT_LIST_HEAD(&peer->transports);

	setup_timer(&peer->T3_rtx_timer, sctp_generate_t3_rtx_event,
			(unsigned long)peer);
	setup_timer(&peer->hb_timer, sctp_generate_heartbeat_event,
			(unsigned long)peer);
	setup_timer(&peer->proto_unreach_timer,
		    sctp_generate_proto_unreach_event, (unsigned long)peer);

	init_timer(&peer->proto_unreach_timer);
        peer->proto_unreach_timer.function = sctp_generate_proto_unreach_event;
	peer->proto_unreach_timer.data = (unsigned long)peer;

	/* Initialize the 64-bit random nonce sent with heartbeat. */
	get_random_bytes(&peer->hb_nonce, sizeof(peer->hb_nonce));

	atomic_set(&peer->refcnt, 1);

	return peer;
}