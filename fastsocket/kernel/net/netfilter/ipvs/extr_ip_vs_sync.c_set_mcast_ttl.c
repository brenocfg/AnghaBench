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
typedef  int /*<<< orphan*/  u_char ;
struct sock {int dummy; } ;
struct inet_sock {int /*<<< orphan*/  mc_ttl; } ;

/* Variables and functions */
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 

__attribute__((used)) static void set_mcast_ttl(struct sock *sk, u_char ttl)
{
	struct inet_sock *inet = inet_sk(sk);

	/* setsockopt(sock, SOL_IP, IP_MULTICAST_TTL, &ttl, sizeof(ttl)); */
	lock_sock(sk);
	inet->mc_ttl = ttl;
	release_sock(sk);
}