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
struct TYPE_2__ {scalar_t__ ts_recent_stamp; scalar_t__ ts_recent; } ;
struct tcp_sock {TYPE_1__ rx_opt; } ;
struct sock {int dummy; } ;
struct rtable {scalar_t__ rt_dst; struct inet_peer* peer; } ;
struct inet_sock {scalar_t__ daddr; } ;
struct inet_peer {scalar_t__ tcp_ts_stamp; scalar_t__ tcp_ts; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ TCP_PAWS_MSL ; 
 scalar_t__ __sk_dst_get (struct sock*) ; 
 scalar_t__ get_seconds () ; 
 struct inet_peer* inet_getpeer (scalar_t__,int) ; 
 int /*<<< orphan*/  inet_putpeer (struct inet_peer*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  rt_bind_peer (struct rtable*,int) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

int tcp_v4_remember_stamp(struct sock *sk)
{
	struct inet_sock *inet = inet_sk(sk);
	struct tcp_sock *tp = tcp_sk(sk);
	struct rtable *rt = (struct rtable *)__sk_dst_get(sk);
	struct inet_peer *peer = NULL;
	int release_it = 0;

	if (!rt || rt->rt_dst != inet->daddr) {
		peer = inet_getpeer(inet->daddr, 1);
		release_it = 1;
	} else {
		if (!rt->peer)
			rt_bind_peer(rt, 1);
		peer = rt->peer;
	}

	if (peer) {
		if ((s32)(peer->tcp_ts - tp->rx_opt.ts_recent) <= 0 ||
		    (peer->tcp_ts_stamp + TCP_PAWS_MSL < get_seconds() &&
		     peer->tcp_ts_stamp <= tp->rx_opt.ts_recent_stamp)) {
			peer->tcp_ts_stamp = tp->rx_opt.ts_recent_stamp;
			peer->tcp_ts = tp->rx_opt.ts_recent;
		}
		if (release_it)
			inet_putpeer(peer);
		return 1;
	}

	return 0;
}