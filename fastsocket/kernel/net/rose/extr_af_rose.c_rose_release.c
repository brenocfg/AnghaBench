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
struct socket {struct sock* sk; } ;
struct sock {int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;int /*<<< orphan*/  sk_shutdown; int /*<<< orphan*/  sk_state; } ;
struct rose_sock {int state; TYPE_1__* neighbour; } ;
struct TYPE_2__ {int /*<<< orphan*/  use; } ;

/* Variables and functions */
 int /*<<< orphan*/  ROSE_CLEAR_REQUEST ; 
#define  ROSE_STATE_0 133 
#define  ROSE_STATE_1 132 
#define  ROSE_STATE_2 131 
#define  ROSE_STATE_3 130 
#define  ROSE_STATE_4 129 
#define  ROSE_STATE_5 128 
 int /*<<< orphan*/  SEND_SHUTDOWN ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  SOCK_DESTROY ; 
 int /*<<< orphan*/  TCP_CLOSE ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  rose_clear_queues (struct sock*) ; 
 int /*<<< orphan*/  rose_destroy_socket (struct sock*) ; 
 int /*<<< orphan*/  rose_disconnect (struct sock*,int /*<<< orphan*/ ,int,int) ; 
 struct rose_sock* rose_sk (struct sock*) ; 
 int /*<<< orphan*/  rose_start_t3timer (struct sock*) ; 
 int /*<<< orphan*/  rose_stop_idletimer (struct sock*) ; 
 int /*<<< orphan*/  rose_write_internal (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  sock_orphan (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static int rose_release(struct socket *sock)
{
	struct sock *sk = sock->sk;
	struct rose_sock *rose;

	if (sk == NULL) return 0;

	sock_hold(sk);
	sock_orphan(sk);
	lock_sock(sk);
	rose = rose_sk(sk);

	switch (rose->state) {
	case ROSE_STATE_0:
		release_sock(sk);
		rose_disconnect(sk, 0, -1, -1);
		lock_sock(sk);
		rose_destroy_socket(sk);
		break;

	case ROSE_STATE_2:
		rose->neighbour->use--;
		release_sock(sk);
		rose_disconnect(sk, 0, -1, -1);
		lock_sock(sk);
		rose_destroy_socket(sk);
		break;

	case ROSE_STATE_1:
	case ROSE_STATE_3:
	case ROSE_STATE_4:
	case ROSE_STATE_5:
		rose_clear_queues(sk);
		rose_stop_idletimer(sk);
		rose_write_internal(sk, ROSE_CLEAR_REQUEST);
		rose_start_t3timer(sk);
		rose->state  = ROSE_STATE_2;
		sk->sk_state    = TCP_CLOSE;
		sk->sk_shutdown |= SEND_SHUTDOWN;
		sk->sk_state_change(sk);
		sock_set_flag(sk, SOCK_DEAD);
		sock_set_flag(sk, SOCK_DESTROY);
		break;

	default:
		break;
	}

	sock->sk = NULL;
	release_sock(sk);
	sock_put(sk);

	return 0;
}