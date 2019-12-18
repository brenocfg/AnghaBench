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
struct socket {TYPE_1__* sk; } ;
struct rds_tcp_connection {int /*<<< orphan*/  t_orig_state_change; int /*<<< orphan*/  t_orig_data_ready; int /*<<< orphan*/  t_orig_write_space; int /*<<< orphan*/ * t_sock; int /*<<< orphan*/  t_list_item; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk_callback_lock; int /*<<< orphan*/ * sk_user_data; int /*<<< orphan*/  sk_state_change; int /*<<< orphan*/  sk_data_ready; int /*<<< orphan*/  sk_write_space; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_tcp_tc_count ; 
 int /*<<< orphan*/  rds_tcp_tc_list_lock ; 
 int /*<<< orphan*/  rdsdebug (char*,struct socket*,struct rds_tcp_connection*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

void rds_tcp_restore_callbacks(struct socket *sock,
			       struct rds_tcp_connection *tc)
{
	rdsdebug("restoring sock %p callbacks from tc %p\n", sock, tc);
	write_lock_bh(&sock->sk->sk_callback_lock);

	/* done under the callback_lock to serialize with write_space */
	spin_lock(&rds_tcp_tc_list_lock);
	list_del_init(&tc->t_list_item);
	rds_tcp_tc_count--;
	spin_unlock(&rds_tcp_tc_list_lock);

	tc->t_sock = NULL;

	sock->sk->sk_write_space = tc->t_orig_write_space;
	sock->sk->sk_data_ready = tc->t_orig_data_ready;
	sock->sk->sk_state_change = tc->t_orig_state_change;
	sock->sk->sk_user_data = NULL;

	write_unlock_bh(&sock->sk->sk_callback_lock);
}