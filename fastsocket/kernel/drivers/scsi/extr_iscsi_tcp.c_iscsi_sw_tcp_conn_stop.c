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
struct iscsi_tcp_conn {struct iscsi_sw_tcp_conn* dd_data; } ;
struct iscsi_sw_tcp_conn {struct socket* sock; } ;
struct iscsi_conn {struct iscsi_tcp_conn* dd_data; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;
struct TYPE_2__ {scalar_t__ sk_sleep; int /*<<< orphan*/  sk_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  iscsi_conn_stop (struct iscsi_cls_conn*,int) ; 
 int /*<<< orphan*/  iscsi_suspend_tx (struct iscsi_conn*) ; 
 int /*<<< orphan*/  iscsi_sw_tcp_release_conn (struct iscsi_conn*) ; 
 int /*<<< orphan*/  wake_up_interruptible (scalar_t__) ; 

__attribute__((used)) static void iscsi_sw_tcp_conn_stop(struct iscsi_cls_conn *cls_conn, int flag)
{
	struct iscsi_conn *conn = cls_conn->dd_data;
	struct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	struct iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;
	struct socket *sock = tcp_sw_conn->sock;

	/* userspace may have goofed up and not bound us */
	if (!sock)
		return;

	if (sock->sk->sk_sleep) {
		sock->sk->sk_err = EIO;
		wake_up_interruptible(sock->sk->sk_sleep);
	}

	/* stop xmit side */
	iscsi_suspend_tx(conn);

	/* stop recv side and release socket */
	iscsi_sw_tcp_release_conn(conn);

	iscsi_conn_stop(cls_conn, flag);
}