#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ ts_recent_stamp; int mss_clamp; scalar_t__ ts_recent; } ;
struct tcp_sock {int write_seq; TYPE_2__ rx_opt; } ;
struct TYPE_7__ {scalar_t__ s_addr; } ;
struct sockaddr_in {scalar_t__ sin_family; scalar_t__ sin_port; TYPE_1__ sin_addr; } ;
struct sockaddr {int dummy; } ;
struct sock {scalar_t__ sk_route_caps; int /*<<< orphan*/  sk_gso_type; int /*<<< orphan*/  sk_bound_dev_if; } ;
struct TYPE_9__ {int /*<<< orphan*/  dst; } ;
struct rtable {int rt_flags; scalar_t__ rt_dst; TYPE_3__ u; scalar_t__ rt_src; } ;
struct ip_options {scalar_t__ faddr; scalar_t__ optlen; scalar_t__ srr; } ;
struct inet_sock {scalar_t__ daddr; int id; scalar_t__ dport; int /*<<< orphan*/  sport; scalar_t__ saddr; scalar_t__ rcv_saddr; int /*<<< orphan*/  opt; } ;
struct inet_peer {scalar_t__ tcp_ts_stamp; scalar_t__ tcp_ts; } ;
typedef  scalar_t__ __be32 ;
struct TYPE_11__ {scalar_t__ icsk_ext_hdr_len; } ;
struct TYPE_10__ {scalar_t__ sysctl_tw_recycle; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int ENETUNREACH ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  IPSTATS_MIB_OUTNOROUTES ; 
 int /*<<< orphan*/  IP_INC_STATS_BH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RTCF_BROADCAST ; 
 int RTCF_MULTICAST ; 
 int /*<<< orphan*/  RT_CONN_FLAGS (struct sock*) ; 
 int /*<<< orphan*/  SKB_GSO_TCPV4 ; 
 int /*<<< orphan*/  TCP_CLOSE ; 
 scalar_t__ TCP_PAWS_MSL ; 
 int /*<<< orphan*/  TCP_SYN_SENT ; 
 scalar_t__ get_seconds () ; 
 TYPE_6__* inet_csk (struct sock*) ; 
 int inet_hash_connect (TYPE_4__*,struct sock*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int ip_route_connect (struct rtable**,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct sock*,int) ; 
 int ip_route_newports (struct rtable**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct sock*) ; 
 int /*<<< orphan*/  ip_rt_put (struct rtable*) ; 
 int jiffies ; 
 struct ip_options* rcu_dereference (int /*<<< orphan*/ ) ; 
 struct inet_peer* rt_get_peer (struct rtable*) ; 
 int secure_tcp_sequence_number (scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sk_setup_caps (struct sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int tcp_connect (struct sock*) ; 
 TYPE_4__ tcp_death_row ; 
 int /*<<< orphan*/  tcp_set_state (struct sock*,int /*<<< orphan*/ ) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

int tcp_v4_connect(struct sock *sk, struct sockaddr *uaddr, int addr_len)
{
	struct inet_sock *inet = inet_sk(sk);
	struct tcp_sock *tp = tcp_sk(sk);
	struct sockaddr_in *usin = (struct sockaddr_in *)uaddr;
	struct rtable *rt;
	__be32 daddr, nexthop;
	int tmp;
	int err;
	struct ip_options *inet_opt;

	if (addr_len < sizeof(struct sockaddr_in))
		return -EINVAL;

	if (usin->sin_family != AF_INET)
		return -EAFNOSUPPORT;

	nexthop = daddr = usin->sin_addr.s_addr;
	inet_opt = rcu_dereference(inet->opt);
	if (inet_opt && inet_opt->srr) {
		if (!daddr)
			return -EINVAL;
		nexthop = inet_opt->faddr;
	}

	tmp = ip_route_connect(&rt, nexthop, inet->saddr,
			       RT_CONN_FLAGS(sk), sk->sk_bound_dev_if,
			       IPPROTO_TCP,
			       inet->sport, usin->sin_port, sk, 1);
	if (tmp < 0) {
		if (tmp == -ENETUNREACH)
			IP_INC_STATS_BH(sock_net(sk), IPSTATS_MIB_OUTNOROUTES);
		return tmp;
	}

	if (rt->rt_flags & (RTCF_MULTICAST | RTCF_BROADCAST)) {
		ip_rt_put(rt);
		return -ENETUNREACH;
	}

	if (!inet_opt || !inet_opt->srr)
		daddr = rt->rt_dst;

	if (!inet->saddr)
		inet->saddr = rt->rt_src;
	inet->rcv_saddr = inet->saddr;

	if (tp->rx_opt.ts_recent_stamp && inet->daddr != daddr) {
		/* Reset inherited state */
		tp->rx_opt.ts_recent	   = 0;
		tp->rx_opt.ts_recent_stamp = 0;
		tp->write_seq		   = 0;
	}

	if (tcp_death_row.sysctl_tw_recycle &&
	    !tp->rx_opt.ts_recent_stamp && rt->rt_dst == daddr) {
		struct inet_peer *peer = rt_get_peer(rt);
		/*
		 * VJ's idea. We save last timestamp seen from
		 * the destination in peer table, when entering state
		 * TIME-WAIT * and initialize rx_opt.ts_recent from it,
		 * when trying new connection.
		 */
		if (peer != NULL &&
		    peer->tcp_ts_stamp + TCP_PAWS_MSL >= get_seconds()) {
			tp->rx_opt.ts_recent_stamp = peer->tcp_ts_stamp;
			tp->rx_opt.ts_recent = peer->tcp_ts;
		}
	}

	inet->dport = usin->sin_port;
	inet->daddr = daddr;

	inet_csk(sk)->icsk_ext_hdr_len = 0;
	if (inet_opt)
		inet_csk(sk)->icsk_ext_hdr_len = inet_opt->optlen;

	tp->rx_opt.mss_clamp = 536;

	/* Socket identity is still unknown (sport may be zero).
	 * However we set state to SYN-SENT and not releasing socket
	 * lock select source port, enter ourselves into the hash tables and
	 * complete initialization after this.
	 */
	tcp_set_state(sk, TCP_SYN_SENT);
	err = inet_hash_connect(&tcp_death_row, sk);
	if (err)
		goto failure;

	err = ip_route_newports(&rt, IPPROTO_TCP,
				inet->sport, inet->dport, sk);
	if (err)
		goto failure;

	/* OK, now commit destination to socket.  */
	sk->sk_gso_type = SKB_GSO_TCPV4;
	sk_setup_caps(sk, &rt->u.dst);

	if (!tp->write_seq)
		tp->write_seq = secure_tcp_sequence_number(inet->saddr,
							   inet->daddr,
							   inet->sport,
							   usin->sin_port);

	inet->id = tp->write_seq ^ jiffies;

	err = tcp_connect(sk);
	rt = NULL;
	if (err)
		goto failure;

	return 0;

failure:
	/*
	 * This unhashes the socket and releases the local port,
	 * if necessary.
	 */
	tcp_set_state(sk, TCP_CLOSE);
	ip_rt_put(rt);
	sk->sk_route_caps = 0;
	inet->dport = 0;
	return err;
}