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
struct tcp_sock {int /*<<< orphan*/  tsq_flags; } ;
struct sock {int sk_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int TCPF_CLOSE_WAIT ; 
 int TCPF_CLOSING ; 
 int TCPF_ESTABLISHED ; 
 int TCPF_FIN_WAIT1 ; 
 int TCPF_LAST_ACK ; 
 int /*<<< orphan*/  TSQ_OWNED ; 
 int /*<<< orphan*/  tcp_current_mss (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_write_xmit (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void tcp_release_cb(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);

	if (test_and_clear_bit(TSQ_OWNED, &tp->tsq_flags)) {
		if ((1 << sk->sk_state) &
		    (TCPF_ESTABLISHED | TCPF_FIN_WAIT1 |
		     TCPF_CLOSING | TCPF_CLOSE_WAIT | TCPF_LAST_ACK))
			tcp_write_xmit(sk,
				       tcp_current_mss(sk),
				       0, 0,
				       GFP_ATOMIC);
	}
}