#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct socket {TYPE_2__* sk; TYPE_1__* ops; int /*<<< orphan*/  type; } ;
struct rds_connection {int dummy; } ;
struct inet_sock {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; int /*<<< orphan*/  dport; int /*<<< orphan*/  sport; } ;
struct TYPE_4__ {int /*<<< orphan*/  sk_protocol; int /*<<< orphan*/  sk_type; int /*<<< orphan*/  sk_family; } ;
struct TYPE_3__ {int (* accept ) (struct socket*,struct socket*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct rds_connection*) ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int PTR_ERR (struct rds_connection*) ; 
 int /*<<< orphan*/  RDS_CONN_CONNECTING ; 
 int /*<<< orphan*/  RDS_CONN_DOWN ; 
 scalar_t__ RDS_CONN_UP ; 
 struct inet_sock* inet_sk (TYPE_2__*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 struct rds_connection* rds_conn_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_conn_drop (struct rds_connection*) ; 
 scalar_t__ rds_conn_state (struct rds_connection*) ; 
 int /*<<< orphan*/  rds_conn_transition (struct rds_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_connect_complete (struct rds_connection*) ; 
 int /*<<< orphan*/  rds_tcp_set_callbacks (struct socket*,struct rds_connection*) ; 
 int /*<<< orphan*/  rds_tcp_stats_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_tcp_transport ; 
 int /*<<< orphan*/  rds_tcp_tune (struct socket*) ; 
 int /*<<< orphan*/  rdsdebug (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_tcp_connect_raced ; 
 int /*<<< orphan*/  s_tcp_listen_closed_stale ; 
 int sock_create_lite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct socket**) ; 
 int /*<<< orphan*/  sock_release (struct socket*) ; 
 int stub1 (struct socket*,struct socket*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rds_tcp_accept_one(struct socket *sock)
{
	struct socket *new_sock = NULL;
	struct rds_connection *conn;
	int ret;
	struct inet_sock *inet;

	ret = sock_create_lite(sock->sk->sk_family, sock->sk->sk_type,
			       sock->sk->sk_protocol, &new_sock);
	if (ret)
		goto out;

	new_sock->type = sock->type;
	new_sock->ops = sock->ops;
	ret = sock->ops->accept(sock, new_sock, O_NONBLOCK);
	if (ret < 0)
		goto out;

	rds_tcp_tune(new_sock);

	inet = inet_sk(new_sock->sk);

	rdsdebug("accepted tcp %pI4:%u -> %pI4:%u\n",
		 &inet->saddr, ntohs(inet->sport),
		 &inet->daddr, ntohs(inet->dport));

	conn = rds_conn_create(inet->saddr, inet->daddr, &rds_tcp_transport,
			       GFP_KERNEL);
	if (IS_ERR(conn)) {
		ret = PTR_ERR(conn);
		goto out;
	}

	/*
	 * see the comment above rds_queue_delayed_reconnect()
	 */
	if (!rds_conn_transition(conn, RDS_CONN_DOWN, RDS_CONN_CONNECTING)) {
		if (rds_conn_state(conn) == RDS_CONN_UP)
			rds_tcp_stats_inc(s_tcp_listen_closed_stale);
		else
			rds_tcp_stats_inc(s_tcp_connect_raced);
		rds_conn_drop(conn);
		ret = 0;
		goto out;
	}

	rds_tcp_set_callbacks(new_sock, conn);
	rds_connect_complete(conn);
	new_sock = NULL;
	ret = 0;

out:
	if (new_sock)
		sock_release(new_sock);
	return ret;
}