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
struct tcp_sock {scalar_t__ retrans_out; scalar_t__ retrans_stamp; int /*<<< orphan*/  frto_counter; } ;
struct sock {int dummy; } ;
struct TYPE_2__ {scalar_t__ icsk_ca_state; } ;

/* Variables and functions */
 int FLAG_ECE ; 
 scalar_t__ TCP_CA_CWR ; 
 scalar_t__ TCP_CA_Open ; 
 TYPE_1__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  tcp_cwnd_down (struct sock*,int) ; 
 int /*<<< orphan*/  tcp_enter_cwr (struct sock*,int) ; 
 int /*<<< orphan*/  tcp_moderate_cwnd (struct tcp_sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_try_keep_open (struct sock*) ; 
 int /*<<< orphan*/  tcp_verify_left_out (struct tcp_sock*) ; 

__attribute__((used)) static void tcp_try_to_open(struct sock *sk, int flag)
{
	struct tcp_sock *tp = tcp_sk(sk);

	tcp_verify_left_out(tp);

	if (!tp->frto_counter && tp->retrans_out == 0)
		tp->retrans_stamp = 0;

	if (flag & FLAG_ECE)
		tcp_enter_cwr(sk, 1);

	if (inet_csk(sk)->icsk_ca_state != TCP_CA_CWR) {
		tcp_try_keep_open(sk);
		if (inet_csk(sk)->icsk_ca_state != TCP_CA_Open)
			tcp_moderate_cwnd(tp);
	} else {
		tcp_cwnd_down(sk, flag);
	}
}