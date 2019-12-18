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
struct sock {int /*<<< orphan*/  sk_callback_lock; scalar_t__ sk_no_check; int /*<<< orphan*/  sk_write_space; int /*<<< orphan*/  sk_state_change; int /*<<< orphan*/  sk_data_ready; int /*<<< orphan*/ * sk_user_data; } ;
struct iscsi_sw_tcp_conn {int /*<<< orphan*/  old_write_space; int /*<<< orphan*/  old_state_change; int /*<<< orphan*/  old_data_ready; TYPE_1__* sock; } ;
struct TYPE_2__ {struct sock* sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
iscsi_sw_tcp_conn_restore_callbacks(struct iscsi_sw_tcp_conn *tcp_sw_conn)
{
	struct sock *sk = tcp_sw_conn->sock->sk;

	/* restore socket callbacks, see also: iscsi_conn_set_callbacks() */
	write_lock_bh(&sk->sk_callback_lock);
	sk->sk_user_data    = NULL;
	sk->sk_data_ready   = tcp_sw_conn->old_data_ready;
	sk->sk_state_change = tcp_sw_conn->old_state_change;
	sk->sk_write_space  = tcp_sw_conn->old_write_space;
	sk->sk_no_check	 = 0;
	write_unlock_bh(&sk->sk_callback_lock);
}