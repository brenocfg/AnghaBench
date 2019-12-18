#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct socket {struct sock* sk; } ;
struct sock {scalar_t__ sk_type; int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;int /*<<< orphan*/  sk_shutdown; void* sk_state; } ;
struct TYPE_14__ {int state; TYPE_1__* ax25_dev; int /*<<< orphan*/  n2count; } ;
typedef  TYPE_2__ ax25_cb ;
struct TYPE_13__ {int /*<<< orphan*/ * values; } ;

/* Variables and functions */
 int /*<<< orphan*/  AX25_COMMAND ; 
 int /*<<< orphan*/  AX25_DISC ; 
 int /*<<< orphan*/  AX25_POLLON ; 
#define  AX25_PROTO_DAMA_SLAVE 135 
#define  AX25_PROTO_STD_DUPLEX 134 
#define  AX25_PROTO_STD_SIMPLEX 133 
#define  AX25_STATE_0 132 
#define  AX25_STATE_1 131 
#define  AX25_STATE_2 130 
#define  AX25_STATE_3 129 
#define  AX25_STATE_4 128 
 size_t AX25_VALUES_PROTOCOL ; 
 int /*<<< orphan*/  SEND_SHUTDOWN ; 
 int /*<<< orphan*/  SOCK_DESTROY ; 
 scalar_t__ SOCK_SEQPACKET ; 
 void* TCP_CLOSE ; 
 int /*<<< orphan*/  ax25_calculate_t1 (TYPE_2__*) ; 
 int /*<<< orphan*/  ax25_clear_queues (TYPE_2__*) ; 
 int /*<<< orphan*/  ax25_destroy_socket (TYPE_2__*) ; 
 int /*<<< orphan*/  ax25_disconnect (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ax25_send_control (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* ax25_sk (struct sock*) ; 
 int /*<<< orphan*/  ax25_start_t1timer (TYPE_2__*) ; 
 int /*<<< orphan*/  ax25_stop_idletimer (TYPE_2__*) ; 
 int /*<<< orphan*/  ax25_stop_t2timer (TYPE_2__*) ; 
 int /*<<< orphan*/  ax25_stop_t3timer (TYPE_2__*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  sock_orphan (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  stub2 (struct sock*) ; 

__attribute__((used)) static int ax25_release(struct socket *sock)
{
	struct sock *sk = sock->sk;
	ax25_cb *ax25;

	if (sk == NULL)
		return 0;

	sock_hold(sk);
	sock_orphan(sk);
	lock_sock(sk);
	ax25 = ax25_sk(sk);

	if (sk->sk_type == SOCK_SEQPACKET) {
		switch (ax25->state) {
		case AX25_STATE_0:
			release_sock(sk);
			ax25_disconnect(ax25, 0);
			lock_sock(sk);
			ax25_destroy_socket(ax25);
			break;

		case AX25_STATE_1:
		case AX25_STATE_2:
			ax25_send_control(ax25, AX25_DISC, AX25_POLLON, AX25_COMMAND);
			release_sock(sk);
			ax25_disconnect(ax25, 0);
			lock_sock(sk);
			ax25_destroy_socket(ax25);
			break;

		case AX25_STATE_3:
		case AX25_STATE_4:
			ax25_clear_queues(ax25);
			ax25->n2count = 0;

			switch (ax25->ax25_dev->values[AX25_VALUES_PROTOCOL]) {
			case AX25_PROTO_STD_SIMPLEX:
			case AX25_PROTO_STD_DUPLEX:
				ax25_send_control(ax25,
						  AX25_DISC,
						  AX25_POLLON,
						  AX25_COMMAND);
				ax25_stop_t2timer(ax25);
				ax25_stop_t3timer(ax25);
				ax25_stop_idletimer(ax25);
				break;
#ifdef CONFIG_AX25_DAMA_SLAVE
			case AX25_PROTO_DAMA_SLAVE:
				ax25_stop_t3timer(ax25);
				ax25_stop_idletimer(ax25);
				break;
#endif
			}
			ax25_calculate_t1(ax25);
			ax25_start_t1timer(ax25);
			ax25->state = AX25_STATE_2;
			sk->sk_state                = TCP_CLOSE;
			sk->sk_shutdown            |= SEND_SHUTDOWN;
			sk->sk_state_change(sk);
			sock_set_flag(sk, SOCK_DESTROY);
			break;

		default:
			break;
		}
	} else {
		sk->sk_state     = TCP_CLOSE;
		sk->sk_shutdown |= SEND_SHUTDOWN;
		sk->sk_state_change(sk);
		ax25_destroy_socket(ax25);
	}

	sock->sk   = NULL;
	release_sock(sk);
	sock_put(sk);

	return 0;
}