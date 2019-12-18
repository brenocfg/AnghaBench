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
typedef  int u32 ;
struct tcp_sock {int snd_cwnd; int mss_cache; } ;
struct sock {int sk_gso_max_size; } ;
struct TYPE_2__ {int sk_gso_max_segs; } ;

/* Variables and functions */
 scalar_t__ sk_can_gso (struct sock const*) ; 
 TYPE_1__* sk_extended (struct sock const*) ; 
 int sysctl_tcp_tso_win_divisor ; 
 int tcp_max_burst (struct tcp_sock const*) ; 
 struct tcp_sock* tcp_sk (struct sock const*) ; 

int tcp_is_cwnd_limited(const struct sock *sk, u32 in_flight)
{
	const struct tcp_sock *tp = tcp_sk(sk);
	u32 left;

	if (in_flight >= tp->snd_cwnd)
		return 1;

	left = tp->snd_cwnd - in_flight;
	if (sk_can_gso(sk) &&
	    left * sysctl_tcp_tso_win_divisor < tp->snd_cwnd &&
	    left * tp->mss_cache < sk->sk_gso_max_size &&
	    left < sk_extended(sk)->sk_gso_max_segs)
		return 1;
	return left <= tcp_max_burst(tp);
}