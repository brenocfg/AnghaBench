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
struct tcp_sock {scalar_t__ tcp_header_len; } ;
struct sock {int dummy; } ;
struct TYPE_2__ {int enabled; int /*<<< orphan*/  search_low; } ;
struct inet_connection_sock {int /*<<< orphan*/  icsk_pmtu_cookie; TYPE_1__ icsk_mtup; } ;

/* Variables and functions */
 int max (int,scalar_t__) ; 
 int min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sysctl_tcp_base_mss ; 
 scalar_t__ sysctl_tcp_mtu_probing ; 
 int /*<<< orphan*/  tcp_mss_to_mtu (struct sock*,int) ; 
 int tcp_mtu_to_mss (struct sock*,int /*<<< orphan*/ ) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_sync_mss (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tcp_mtu_probing(struct inet_connection_sock *icsk, struct sock *sk)
{
	/* Black hole detection */
	if (sysctl_tcp_mtu_probing) {
		if (!icsk->icsk_mtup.enabled) {
			icsk->icsk_mtup.enabled = 1;
			tcp_sync_mss(sk, icsk->icsk_pmtu_cookie);
		} else {
			struct tcp_sock *tp = tcp_sk(sk);
			int mss;

			mss = tcp_mtu_to_mss(sk, icsk->icsk_mtup.search_low) >> 1;
			mss = min(sysctl_tcp_base_mss, mss);
			mss = max(mss, 68 - tp->tcp_header_len);
			icsk->icsk_mtup.search_low = tcp_mss_to_mtu(sk, mss);
			tcp_sync_mss(sk, icsk->icsk_pmtu_cookie);
		}
	}
}