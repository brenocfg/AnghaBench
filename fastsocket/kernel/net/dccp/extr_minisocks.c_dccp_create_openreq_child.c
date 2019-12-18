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
struct sock {int /*<<< orphan*/ * sk_destruct; } ;
struct sk_buff {int dummy; } ;
struct request_sock {int dummy; } ;
struct inet_connection_sock {int /*<<< orphan*/  icsk_rto; } ;
struct dccp_sock {int /*<<< orphan*/  dccps_iss; int /*<<< orphan*/  dccps_awl; int /*<<< orphan*/  dccps_isr; int /*<<< orphan*/  dccps_swl; int /*<<< orphan*/  dccps_gar; int /*<<< orphan*/  dccps_featneg; int /*<<< orphan*/  dccps_timestamp_time; int /*<<< orphan*/  dccps_timestamp_echo; int /*<<< orphan*/  dccps_service; int /*<<< orphan*/ * dccps_service_list; int /*<<< orphan*/ * dccps_hc_rx_ackvec; int /*<<< orphan*/  dccps_role; } ;
struct dccp_request_sock {int /*<<< orphan*/  dreq_featneg; int /*<<< orphan*/  dreq_isr; int /*<<< orphan*/  dreq_iss; int /*<<< orphan*/  dreq_timestamp_time; int /*<<< orphan*/  dreq_timestamp_echo; int /*<<< orphan*/  dreq_service; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCCP_INC_STATS_BH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DCCP_MIB_PASSIVEOPENS ; 
 int /*<<< orphan*/  DCCP_ROLE_SERVER ; 
 int /*<<< orphan*/  DCCP_TIMEOUT_INIT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ dccp_feat_activate_values (struct sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dccp_init_xmit_timers (struct sock*) ; 
 struct dccp_request_sock* dccp_rsk (struct request_sock const*) ; 
 int /*<<< orphan*/  dccp_set_seqno (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 
 int /*<<< orphan*/  dccp_update_gsr (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dccp_update_gss (struct sock*,int /*<<< orphan*/ ) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 struct sock* inet_csk_clone (struct sock*,struct request_sock const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max48 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_free (struct sock*) ; 

struct sock *dccp_create_openreq_child(struct sock *sk,
				       const struct request_sock *req,
				       const struct sk_buff *skb)
{
	/*
	 * Step 3: Process LISTEN state
	 *
	 *   (* Generate a new socket and switch to that socket *)
	 *   Set S := new socket for this port pair
	 */
	struct sock *newsk = inet_csk_clone(sk, req, GFP_ATOMIC);

	if (newsk != NULL) {
		struct dccp_request_sock *dreq = dccp_rsk(req);
		struct inet_connection_sock *newicsk = inet_csk(newsk);
		struct dccp_sock *newdp = dccp_sk(newsk);

		newdp->dccps_role	    = DCCP_ROLE_SERVER;
		newdp->dccps_hc_rx_ackvec   = NULL;
		newdp->dccps_service_list   = NULL;
		newdp->dccps_service	    = dreq->dreq_service;
		newdp->dccps_timestamp_echo = dreq->dreq_timestamp_echo;
		newdp->dccps_timestamp_time = dreq->dreq_timestamp_time;
		newicsk->icsk_rto	    = DCCP_TIMEOUT_INIT;

		INIT_LIST_HEAD(&newdp->dccps_featneg);
		/*
		 * Step 3: Process LISTEN state
		 *
		 *    Choose S.ISS (initial seqno) or set from Init Cookies
		 *    Initialize S.GAR := S.ISS
		 *    Set S.ISR, S.GSR, S.SWL, S.SWH from packet or Init Cookies
		 */
		newdp->dccps_gar = newdp->dccps_iss = dreq->dreq_iss;
		dccp_update_gss(newsk, dreq->dreq_iss);

		newdp->dccps_isr = dreq->dreq_isr;
		dccp_update_gsr(newsk, dreq->dreq_isr);

		/*
		 * SWL and AWL are initially adjusted so that they are not less than
		 * the initial Sequence Numbers received and sent, respectively:
		 *	SWL := max(GSR + 1 - floor(W/4), ISR),
		 *	AWL := max(GSS - W' + 1, ISS).
		 * These adjustments MUST be applied only at the beginning of the
		 * connection.
		 */
		dccp_set_seqno(&newdp->dccps_swl,
			       max48(newdp->dccps_swl, newdp->dccps_isr));
		dccp_set_seqno(&newdp->dccps_awl,
			       max48(newdp->dccps_awl, newdp->dccps_iss));

		/*
		 * Activate features after initialising the sequence numbers,
		 * since CCID initialisation may depend on GSS, ISR, ISS etc.
		 */
		if (dccp_feat_activate_values(newsk, &dreq->dreq_featneg)) {
			/* It is still raw copy of parent, so invalidate
			 * destructor and make plain sk_free() */
			newsk->sk_destruct = NULL;
			sk_free(newsk);
			return NULL;
		}
		dccp_init_xmit_timers(newsk);

		DCCP_INC_STATS_BH(DCCP_MIB_PASSIVEOPENS);
	}
	return newsk;
}