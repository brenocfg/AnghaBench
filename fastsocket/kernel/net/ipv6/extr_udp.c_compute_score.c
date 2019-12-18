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
struct sock {unsigned short sk_hash; scalar_t__ sk_family; int sk_bound_dev_if; } ;
struct net {int dummy; } ;
struct ipv6_pinfo {int /*<<< orphan*/  daddr; int /*<<< orphan*/  rcv_saddr; } ;
struct inet_sock {scalar_t__ dport; } ;
struct in6_addr {int dummy; } ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 scalar_t__ PF_INET6 ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  ipv6_addr_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipv6_addr_equal (int /*<<< orphan*/ *,struct in6_addr const*) ; 
 scalar_t__ net_eq (int /*<<< orphan*/ ,struct net*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 

__attribute__((used)) static inline int compute_score(struct sock *sk, struct net *net,
				unsigned short hnum,
				const struct in6_addr *saddr, __be16 sport,
				const struct in6_addr *daddr, __be16 dport,
				int dif)
{
	int score = -1;

	if (net_eq(sock_net(sk), net) && sk->sk_hash == hnum &&
			sk->sk_family == PF_INET6) {
		struct ipv6_pinfo *np = inet6_sk(sk);
		struct inet_sock *inet = inet_sk(sk);

		score = 0;
		if (inet->dport) {
			if (inet->dport != sport)
				return -1;
			score++;
		}
		if (!ipv6_addr_any(&np->rcv_saddr)) {
			if (!ipv6_addr_equal(&np->rcv_saddr, daddr))
				return -1;
			score++;
		}
		if (!ipv6_addr_any(&np->daddr)) {
			if (!ipv6_addr_equal(&np->daddr, saddr))
				return -1;
			score++;
		}
		if (sk->sk_bound_dev_if) {
			if (sk->sk_bound_dev_if != dif)
				return -1;
			score++;
		}
	}
	return score;
}