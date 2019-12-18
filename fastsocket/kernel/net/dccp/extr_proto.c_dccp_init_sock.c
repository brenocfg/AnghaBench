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
struct sock {int /*<<< orphan*/  sk_write_space; int /*<<< orphan*/  sk_state; } ;
struct inet_connection_sock {int /*<<< orphan*/  icsk_sync_mss; int /*<<< orphan*/  icsk_syn_retries; int /*<<< orphan*/  icsk_rto; } ;
struct dccp_sock {int dccps_mss_cache; int dccps_l_ack_ratio; int dccps_r_ack_ratio; int /*<<< orphan*/  dccps_featneg; int /*<<< orphan*/  dccps_service; int /*<<< orphan*/  dccps_role; int /*<<< orphan*/  dccps_rate_last; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  DCCP_CLOSED ; 
 int /*<<< orphan*/  DCCP_ROLE_UNDEFINED ; 
 int /*<<< orphan*/  DCCP_SERVICE_CODE_IS_ABSENT ; 
 int /*<<< orphan*/  DCCP_TIMEOUT_INIT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int dccp_feat_init (struct sock*) ; 
 int /*<<< orphan*/  dccp_init_xmit_timers (struct sock*) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 
 int /*<<< orphan*/  dccp_sync_mss ; 
 int /*<<< orphan*/  dccp_write_space ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ likely (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  sysctl_dccp_request_retries ; 

int dccp_init_sock(struct sock *sk, const __u8 ctl_sock_initialized)
{
	struct dccp_sock *dp = dccp_sk(sk);
	struct inet_connection_sock *icsk = inet_csk(sk);

	icsk->icsk_rto		= DCCP_TIMEOUT_INIT;
	icsk->icsk_syn_retries	= sysctl_dccp_request_retries;
	sk->sk_state		= DCCP_CLOSED;
	sk->sk_write_space	= dccp_write_space;
	icsk->icsk_sync_mss	= dccp_sync_mss;
	dp->dccps_mss_cache	= 536;
	dp->dccps_rate_last	= jiffies;
	dp->dccps_role		= DCCP_ROLE_UNDEFINED;
	dp->dccps_service	= DCCP_SERVICE_CODE_IS_ABSENT;
	dp->dccps_l_ack_ratio	= dp->dccps_r_ack_ratio = 1;

	dccp_init_xmit_timers(sk);

	INIT_LIST_HEAD(&dp->dccps_featneg);
	/* control socket doesn't need feat nego */
	if (likely(ctl_sock_initialized))
		return dccp_feat_init(sk);
	return 0;
}