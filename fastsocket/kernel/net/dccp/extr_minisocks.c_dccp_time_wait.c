#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sock {int /*<<< orphan*/  sk_prot; } ;
struct ipv6_pinfo {int /*<<< orphan*/  ipv6only; int /*<<< orphan*/  rcv_saddr; int /*<<< orphan*/  daddr; } ;
struct inet_timewait_sock {scalar_t__ tw_family; void* tw_timeout; int /*<<< orphan*/  tw_ipv6only; int /*<<< orphan*/  tw_ipv6_offset; } ;
struct inet_connection_sock {int icsk_rto; } ;
struct inet6_timewait_sock {int /*<<< orphan*/  tw_v6_rcv_saddr; int /*<<< orphan*/  tw_v6_daddr; } ;
struct TYPE_3__ {scalar_t__ tw_count; scalar_t__ sysctl_max_tw_buckets; } ;

/* Variables and functions */
 void* DCCP_TIMEWAIT_LEN ; 
 int DCCP_TIME_WAIT ; 
 int /*<<< orphan*/  DCCP_WARN (char*) ; 
 scalar_t__ PF_INET6 ; 
 int /*<<< orphan*/  __inet_twsk_hashdance (struct inet_timewait_sock*,struct sock*,int /*<<< orphan*/ *) ; 
 TYPE_1__ dccp_death_row ; 
 int /*<<< orphan*/  dccp_done (struct sock*) ; 
 int /*<<< orphan*/  dccp_hashinfo ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 int /*<<< orphan*/  inet6_tw_offset (int /*<<< orphan*/ ) ; 
 struct inet6_timewait_sock* inet6_twsk (struct sock*) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 struct inet_timewait_sock* inet_twsk_alloc (struct sock*,int) ; 
 int /*<<< orphan*/  inet_twsk_put (struct inet_timewait_sock*) ; 
 int /*<<< orphan*/  inet_twsk_schedule (struct inet_timewait_sock*,TYPE_1__*,int,void*) ; 
 int /*<<< orphan*/  ipv6_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void dccp_time_wait(struct sock *sk, int state, int timeo)
{
	struct inet_timewait_sock *tw = NULL;

	if (dccp_death_row.tw_count < dccp_death_row.sysctl_max_tw_buckets)
		tw = inet_twsk_alloc(sk, state);

	if (tw != NULL) {
		const struct inet_connection_sock *icsk = inet_csk(sk);
		const int rto = (icsk->icsk_rto << 2) - (icsk->icsk_rto >> 1);
#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
		if (tw->tw_family == PF_INET6) {
			const struct ipv6_pinfo *np = inet6_sk(sk);
			struct inet6_timewait_sock *tw6;

			tw->tw_ipv6_offset = inet6_tw_offset(sk->sk_prot);
			tw6 = inet6_twsk((struct sock *)tw);
			ipv6_addr_copy(&tw6->tw_v6_daddr, &np->daddr);
			ipv6_addr_copy(&tw6->tw_v6_rcv_saddr, &np->rcv_saddr);
			tw->tw_ipv6only = np->ipv6only;
		}
#endif
		/* Linkage updates. */
		__inet_twsk_hashdance(tw, sk, &dccp_hashinfo);

		/* Get the TIME_WAIT timeout firing. */
		if (timeo < rto)
			timeo = rto;

		tw->tw_timeout = DCCP_TIMEWAIT_LEN;
		if (state == DCCP_TIME_WAIT)
			timeo = DCCP_TIMEWAIT_LEN;

		inet_twsk_schedule(tw, &dccp_death_row, timeo,
				   DCCP_TIMEWAIT_LEN);
		inet_twsk_put(tw);
	} else {
		/* Sorry, if we're out of memory, just CLOSE this
		 * socket up.  We've got bigger problems than
		 * non-graceful socket closings.
		 */
		DCCP_WARN("time wait bucket table overflow\n");
	}

	dccp_done(sk);
}