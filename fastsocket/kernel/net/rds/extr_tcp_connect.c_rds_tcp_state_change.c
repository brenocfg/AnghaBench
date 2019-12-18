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
struct sock {void (* sk_state_change ) (struct sock*) ;int sk_state; int /*<<< orphan*/  sk_callback_lock; struct rds_connection* sk_user_data; } ;
struct rds_tcp_connection {void (* t_orig_state_change ) (struct sock*) ;int /*<<< orphan*/  t_sock; } ;
struct rds_connection {struct rds_tcp_connection* c_transport_data; } ;

/* Variables and functions */
#define  TCP_CLOSE 131 
#define  TCP_ESTABLISHED 130 
#define  TCP_SYN_RECV 129 
#define  TCP_SYN_SENT 128 
 int /*<<< orphan*/  rds_conn_drop (struct rds_connection*) ; 
 int /*<<< orphan*/  rds_connect_complete (struct rds_connection*) ; 
 int /*<<< orphan*/  rdsdebug (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

void rds_tcp_state_change(struct sock *sk)
{
	void (*state_change)(struct sock *sk);
	struct rds_connection *conn;
	struct rds_tcp_connection *tc;

	read_lock(&sk->sk_callback_lock);
	conn = sk->sk_user_data;
	if (!conn) {
		state_change = sk->sk_state_change;
		goto out;
	}
	tc = conn->c_transport_data;
	state_change = tc->t_orig_state_change;

	rdsdebug("sock %p state_change to %d\n", tc->t_sock, sk->sk_state);

	switch(sk->sk_state) {
		/* ignore connecting sockets as they make progress */
		case TCP_SYN_SENT:
		case TCP_SYN_RECV:
			break;
		case TCP_ESTABLISHED:
			rds_connect_complete(conn);
			break;
		case TCP_CLOSE:
			rds_conn_drop(conn);
		default:
			break;
	}
out:
	read_unlock(&sk->sk_callback_lock);
	state_change(sk);
}