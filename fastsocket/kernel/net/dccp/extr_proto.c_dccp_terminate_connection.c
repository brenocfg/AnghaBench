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
typedef  int /*<<< orphan*/  u8 ;
struct sock {int sk_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  dccps_server_timewait; int /*<<< orphan*/  dccps_role; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCCP_ACTIVE_CLOSEREQ ; 
 int /*<<< orphan*/  DCCP_CLOSED ; 
 int /*<<< orphan*/  DCCP_CLOSING ; 
#define  DCCP_OPEN 131 
#define  DCCP_PARTOPEN 130 
#define  DCCP_PASSIVE_CLOSE 129 
#define  DCCP_PASSIVE_CLOSEREQ 128 
 int /*<<< orphan*/  DCCP_ROLE_SERVER ; 
 int /*<<< orphan*/  ICSK_TIME_DACK ; 
 int /*<<< orphan*/  dccp_finish_passive_close (struct sock*) ; 
 int /*<<< orphan*/  dccp_pr_debug (char*,struct sock*) ; 
 int /*<<< orphan*/  dccp_send_close (struct sock*,int) ; 
 int /*<<< orphan*/  dccp_set_state (struct sock*,int /*<<< orphan*/ ) ; 
 TYPE_1__* dccp_sk (struct sock*) ; 
 int /*<<< orphan*/  inet_csk_clear_xmit_timer (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dccp_terminate_connection(struct sock *sk)
{
	u8 next_state = DCCP_CLOSED;

	switch (sk->sk_state) {
	case DCCP_PASSIVE_CLOSE:
	case DCCP_PASSIVE_CLOSEREQ:
		dccp_finish_passive_close(sk);
		break;
	case DCCP_PARTOPEN:
		dccp_pr_debug("Stop PARTOPEN timer (%p)\n", sk);
		inet_csk_clear_xmit_timer(sk, ICSK_TIME_DACK);
		/* fall through */
	case DCCP_OPEN:
		dccp_send_close(sk, 1);

		if (dccp_sk(sk)->dccps_role == DCCP_ROLE_SERVER &&
		    !dccp_sk(sk)->dccps_server_timewait)
			next_state = DCCP_ACTIVE_CLOSEREQ;
		else
			next_state = DCCP_CLOSING;
		/* fall through */
	default:
		dccp_set_state(sk, next_state);
	}
}