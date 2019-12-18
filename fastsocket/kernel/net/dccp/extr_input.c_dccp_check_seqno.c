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
typedef  scalar_t__ u64 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct dccp_sock {scalar_t__ dccps_awl; scalar_t__ dccps_swl; scalar_t__ dccps_gsr; scalar_t__ dccps_gar; unsigned long dccps_rate_last; scalar_t__ dccps_awh; scalar_t__ dccps_swh; } ;
struct dccp_hdr {scalar_t__ dccph_type; } ;
struct TYPE_2__ {scalar_t__ dccpd_seq; scalar_t__ dccpd_ack_seq; } ;

/* Variables and functions */
 scalar_t__ ADD48 (scalar_t__,int) ; 
 scalar_t__ DCCP_PKT_CLOSE ; 
 scalar_t__ DCCP_PKT_CLOSEREQ ; 
 scalar_t__ DCCP_PKT_RESET ; 
 scalar_t__ DCCP_PKT_SYNC ; 
 scalar_t__ DCCP_PKT_SYNCACK ; 
 scalar_t__ DCCP_PKT_WITHOUT_ACK_SEQ ; 
 TYPE_1__* DCCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  DCCP_WARN (char*,int /*<<< orphan*/ ,unsigned long long,unsigned long long,unsigned long long,char*,unsigned long long,unsigned long long,unsigned long long) ; 
 scalar_t__ between48 (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ dccp_delta_seqno (scalar_t__,scalar_t__) ; 
 struct dccp_hdr* dccp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_packet_name (scalar_t__) ; 
 int /*<<< orphan*/  dccp_send_sync (struct sock*,scalar_t__,scalar_t__) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 
 int /*<<< orphan*/  dccp_update_gsr (struct sock*,scalar_t__) ; 
 unsigned long jiffies ; 
 scalar_t__ sysctl_dccp_sync_ratelimit ; 
 scalar_t__ time_before (unsigned long,scalar_t__) ; 

__attribute__((used)) static int dccp_check_seqno(struct sock *sk, struct sk_buff *skb)
{
	const struct dccp_hdr *dh = dccp_hdr(skb);
	struct dccp_sock *dp = dccp_sk(sk);
	u64 lswl, lawl, seqno = DCCP_SKB_CB(skb)->dccpd_seq,
			ackno = DCCP_SKB_CB(skb)->dccpd_ack_seq;

	/*
	 *   Step 5: Prepare sequence numbers for Sync
	 *     If P.type == Sync or P.type == SyncAck,
	 *	  If S.AWL <= P.ackno <= S.AWH and P.seqno >= S.SWL,
	 *	     / * P is valid, so update sequence number variables
	 *		 accordingly.  After this update, P will pass the tests
	 *		 in Step 6.  A SyncAck is generated if necessary in
	 *		 Step 15 * /
	 *	     Update S.GSR, S.SWL, S.SWH
	 *	  Otherwise,
	 *	     Drop packet and return
	 */
	if (dh->dccph_type == DCCP_PKT_SYNC ||
	    dh->dccph_type == DCCP_PKT_SYNCACK) {
		if (between48(ackno, dp->dccps_awl, dp->dccps_awh) &&
		    dccp_delta_seqno(dp->dccps_swl, seqno) >= 0)
			dccp_update_gsr(sk, seqno);
		else
			return -1;
	}

	/*
	 *   Step 6: Check sequence numbers
	 *      Let LSWL = S.SWL and LAWL = S.AWL
	 *      If P.type == CloseReq or P.type == Close or P.type == Reset,
	 *	  LSWL := S.GSR + 1, LAWL := S.GAR
	 *      If LSWL <= P.seqno <= S.SWH
	 *	     and (P.ackno does not exist or LAWL <= P.ackno <= S.AWH),
	 *	  Update S.GSR, S.SWL, S.SWH
	 *	  If P.type != Sync,
	 *	     Update S.GAR
	 */
	lswl = dp->dccps_swl;
	lawl = dp->dccps_awl;

	if (dh->dccph_type == DCCP_PKT_CLOSEREQ ||
	    dh->dccph_type == DCCP_PKT_CLOSE ||
	    dh->dccph_type == DCCP_PKT_RESET) {
		lswl = ADD48(dp->dccps_gsr, 1);
		lawl = dp->dccps_gar;
	}

	if (between48(seqno, lswl, dp->dccps_swh) &&
	    (ackno == DCCP_PKT_WITHOUT_ACK_SEQ ||
	     between48(ackno, lawl, dp->dccps_awh))) {
		dccp_update_gsr(sk, seqno);

		if (dh->dccph_type != DCCP_PKT_SYNC &&
		    (ackno != DCCP_PKT_WITHOUT_ACK_SEQ))
			dp->dccps_gar = ackno;
	} else {
		unsigned long now = jiffies;
		/*
		 *   Step 6: Check sequence numbers
		 *      Otherwise,
		 *         If P.type == Reset,
		 *            Send Sync packet acknowledging S.GSR
		 *         Otherwise,
		 *            Send Sync packet acknowledging P.seqno
		 *      Drop packet and return
		 *
		 *   These Syncs are rate-limited as per RFC 4340, 7.5.4:
		 *   at most 1 / (dccp_sync_rate_limit * HZ) Syncs per second.
		 */
		if (time_before(now, (dp->dccps_rate_last +
				      sysctl_dccp_sync_ratelimit)))
			return 0;

		DCCP_WARN("DCCP: Step 6 failed for %s packet, "
			  "(LSWL(%llu) <= P.seqno(%llu) <= S.SWH(%llu)) and "
			  "(P.ackno %s or LAWL(%llu) <= P.ackno(%llu) <= S.AWH(%llu), "
			  "sending SYNC...\n",  dccp_packet_name(dh->dccph_type),
			  (unsigned long long) lswl, (unsigned long long) seqno,
			  (unsigned long long) dp->dccps_swh,
			  (ackno == DCCP_PKT_WITHOUT_ACK_SEQ) ? "doesn't exist"
							      : "exists",
			  (unsigned long long) lawl, (unsigned long long) ackno,
			  (unsigned long long) dp->dccps_awh);

		dp->dccps_rate_last = now;

		if (dh->dccph_type == DCCP_PKT_RESET)
			seqno = dp->dccps_gsr;
		dccp_send_sync(sk, seqno, DCCP_PKT_SYNC);
		return -1;
	}

	return 0;
}