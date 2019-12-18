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
typedef  scalar_t__ uint64_t ;
struct socket {TYPE_1__* ops; struct sock* sk; } ;
struct sock {int sk_reuse; int sk_sndtimeo; int /*<<< orphan*/  sk_allocation; } ;
struct iscsi_tcp_conn {struct iscsi_sw_tcp_conn* dd_data; } ;
struct iscsi_sw_tcp_conn {struct socket* sock; int /*<<< orphan*/  sendpage; } ;
struct iscsi_session {int /*<<< orphan*/  lock; } ;
struct iscsi_conn {struct iscsi_tcp_conn* dd_data; } ;
struct iscsi_cls_session {struct iscsi_session* dd_data; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  sendpage; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int HZ ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int iscsi_conn_bind (struct iscsi_cls_session*,struct iscsi_cls_conn*,int) ; 
 int /*<<< orphan*/  iscsi_conn_printk (int /*<<< orphan*/ ,struct iscsi_conn*,char*,int) ; 
 int /*<<< orphan*/  iscsi_sw_tcp_conn_set_callbacks (struct iscsi_conn*) ; 
 int /*<<< orphan*/  iscsi_tcp_hdr_recv_prep (struct iscsi_tcp_conn*) ; 
 struct socket* sockfd_lookup (int,int*) ; 
 int /*<<< orphan*/  sockfd_put (struct socket*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
iscsi_sw_tcp_conn_bind(struct iscsi_cls_session *cls_session,
		       struct iscsi_cls_conn *cls_conn, uint64_t transport_eph,
		       int is_leading)
{
	struct iscsi_session *session = cls_session->dd_data;
	struct iscsi_conn *conn = cls_conn->dd_data;
	struct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	struct iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;
	struct sock *sk;
	struct socket *sock;
	int err;

	/* lookup for existing socket */
	sock = sockfd_lookup((int)transport_eph, &err);
	if (!sock) {
		iscsi_conn_printk(KERN_ERR, conn,
				  "sockfd_lookup failed %d\n", err);
		return -EEXIST;
	}

	err = iscsi_conn_bind(cls_session, cls_conn, is_leading);
	if (err)
		goto free_socket;

	spin_lock_bh(&session->lock);
	/* bind iSCSI connection and socket */
	tcp_sw_conn->sock = sock;
	spin_unlock_bh(&session->lock);

	/* setup Socket parameters */
	sk = sock->sk;
	sk->sk_reuse = 1;
	sk->sk_sndtimeo = 15 * HZ; /* FIXME: make it configurable */
	sk->sk_allocation = GFP_ATOMIC;

	iscsi_sw_tcp_conn_set_callbacks(conn);
	tcp_sw_conn->sendpage = tcp_sw_conn->sock->ops->sendpage;
	/*
	 * set receive state machine into initial state
	 */
	iscsi_tcp_hdr_recv_prep(tcp_conn);
	return 0;

free_socket:
	sockfd_put(sock);
	return err;
}