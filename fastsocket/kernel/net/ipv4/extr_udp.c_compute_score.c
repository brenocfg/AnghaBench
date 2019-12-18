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
struct inet_sock {scalar_t__ rcv_saddr; scalar_t__ daddr; scalar_t__ dport; } ;
typedef  scalar_t__ __be32 ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 scalar_t__ PF_INET ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  ipv6_only_sock (struct sock*) ; 
 scalar_t__ net_eq (int /*<<< orphan*/ ,struct net*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 

__attribute__((used)) static inline int compute_score(struct sock *sk, struct net *net, __be32 saddr,
			 unsigned short hnum,
			 __be16 sport, __be32 daddr, __be16 dport, int dif)
{
	int score = -1;

	if (net_eq(sock_net(sk), net) && sk->sk_hash == hnum &&
			!ipv6_only_sock(sk)) {
		struct inet_sock *inet = inet_sk(sk);

		score = (sk->sk_family == PF_INET ? 2 : 1);
		if (inet->rcv_saddr) {
			if (inet->rcv_saddr != daddr)
				return -1;
			score += 4;
		}
		if (inet->daddr) {
			if (inet->daddr != saddr)
				return -1;
			score += 4;
		}
		if (inet->dport) {
			if (inet->dport != sport)
				return -1;
			score += 4;
		}
		if (sk->sk_bound_dev_if) {
			if (sk->sk_bound_dev_if != dif)
				return -1;
			score += 4;
		}
	}
	return score;
}