#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_2__* sk; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ ax25_cb ;
struct TYPE_15__ {int sk_err; int /*<<< orphan*/  (* sk_state_change ) (TYPE_2__*) ;int /*<<< orphan*/  sk_shutdown; int /*<<< orphan*/  sk_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  AX25_STATE_0 ; 
 int /*<<< orphan*/  SEND_SHUTDOWN ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  TCP_CLOSE ; 
 int /*<<< orphan*/  ax25_clear_queues (TYPE_1__*) ; 
 int /*<<< orphan*/  ax25_link_failed (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ax25_stop_idletimer (TYPE_1__*) ; 
 int /*<<< orphan*/  ax25_stop_t1timer (TYPE_1__*) ; 
 int /*<<< orphan*/  ax25_stop_t2timer (TYPE_1__*) ; 
 int /*<<< orphan*/  ax25_stop_t3timer (TYPE_1__*) ; 
 int /*<<< orphan*/  bh_lock_sock (TYPE_2__*) ; 
 int /*<<< orphan*/  bh_unlock_sock (TYPE_2__*) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  sock_flag (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_set_flag (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void ax25_disconnect(ax25_cb *ax25, int reason)
{
	ax25_clear_queues(ax25);

	ax25_stop_t1timer(ax25);
	ax25_stop_t2timer(ax25);
	ax25_stop_t3timer(ax25);
	ax25_stop_idletimer(ax25);

	ax25->state = AX25_STATE_0;

	ax25_link_failed(ax25, reason);

	if (ax25->sk != NULL) {
		local_bh_disable();
		bh_lock_sock(ax25->sk);
		ax25->sk->sk_state     = TCP_CLOSE;
		ax25->sk->sk_err       = reason;
		ax25->sk->sk_shutdown |= SEND_SHUTDOWN;
		if (!sock_flag(ax25->sk, SOCK_DEAD)) {
			ax25->sk->sk_state_change(ax25->sk);
			sock_set_flag(ax25->sk, SOCK_DEAD);
		}
		bh_unlock_sock(ax25->sk);
		local_bh_enable();
	}
}