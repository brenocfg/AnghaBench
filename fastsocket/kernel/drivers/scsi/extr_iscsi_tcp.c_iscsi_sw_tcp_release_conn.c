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
struct socket {int /*<<< orphan*/  sk; } ;
struct iscsi_tcp_conn {struct iscsi_sw_tcp_conn* dd_data; } ;
struct iscsi_sw_tcp_conn {struct socket* sock; } ;
struct iscsi_session {int /*<<< orphan*/  lock; } ;
struct iscsi_conn {struct iscsi_tcp_conn* dd_data; struct iscsi_session* session; } ;

/* Variables and functions */
 int /*<<< orphan*/  iscsi_sw_tcp_conn_restore_callbacks (struct iscsi_sw_tcp_conn*) ; 
 int /*<<< orphan*/  sock_hold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sockfd_put (struct socket*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iscsi_sw_tcp_release_conn(struct iscsi_conn *conn)
{
	struct iscsi_session *session = conn->session;
	struct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	struct iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;
	struct socket *sock = tcp_sw_conn->sock;

	if (!sock)
		return;

	sock_hold(sock->sk);
	iscsi_sw_tcp_conn_restore_callbacks(tcp_sw_conn);
	sock_put(sock->sk);

	spin_lock_bh(&session->lock);
	tcp_sw_conn->sock = NULL;
	spin_unlock_bh(&session->lock);
	sockfd_put(sock);
}