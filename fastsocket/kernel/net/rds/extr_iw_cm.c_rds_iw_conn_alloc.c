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
struct rds_iw_connection {int /*<<< orphan*/  iw_node; struct rds_connection* conn; int /*<<< orphan*/  i_recv_ring; int /*<<< orphan*/  i_send_ring; int /*<<< orphan*/  i_ack_lock; int /*<<< orphan*/  i_recv_mutex; int /*<<< orphan*/  i_recv_tasklet; } ;
struct rds_connection {struct rds_iw_connection* c_transport_data; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iw_nodev_conns ; 
 int /*<<< orphan*/  iw_nodev_conns_lock ; 
 struct rds_iw_connection* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_iw_recv_tasklet_fn ; 
 int /*<<< orphan*/  rds_iw_ring_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_iw_sysctl_max_recv_wr ; 
 int /*<<< orphan*/  rds_iw_sysctl_max_send_wr ; 
 int /*<<< orphan*/  rdsdebug (char*,struct rds_connection*,struct rds_iw_connection*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

int rds_iw_conn_alloc(struct rds_connection *conn, gfp_t gfp)
{
	struct rds_iw_connection *ic;
	unsigned long flags;

	/* XXX too lazy? */
	ic = kzalloc(sizeof(struct rds_iw_connection), gfp);
	if (!ic)
		return -ENOMEM;

	INIT_LIST_HEAD(&ic->iw_node);
	tasklet_init(&ic->i_recv_tasklet, rds_iw_recv_tasklet_fn,
		     (unsigned long) ic);
	mutex_init(&ic->i_recv_mutex);
#ifndef KERNEL_HAS_ATOMIC64
	spin_lock_init(&ic->i_ack_lock);
#endif

	/*
	 * rds_iw_conn_shutdown() waits for these to be emptied so they
	 * must be initialized before it can be called.
	 */
	rds_iw_ring_init(&ic->i_send_ring, rds_iw_sysctl_max_send_wr);
	rds_iw_ring_init(&ic->i_recv_ring, rds_iw_sysctl_max_recv_wr);

	ic->conn = conn;
	conn->c_transport_data = ic;

	spin_lock_irqsave(&iw_nodev_conns_lock, flags);
	list_add_tail(&ic->iw_node, &iw_nodev_conns);
	spin_unlock_irqrestore(&iw_nodev_conns_lock, flags);


	rdsdebug("conn %p conn ic %p\n", conn, conn->c_transport_data);
	return 0;
}