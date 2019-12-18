#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  sk_err_soft; } ;
struct iphdr {int dummy; } ;
struct inet_sock {scalar_t__ pmtudisc; } ;
struct dst_entry {TYPE_1__* ops; } ;
struct dccp_sock {int /*<<< orphan*/  dccps_gsr; } ;
struct TYPE_4__ {scalar_t__ icsk_pmtu_cookie; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* update_pmtu ) (struct dst_entry*,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ DCCP_LISTEN ; 
 int /*<<< orphan*/  DCCP_PKT_SYNC ; 
 int /*<<< orphan*/  EMSGSIZE ; 
 scalar_t__ IP_PMTUDISC_DONT ; 
 struct dst_entry* __sk_dst_check (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dccp_send_sync (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 
 int /*<<< orphan*/  dccp_sync_mss (struct sock*,scalar_t__) ; 
 scalar_t__ dst_mtu (struct dst_entry*) ; 
 TYPE_2__* inet_csk (struct sock*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 scalar_t__ ip_dont_fragment (struct sock*,struct dst_entry*) ; 
 int /*<<< orphan*/  stub1 (struct dst_entry*,scalar_t__) ; 

__attribute__((used)) static inline void dccp_do_pmtu_discovery(struct sock *sk,
					  const struct iphdr *iph,
					  u32 mtu)
{
	struct dst_entry *dst;
	const struct inet_sock *inet = inet_sk(sk);
	const struct dccp_sock *dp = dccp_sk(sk);

	/* We are not interested in DCCP_LISTEN and request_socks (RESPONSEs
	 * send out by Linux are always < 576bytes so they should go through
	 * unfragmented).
	 */
	if (sk->sk_state == DCCP_LISTEN)
		return;

	/* We don't check in the destentry if pmtu discovery is forbidden
	 * on this route. We just assume that no packet_to_big packets
	 * are send back when pmtu discovery is not active.
	 * There is a small race when the user changes this flag in the
	 * route, but I think that's acceptable.
	 */
	if ((dst = __sk_dst_check(sk, 0)) == NULL)
		return;

	dst->ops->update_pmtu(dst, mtu);

	/* Something is about to be wrong... Remember soft error
	 * for the case, if this connection will not able to recover.
	 */
	if (mtu < dst_mtu(dst) && ip_dont_fragment(sk, dst))
		sk->sk_err_soft = EMSGSIZE;

	mtu = dst_mtu(dst);

	if (inet->pmtudisc != IP_PMTUDISC_DONT &&
	    inet_csk(sk)->icsk_pmtu_cookie > mtu) {
		dccp_sync_mss(sk, mtu);

		/*
		 * From RFC 4340, sec. 14.1:
		 *
		 *	DCCP-Sync packets are the best choice for upward
		 *	probing, since DCCP-Sync probes do not risk application
		 *	data loss.
		 */
		dccp_send_sync(sk, dp->dccps_gsr, DCCP_PKT_SYNC);
	} /* else let the usual retransmit timer handle it */
}