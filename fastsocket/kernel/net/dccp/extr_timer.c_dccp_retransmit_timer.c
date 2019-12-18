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
struct sock {int dummy; } ;
struct inet_connection_sock {scalar_t__ icsk_retransmits; int icsk_rto; int /*<<< orphan*/  icsk_backoff; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCCP_INC_STATS_BH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DCCP_MIB_TIMEOUTS ; 
 int /*<<< orphan*/  DCCP_RTO_MAX ; 
 int /*<<< orphan*/  ICSK_TIME_RETRANS ; 
 int /*<<< orphan*/  TCP_RESOURCE_PROBE_INTERVAL ; 
 int /*<<< orphan*/  __sk_dst_reset (struct sock*) ; 
 scalar_t__ dccp_retransmit_skb (struct sock*) ; 
 scalar_t__ dccp_write_timeout (struct sock*) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  inet_csk_reset_xmit_timer (struct sock*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int sysctl_dccp_retries1 ; 

__attribute__((used)) static void dccp_retransmit_timer(struct sock *sk)
{
	struct inet_connection_sock *icsk = inet_csk(sk);

	/*
	 * More than than 4MSL (8 minutes) has passed, a RESET(aborted) was
	 * sent, no need to retransmit, this sock is dead.
	 */
	if (dccp_write_timeout(sk))
		return;

	/*
	 * We want to know the number of packets retransmitted, not the
	 * total number of retransmissions of clones of original packets.
	 */
	if (icsk->icsk_retransmits == 0)
		DCCP_INC_STATS_BH(DCCP_MIB_TIMEOUTS);

	if (dccp_retransmit_skb(sk) != 0) {
		/*
		 * Retransmission failed because of local congestion,
		 * do not backoff.
		 */
		if (--icsk->icsk_retransmits == 0)
			icsk->icsk_retransmits = 1;
		inet_csk_reset_xmit_timer(sk, ICSK_TIME_RETRANS,
					  min(icsk->icsk_rto,
					      TCP_RESOURCE_PROBE_INTERVAL),
					  DCCP_RTO_MAX);
		return;
	}

	icsk->icsk_backoff++;

	icsk->icsk_rto = min(icsk->icsk_rto << 1, DCCP_RTO_MAX);
	inet_csk_reset_xmit_timer(sk, ICSK_TIME_RETRANS, icsk->icsk_rto,
				  DCCP_RTO_MAX);
	if (icsk->icsk_retransmits > sysctl_dccp_retries1)
		__sk_dst_reset(sk);
}