#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct sock {int sk_rcvbuf; scalar_t__ sk_family; } ;
struct sctp_tsnmap {int dummy; } ;
struct TYPE_22__ {int /*<<< orphan*/  sinit_max_init_timeo; int /*<<< orphan*/  sinit_max_attempts; int /*<<< orphan*/  sinit_num_ostreams; int /*<<< orphan*/  sinit_max_instreams; } ;
struct TYPE_21__ {int /*<<< orphan*/  srto_min; int /*<<< orphan*/  srto_max; int /*<<< orphan*/  srto_initial; } ;
struct TYPE_20__ {int sasoc_cookie_life; int /*<<< orphan*/  sasoc_asocmaxrxt; } ;
struct sctp_sock {int /*<<< orphan*/  default_rcv_context; int /*<<< orphan*/  default_timetolive; int /*<<< orphan*/  default_context; int /*<<< orphan*/  default_flags; int /*<<< orphan*/  default_ppid; int /*<<< orphan*/  default_stream; scalar_t__ autoclose; TYPE_4__ initmsg; int /*<<< orphan*/  max_burst; int /*<<< orphan*/  param_flags; int /*<<< orphan*/  sackfreq; int /*<<< orphan*/  sackdelay; int /*<<< orphan*/  pathmtu; int /*<<< orphan*/  pathmaxrxt; int /*<<< orphan*/  hbinterval; TYPE_3__ rtoinfo; TYPE_2__ assocparams; int /*<<< orphan*/  user_frag; } ;
struct sctp_priv_assoc_stats {int dummy; } ;
struct TYPE_24__ {int /*<<< orphan*/  port; } ;
struct TYPE_25__ {TYPE_6__ bind_addr; } ;
struct sctp_endpoint {TYPE_13__* auth_chunk_list; TYPE_13__* auth_hmacs_list; int /*<<< orphan*/  active_key_id; TYPE_7__ base; } ;
struct TYPE_16__ {struct sock* sk; int /*<<< orphan*/  inqueue; int /*<<< orphan*/  bind_addr; scalar_t__ malloced; scalar_t__ dead; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  type; } ;
struct TYPE_15__ {scalar_t__ auth_random; int /*<<< orphan*/  auth_chunks; int /*<<< orphan*/  auth_hmacs; scalar_t__ initial_tsn; int /*<<< orphan*/  my_port; scalar_t__ peer_ttag; scalar_t__ my_ttag; scalar_t__ peer_vtag; int /*<<< orphan*/  my_vtag; int /*<<< orphan*/  sinit_num_ostreams; int /*<<< orphan*/  sinit_max_instreams; } ;
struct TYPE_23__ {scalar_t__ init_tag; } ;
struct TYPE_26__ {int sack_needed; int sack_generation; int asconf_capable; int ipv4_address; int ipv6_address; int /*<<< orphan*/  tsn_map; scalar_t__ sack_cnt; scalar_t__ transport_count; int /*<<< orphan*/  transport_addr_list; TYPE_5__ i; int /*<<< orphan*/  rwnd; } ;
struct TYPE_19__ {int tv_sec; int tv_usec; } ;
struct sctp_association {int rto_initial; int rto_max; int sackdelay; int* timeouts; int rwnd; int a_rwnd; TYPE_11__ base; struct sctp_endpoint* ep; TYPE_10__ c; scalar_t__ default_hmac_id; int /*<<< orphan*/ * asoc_shared_key; int /*<<< orphan*/  active_key_id; int /*<<< orphan*/  endpoint_shared_keys; int /*<<< orphan*/  stats; int /*<<< orphan*/  default_rcv_context; int /*<<< orphan*/  default_timetolive; int /*<<< orphan*/  default_context; int /*<<< orphan*/  default_flags; int /*<<< orphan*/  default_ppid; int /*<<< orphan*/  default_stream; scalar_t__ autoclose; int /*<<< orphan*/  asocs; TYPE_8__ peer; scalar_t__ assoc_id; scalar_t__ need_ecne; int /*<<< orphan*/  ulpq; int /*<<< orphan*/  outqueue; int /*<<< orphan*/  asconf_ack_list; int /*<<< orphan*/  addip_chunk_list; scalar_t__ addip_serial; scalar_t__ unack_data; scalar_t__ ctsn_ack_point; scalar_t__ last_cwr_tsn; scalar_t__ highest_sacked; scalar_t__ adv_peer_ack_point; scalar_t__ next_tsn; int /*<<< orphan*/  wait; int /*<<< orphan*/  rmem_alloc; scalar_t__ sndbuf_used; scalar_t__ rwnd_press; scalar_t__ rwnd_over; int /*<<< orphan*/ * ssnmap; void* max_init_timeo; int /*<<< orphan*/  max_init_attempts; int /*<<< orphan*/ * timers; int /*<<< orphan*/  max_burst; int /*<<< orphan*/  param_flags; int /*<<< orphan*/  sackfreq; int /*<<< orphan*/  pathmtu; int /*<<< orphan*/  pathmaxrxt; void* hbinterval; scalar_t__ overall_error_count; void* rto_min; int /*<<< orphan*/  pf_retrans; int /*<<< orphan*/  max_retrans; int /*<<< orphan*/  user_frag; scalar_t__ frag_point; TYPE_1__ cookie_life; int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  sctp_scope_t ;
struct TYPE_17__ {int /*<<< orphan*/  length; int /*<<< orphan*/  type; } ;
typedef  TYPE_12__ sctp_paramhdr_t ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_27__ {int /*<<< orphan*/  length; } ;
struct TYPE_18__ {TYPE_9__ param_hdr; } ;

/* Variables and functions */
 unsigned long HZ ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ PF_INET6 ; 
 scalar_t__ SCTP_AUTH_RANDOM_LENGTH ; 
 int /*<<< orphan*/  SCTP_DEFAULT_MAXWINDOW ; 
 int SCTP_DEFAULT_MINWINDOW ; 
 int /*<<< orphan*/  SCTP_EP_TYPE_ASSOCIATION ; 
 size_t SCTP_EVENT_TIMEOUT_AUTOCLOSE ; 
 size_t SCTP_EVENT_TIMEOUT_HEARTBEAT ; 
 size_t SCTP_EVENT_TIMEOUT_NONE ; 
 size_t SCTP_EVENT_TIMEOUT_SACK ; 
 size_t SCTP_EVENT_TIMEOUT_T1_COOKIE ; 
 size_t SCTP_EVENT_TIMEOUT_T1_INIT ; 
 size_t SCTP_EVENT_TIMEOUT_T2_SHUTDOWN ; 
 size_t SCTP_EVENT_TIMEOUT_T3_RTX ; 
 size_t SCTP_EVENT_TIMEOUT_T4_RTO ; 
 size_t SCTP_EVENT_TIMEOUT_T5_SHUTDOWN_GUARD ; 
 int SCTP_NUM_TIMEOUT_TYPES ; 
 int /*<<< orphan*/  SCTP_PARAM_RANDOM ; 
 int /*<<< orphan*/  SCTP_STATE_CLOSED ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_random_bytes (TYPE_12__*,scalar_t__) ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_13__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 void* msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_addip_noauth ; 
 int /*<<< orphan*/  sctp_assoc_bh_rcv ; 
 int sctp_auth_asoc_copy_shkeys (struct sctp_endpoint const*,struct sctp_association*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_bind_addr_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_endpoint_hold (struct sctp_endpoint*) ; 
 int /*<<< orphan*/  sctp_endpoint_put (struct sctp_endpoint*) ; 
 int /*<<< orphan*/  sctp_generate_tag (struct sctp_endpoint const*) ; 
 scalar_t__ sctp_generate_tsn (struct sctp_endpoint const*) ; 
 int /*<<< orphan*/  sctp_inq_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_inq_set_th_handler (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_outq_init (struct sctp_association*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_pf_retrans ; 
 struct sctp_sock* sctp_sk (struct sock*) ; 
 int /*<<< orphan*/ * sctp_timer_events ; 
 int /*<<< orphan*/  sctp_ulpq_init (int /*<<< orphan*/ *,struct sctp_association*) ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

__attribute__((used)) static struct sctp_association *sctp_association_init(struct sctp_association *asoc,
					  const struct sctp_endpoint *ep,
					  const struct sock *sk,
					  sctp_scope_t scope,
					  gfp_t gfp)
{
	struct sctp_sock *sp;
	int i;
	sctp_paramhdr_t *p;
	int err;

	/* Retrieve the SCTP per socket area.  */
	sp = sctp_sk((struct sock *)sk);

	/* Discarding const is appropriate here.  */
	asoc->ep = (struct sctp_endpoint *)ep;
	sctp_endpoint_hold(asoc->ep);

	/* Hold the sock.  */
	asoc->base.sk = (struct sock *)sk;
	sock_hold(asoc->base.sk);

	/* Initialize the common base substructure.  */
	asoc->base.type = SCTP_EP_TYPE_ASSOCIATION;

	/* Initialize the object handling fields.  */
	atomic_set(&asoc->base.refcnt, 1);
	asoc->base.dead = 0;
	asoc->base.malloced = 0;

	/* Initialize the bind addr area.  */
	sctp_bind_addr_init(&asoc->base.bind_addr, ep->base.bind_addr.port);

	asoc->state = SCTP_STATE_CLOSED;

	/* Set these values from the socket values, a conversion between
	 * millsecons to seconds/microseconds must also be done.
	 */
	asoc->cookie_life.tv_sec = sp->assocparams.sasoc_cookie_life / 1000;
	asoc->cookie_life.tv_usec = (sp->assocparams.sasoc_cookie_life % 1000)
					* 1000;
	asoc->frag_point = 0;
	asoc->user_frag = sp->user_frag;

	/* Set the association max_retrans and RTO values from the
	 * socket values.
	 */
	asoc->max_retrans = sp->assocparams.sasoc_asocmaxrxt;
	asoc->pf_retrans  = sctp_pf_retrans;

	asoc->rto_initial = msecs_to_jiffies(sp->rtoinfo.srto_initial);
	asoc->rto_max = msecs_to_jiffies(sp->rtoinfo.srto_max);
	asoc->rto_min = msecs_to_jiffies(sp->rtoinfo.srto_min);

	asoc->overall_error_count = 0;

	/* Initialize the association's heartbeat interval based on the
	 * sock configured value.
	 */
	asoc->hbinterval = msecs_to_jiffies(sp->hbinterval);

	/* Initialize path max retrans value. */
	asoc->pathmaxrxt = sp->pathmaxrxt;

	/* Initialize default path MTU. */
	asoc->pathmtu = sp->pathmtu;

	/* Set association default SACK delay */
	asoc->sackdelay = msecs_to_jiffies(sp->sackdelay);
	asoc->sackfreq = sp->sackfreq;

	/* Set the association default flags controlling
	 * Heartbeat, SACK delay, and Path MTU Discovery.
	 */
	asoc->param_flags = sp->param_flags;

	/* Initialize the maximum mumber of new data packets that can be sent
	 * in a burst.
	 */
	asoc->max_burst = sp->max_burst;

	/* initialize association timers */
	asoc->timeouts[SCTP_EVENT_TIMEOUT_NONE] = 0;
	asoc->timeouts[SCTP_EVENT_TIMEOUT_T1_COOKIE] = asoc->rto_initial;
	asoc->timeouts[SCTP_EVENT_TIMEOUT_T1_INIT] = asoc->rto_initial;
	asoc->timeouts[SCTP_EVENT_TIMEOUT_T2_SHUTDOWN] = asoc->rto_initial;
	asoc->timeouts[SCTP_EVENT_TIMEOUT_T3_RTX] = 0;
	asoc->timeouts[SCTP_EVENT_TIMEOUT_T4_RTO] = 0;

	/* sctpimpguide Section 2.12.2
	 * If the 'T5-shutdown-guard' timer is used, it SHOULD be set to the
	 * recommended value of 5 times 'RTO.Max'.
	 */
	asoc->timeouts[SCTP_EVENT_TIMEOUT_T5_SHUTDOWN_GUARD]
		= 5 * asoc->rto_max;

	asoc->timeouts[SCTP_EVENT_TIMEOUT_HEARTBEAT] = 0;
	asoc->timeouts[SCTP_EVENT_TIMEOUT_SACK] = asoc->sackdelay;
	asoc->timeouts[SCTP_EVENT_TIMEOUT_AUTOCLOSE] =
		(unsigned long)sp->autoclose * HZ;

	/* Initilizes the timers */
	for (i = SCTP_EVENT_TIMEOUT_NONE; i < SCTP_NUM_TIMEOUT_TYPES; ++i)
		setup_timer(&asoc->timers[i], sctp_timer_events[i],
				(unsigned long)asoc);

	/* Pull default initialization values from the sock options.
	 * Note: This assumes that the values have already been
	 * validated in the sock.
	 */
	asoc->c.sinit_max_instreams = sp->initmsg.sinit_max_instreams;
	asoc->c.sinit_num_ostreams  = sp->initmsg.sinit_num_ostreams;
	asoc->max_init_attempts	= sp->initmsg.sinit_max_attempts;

	asoc->max_init_timeo =
		 msecs_to_jiffies(sp->initmsg.sinit_max_init_timeo);

	/* Allocate storage for the ssnmap after the inbound and outbound
	 * streams have been negotiated during Init.
	 */
	asoc->ssnmap = NULL;

	/* Set the local window size for receive.
	 * This is also the rcvbuf space per association.
	 * RFC 6 - A SCTP receiver MUST be able to receive a minimum of
	 * 1500 bytes in one SCTP packet.
	 */
	if ((sk->sk_rcvbuf/2) < SCTP_DEFAULT_MINWINDOW)
		asoc->rwnd = SCTP_DEFAULT_MINWINDOW;
	else
		asoc->rwnd = sk->sk_rcvbuf/2;

	asoc->a_rwnd = asoc->rwnd;

	asoc->rwnd_over = 0;
	asoc->rwnd_press = 0;

	/* Use my own max window until I learn something better.  */
	asoc->peer.rwnd = SCTP_DEFAULT_MAXWINDOW;

	/* Set the sndbuf size for transmit.  */
	asoc->sndbuf_used = 0;

	/* Initialize the receive memory counter */
	atomic_set(&asoc->rmem_alloc, 0);

	init_waitqueue_head(&asoc->wait);

	asoc->c.my_vtag = sctp_generate_tag(ep);
	asoc->peer.i.init_tag = 0;     /* INIT needs a vtag of 0. */
	asoc->c.peer_vtag = 0;
	asoc->c.my_ttag   = 0;
	asoc->c.peer_ttag = 0;
	asoc->c.my_port = ep->base.bind_addr.port;

	asoc->c.initial_tsn = sctp_generate_tsn(ep);

	asoc->next_tsn = asoc->c.initial_tsn;

	asoc->ctsn_ack_point = asoc->next_tsn - 1;
	asoc->adv_peer_ack_point = asoc->ctsn_ack_point;
	asoc->highest_sacked = asoc->ctsn_ack_point;
	asoc->last_cwr_tsn = asoc->ctsn_ack_point;
	asoc->unack_data = 0;

	/* ADDIP Section 4.1 Asconf Chunk Procedures
	 *
	 * When an endpoint has an ASCONF signaled change to be sent to the
	 * remote endpoint it should do the following:
	 * ...
	 * A2) a serial number should be assigned to the chunk. The serial
	 * number SHOULD be a monotonically increasing number. The serial
	 * numbers SHOULD be initialized at the start of the
	 * association to the same value as the initial TSN.
	 */
	asoc->addip_serial = asoc->c.initial_tsn;

	INIT_LIST_HEAD(&asoc->addip_chunk_list);
	INIT_LIST_HEAD(&asoc->asconf_ack_list);

	/* Make an empty list of remote transport addresses.  */
	INIT_LIST_HEAD(&asoc->peer.transport_addr_list);
	asoc->peer.transport_count = 0;

	/* RFC 2960 5.1 Normal Establishment of an Association
	 *
	 * After the reception of the first data chunk in an
	 * association the endpoint must immediately respond with a
	 * sack to acknowledge the data chunk.  Subsequent
	 * acknowledgements should be done as described in Section
	 * 6.2.
	 *
	 * [We implement this by telling a new association that it
	 * already received one packet.]
	 */
	asoc->peer.sack_needed = 1;
	asoc->peer.sack_cnt = 0;
	asoc->peer.sack_generation = 1;

	/* Assume that the peer will tell us if he recognizes ASCONF
	 * as part of INIT exchange.
	 * The sctp_addip_noauth option is there for backward compatibilty
	 * and will revert old behavior.
	 */
	asoc->peer.asconf_capable = 0;
	if (sctp_addip_noauth)
		asoc->peer.asconf_capable = 1;

	/* Create an input queue.  */
	sctp_inq_init(&asoc->base.inqueue);
	sctp_inq_set_th_handler(&asoc->base.inqueue, sctp_assoc_bh_rcv);

	/* Create an output queue.  */
	sctp_outq_init(asoc, &asoc->outqueue);

	if (!sctp_ulpq_init(&asoc->ulpq, asoc))
		goto fail_init;

	memset(&asoc->peer.tsn_map, 0, sizeof(struct sctp_tsnmap));

	asoc->need_ecne = 0;

	asoc->assoc_id = 0;

	/* Assume that peer would support both address types unless we are
	 * told otherwise.
	 */
	asoc->peer.ipv4_address = 1;
	if (asoc->base.sk->sk_family == PF_INET6)
		asoc->peer.ipv6_address = 1;
	INIT_LIST_HEAD(&asoc->asocs);

	asoc->autoclose = sp->autoclose;

	asoc->default_stream = sp->default_stream;
	asoc->default_ppid = sp->default_ppid;
	asoc->default_flags = sp->default_flags;
	asoc->default_context = sp->default_context;
	asoc->default_timetolive = sp->default_timetolive;
	asoc->default_rcv_context = sp->default_rcv_context;

	/* SCTP_GET_ASSOC_STATS COUNTERS */
	memset(&asoc->stats, 0, sizeof(struct sctp_priv_assoc_stats));

	/* AUTH related initializations */
	INIT_LIST_HEAD(&asoc->endpoint_shared_keys);
	err = sctp_auth_asoc_copy_shkeys(ep, asoc, gfp);
	if (err)
		goto fail_init;

	asoc->active_key_id = ep->active_key_id;
	asoc->asoc_shared_key = NULL;

	asoc->default_hmac_id = 0;
	/* Save the hmacs and chunks list into this association */
	if (ep->auth_hmacs_list)
		memcpy(asoc->c.auth_hmacs, ep->auth_hmacs_list,
			ntohs(ep->auth_hmacs_list->param_hdr.length));
	if (ep->auth_chunk_list)
		memcpy(asoc->c.auth_chunks, ep->auth_chunk_list,
			ntohs(ep->auth_chunk_list->param_hdr.length));

	/* Get the AUTH random number for this association */
	p = (sctp_paramhdr_t *)asoc->c.auth_random;
	p->type = SCTP_PARAM_RANDOM;
	p->length = htons(sizeof(sctp_paramhdr_t) + SCTP_AUTH_RANDOM_LENGTH);
	get_random_bytes(p+1, SCTP_AUTH_RANDOM_LENGTH);

	return asoc;

fail_init:
	sctp_endpoint_put(asoc->ep);
	sock_put(asoc->base.sk);
	return NULL;
}