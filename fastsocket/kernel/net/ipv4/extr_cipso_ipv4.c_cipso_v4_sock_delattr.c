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
struct sock {int dummy; } ;
struct ip_options {scalar_t__ cipso; } ;
struct inet_sock {scalar_t__ is_icsk; int /*<<< orphan*/  opt; } ;
struct inet_connection_sock {int icsk_ext_hdr_len; int /*<<< orphan*/  icsk_pmtu_cookie; int /*<<< orphan*/  (* icsk_sync_mss ) (struct sock*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int cipso_v4_delopt (int /*<<< orphan*/ *) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 struct ip_options* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*,int /*<<< orphan*/ ) ; 

void cipso_v4_sock_delattr(struct sock *sk)
{
	int hdr_delta;
	struct ip_options *opt;
	struct inet_sock *sk_inet;

	sk_inet = inet_sk(sk);
	opt = rcu_dereference(sk_inet->opt);
	if (opt == NULL || opt->cipso == 0)
		return;

	hdr_delta = cipso_v4_delopt(&sk_inet->opt);
	if (sk_inet->is_icsk && hdr_delta > 0) {
		struct inet_connection_sock *sk_conn = inet_csk(sk);
		sk_conn->icsk_ext_hdr_len -= hdr_delta;
		sk_conn->icsk_sync_mss(sk, sk_conn->icsk_pmtu_cookie);
	}
}