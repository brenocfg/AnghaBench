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
struct tcp_sock {scalar_t__ packets_out; scalar_t__ snd_cwnd; } ;
struct sock {int sk_userlocks; } ;

/* Variables and functions */
 int SOCK_SNDBUF_LOCK ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__* sysctl_tcp_mem ; 
 int /*<<< orphan*/  tcp_memory_allocated ; 
 scalar_t__ tcp_memory_pressure ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static int tcp_should_expand_sndbuf(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);

	/* If the user specified a specific send buffer setting, do
	 * not modify it.
	 */
	if (sk->sk_userlocks & SOCK_SNDBUF_LOCK)
		return 0;

	/* If we are under global TCP memory pressure, do not expand.  */
	if (tcp_memory_pressure)
		return 0;

	/* If we are under soft global TCP memory pressure, do not expand.  */
	if (atomic_read(&tcp_memory_allocated) >= sysctl_tcp_mem[0])
		return 0;

	/* If we filled the congestion window, do not expand.  */
	if (tp->packets_out >= tp->snd_cwnd)
		return 0;

	return 1;
}