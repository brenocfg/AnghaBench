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
struct rds_transport {int (* conn_alloc ) (struct rds_connection*,int /*<<< orphan*/ ) ;char* t_name; int /*<<< orphan*/  (* conn_free ) (int /*<<< orphan*/ ) ;scalar_t__ t_prefer_loopback; } ;
struct rds_connection {int c_loopback; int c_next_tx_seq; int /*<<< orphan*/  c_hash_node; int /*<<< orphan*/  c_transport_data; struct rds_connection* c_passive; scalar_t__ c_flags; int /*<<< orphan*/  c_cm_lock; int /*<<< orphan*/  c_down_w; int /*<<< orphan*/  c_conn_w; int /*<<< orphan*/  c_recv_w; int /*<<< orphan*/  c_send_w; scalar_t__ c_reconnect_jiffies; int /*<<< orphan*/  c_state; struct rds_transport* c_trans; int /*<<< orphan*/  c_retrans; int /*<<< orphan*/  c_send_queue; int /*<<< orphan*/  c_waitq; int /*<<< orphan*/  c_lock; void* c_faddr; void* c_laddr; } ;
struct hlist_head {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  void* __be32 ;

/* Variables and functions */
 int ENOMEM ; 
 struct rds_connection* ERR_PTR (int) ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDS_CONN_DOWN ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,struct hlist_head*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct rds_connection*) ; 
 struct rds_connection* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  rds_cong_add_conn (struct rds_connection*) ; 
 int rds_cong_get_maps (struct rds_connection*) ; 
 struct hlist_head* rds_conn_bucket (void*,void*) ; 
 int /*<<< orphan*/  rds_conn_count ; 
 int /*<<< orphan*/  rds_conn_lock ; 
 struct rds_connection* rds_conn_lookup (struct hlist_head*,void*,void*,struct rds_transport*) ; 
 int /*<<< orphan*/  rds_conn_slab ; 
 int /*<<< orphan*/  rds_connect_worker ; 
 struct rds_transport rds_loop_transport ; 
 int /*<<< orphan*/  rds_recv_worker ; 
 int /*<<< orphan*/  rds_send_worker ; 
 int /*<<< orphan*/  rds_shutdown_worker ; 
 struct rds_transport* rds_trans_get_preferred (void*) ; 
 int /*<<< orphan*/  rds_trans_put (struct rds_transport*) ; 
 int /*<<< orphan*/  rdsdebug (char*,struct rds_connection*,void**,void**,char*,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct rds_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rds_connection *__rds_conn_create(__be32 laddr, __be32 faddr,
				       struct rds_transport *trans, gfp_t gfp,
				       int is_outgoing)
{
	struct rds_connection *conn, *parent = NULL;
	struct hlist_head *head = rds_conn_bucket(laddr, faddr);
	struct rds_transport *loop_trans;
	unsigned long flags;
	int ret;

	rcu_read_lock();
	conn = rds_conn_lookup(head, laddr, faddr, trans);
	if (conn
	 && conn->c_loopback
	 && conn->c_trans != &rds_loop_transport
	 && !is_outgoing) {
		/* This is a looped back IB connection, and we're
		 * called by the code handling the incoming connect.
		 * We need a second connection object into which we
		 * can stick the other QP. */
		parent = conn;
		conn = parent->c_passive;
	}
	rcu_read_unlock();
	if (conn)
		goto out;

	conn = kmem_cache_zalloc(rds_conn_slab, gfp);
	if (!conn) {
		conn = ERR_PTR(-ENOMEM);
		goto out;
	}

	INIT_HLIST_NODE(&conn->c_hash_node);
	conn->c_laddr = laddr;
	conn->c_faddr = faddr;
	spin_lock_init(&conn->c_lock);
	conn->c_next_tx_seq = 1;

	init_waitqueue_head(&conn->c_waitq);
	INIT_LIST_HEAD(&conn->c_send_queue);
	INIT_LIST_HEAD(&conn->c_retrans);

	ret = rds_cong_get_maps(conn);
	if (ret) {
		kmem_cache_free(rds_conn_slab, conn);
		conn = ERR_PTR(ret);
		goto out;
	}

	/*
	 * This is where a connection becomes loopback.  If *any* RDS sockets
	 * can bind to the destination address then we'd rather the messages
	 * flow through loopback rather than either transport.
	 */
	loop_trans = rds_trans_get_preferred(faddr);
	if (loop_trans) {
		rds_trans_put(loop_trans);
		conn->c_loopback = 1;
		if (is_outgoing && trans->t_prefer_loopback) {
			/* "outgoing" connection - and the transport
			 * says it wants the connection handled by the
			 * loopback transport. This is what TCP does.
			 */
			trans = &rds_loop_transport;
		}
	}

	conn->c_trans = trans;

	ret = trans->conn_alloc(conn, gfp);
	if (ret) {
		kmem_cache_free(rds_conn_slab, conn);
		conn = ERR_PTR(ret);
		goto out;
	}

	atomic_set(&conn->c_state, RDS_CONN_DOWN);
	conn->c_reconnect_jiffies = 0;
	INIT_DELAYED_WORK(&conn->c_send_w, rds_send_worker);
	INIT_DELAYED_WORK(&conn->c_recv_w, rds_recv_worker);
	INIT_DELAYED_WORK(&conn->c_conn_w, rds_connect_worker);
	INIT_WORK(&conn->c_down_w, rds_shutdown_worker);
	mutex_init(&conn->c_cm_lock);
	conn->c_flags = 0;

	rdsdebug("allocated conn %p for %pI4 -> %pI4 over %s %s\n",
	  conn, &laddr, &faddr,
	  trans->t_name ? trans->t_name : "[unknown]",
	  is_outgoing ? "(outgoing)" : "");

	/*
	 * Since we ran without holding the conn lock, someone could
	 * have created the same conn (either normal or passive) in the
	 * interim. We check while holding the lock. If we won, we complete
	 * init and return our conn. If we lost, we rollback and return the
	 * other one.
	 */
	spin_lock_irqsave(&rds_conn_lock, flags);
	if (parent) {
		/* Creating passive conn */
		if (parent->c_passive) {
			trans->conn_free(conn->c_transport_data);
			kmem_cache_free(rds_conn_slab, conn);
			conn = parent->c_passive;
		} else {
			parent->c_passive = conn;
			rds_cong_add_conn(conn);
			rds_conn_count++;
		}
	} else {
		/* Creating normal conn */
		struct rds_connection *found;

		found = rds_conn_lookup(head, laddr, faddr, trans);
		if (found) {
			trans->conn_free(conn->c_transport_data);
			kmem_cache_free(rds_conn_slab, conn);
			conn = found;
		} else {
			hlist_add_head_rcu(&conn->c_hash_node, head);
			rds_cong_add_conn(conn);
			rds_conn_count++;
		}
	}
	spin_unlock_irqrestore(&rds_conn_lock, flags);

out:
	return conn;
}