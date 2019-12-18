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
struct tcp_sock {int mss_cache; } ;
struct sock {int sk_route_caps; } ;

/* Variables and functions */
 int MAX_SKB_FRAGS ; 
 int /*<<< orphan*/  MAX_TCP_HEADER ; 
 int NETIF_F_SG ; 
 int PAGE_SIZE ; 
 int SKB_MAX_HEAD (int /*<<< orphan*/ ) ; 
 scalar_t__ sk_can_gso (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static inline int select_size(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);
	int tmp = tp->mss_cache;

	if (sk->sk_route_caps & NETIF_F_SG) {
		if (sk_can_gso(sk))
			tmp = 0;
		else {
			int pgbreak = SKB_MAX_HEAD(MAX_TCP_HEADER);

			if (tmp >= pgbreak &&
			    tmp <= pgbreak + (MAX_SKB_FRAGS - 1) * PAGE_SIZE)
				tmp = pgbreak;
		}
	}

	return tmp;
}