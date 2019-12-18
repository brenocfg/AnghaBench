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
struct sock {scalar_t__ sk_err; } ;
struct inet_connection_sock {scalar_t__ icsk_retransmits; } ;
struct dst_entry {int dummy; } ;
struct dccp_sock {int /*<<< orphan*/  dccps_iss; int /*<<< orphan*/  dccps_gar; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_DONE ; 
 struct dst_entry* __sk_dst_get (struct sock*) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 
 int /*<<< orphan*/  dccp_sync_mss (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_mtu (struct dst_entry*) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  sock_reset_flag (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void dccp_connect_init(struct sock *sk)
{
	struct dccp_sock *dp = dccp_sk(sk);
	struct dst_entry *dst = __sk_dst_get(sk);
	struct inet_connection_sock *icsk = inet_csk(sk);

	sk->sk_err = 0;
	sock_reset_flag(sk, SOCK_DONE);

	dccp_sync_mss(sk, dst_mtu(dst));

	/* Initialise GAR as per 8.5; AWL/AWH are set in dccp_transmit_skb() */
	dp->dccps_gar = dp->dccps_iss;

	icsk->icsk_retransmits = 0;
}