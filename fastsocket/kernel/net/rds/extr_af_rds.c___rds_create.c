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
struct socket {int /*<<< orphan*/ * ops; } ;
struct sock {int sk_protocol; } ;
struct rds_sock {int /*<<< orphan*/  rs_item; int /*<<< orphan*/  rs_rdma_keys; int /*<<< orphan*/  rs_rdma_lock; int /*<<< orphan*/  rs_cong_list; int /*<<< orphan*/  rs_notify_queue; int /*<<< orphan*/  rs_recv_queue; int /*<<< orphan*/  rs_send_queue; int /*<<< orphan*/  rs_recv_lock; int /*<<< orphan*/  rs_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_proto_ops ; 
 struct rds_sock* rds_sk_to_rs (struct sock*) ; 
 int /*<<< orphan*/  rds_sock_count ; 
 int /*<<< orphan*/  rds_sock_list ; 
 int /*<<< orphan*/  rds_sock_lock ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_init_data (struct socket*,struct sock*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __rds_create(struct socket *sock, struct sock *sk, int protocol)
{
	struct rds_sock *rs;

	sock_init_data(sock, sk);
	sock->ops		= &rds_proto_ops;
	sk->sk_protocol		= protocol;

	rs = rds_sk_to_rs(sk);
	spin_lock_init(&rs->rs_lock);
	rwlock_init(&rs->rs_recv_lock);
	INIT_LIST_HEAD(&rs->rs_send_queue);
	INIT_LIST_HEAD(&rs->rs_recv_queue);
	INIT_LIST_HEAD(&rs->rs_notify_queue);
	INIT_LIST_HEAD(&rs->rs_cong_list);
	spin_lock_init(&rs->rs_rdma_lock);
	rs->rs_rdma_keys = RB_ROOT;

	spin_lock_bh(&rds_sock_lock);
	list_add_tail(&rs->rs_item, &rds_sock_list);
	rds_sock_count++;
	spin_unlock_bh(&rds_sock_lock);

	return 0;
}