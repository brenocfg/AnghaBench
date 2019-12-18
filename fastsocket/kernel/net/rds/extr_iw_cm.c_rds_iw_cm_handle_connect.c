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
typedef  int /*<<< orphan*/  u32 ;
struct rds_iw_device {int /*<<< orphan*/  dma_local_lkey; } ;
struct rds_iw_connection {int /*<<< orphan*/  i_dma_local_lkey; struct rds_connection* i_cm_id; } ;
struct rds_iw_connect_private {scalar_t__ dp_ack_seq; int /*<<< orphan*/  dp_credit; int /*<<< orphan*/  dp_saddr; int /*<<< orphan*/  dp_daddr; } ;
struct rds_connection {int /*<<< orphan*/  c_cm_lock; int /*<<< orphan*/  device; struct rds_connection* context; struct rds_iw_connection* c_transport_data; } ;
struct rdma_conn_param {int dummy; } ;
struct rdma_cm_id {int /*<<< orphan*/  c_cm_lock; int /*<<< orphan*/  device; struct rdma_cm_id* context; struct rds_iw_connection* c_transport_data; } ;
struct TYPE_3__ {struct rds_iw_connect_private* private_data; } ;
struct TYPE_4__ {TYPE_1__ conn; } ;
struct rdma_cm_event {TYPE_2__ param; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (struct rds_connection*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct rds_connection*) ; 
 int /*<<< orphan*/  PTR_ERR (struct rds_connection*) ; 
 scalar_t__ RDS_CONN_CONNECTING ; 
 int /*<<< orphan*/  RDS_CONN_DOWN ; 
 scalar_t__ RDS_CONN_UP ; 
 int /*<<< orphan*/  RDS_PROTOCOL_MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDS_PROTOCOL_MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (scalar_t__) ; 
 struct rds_iw_device* ib_get_client_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rdma_accept (struct rds_connection*,struct rdma_conn_param*) ; 
 int /*<<< orphan*/  rdma_reject (struct rds_connection*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct rds_connection* rds_conn_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_conn_drop (struct rds_connection*) ; 
 scalar_t__ rds_conn_state (struct rds_connection*) ; 
 int /*<<< orphan*/  rds_conn_transition (struct rds_connection*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  rds_iw_client ; 
 int /*<<< orphan*/  rds_iw_cm_fill_conn_param (struct rds_connection*,struct rdma_conn_param*,struct rds_iw_connect_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_iw_conn_error (struct rds_connection*,char*,int) ; 
 int /*<<< orphan*/  rds_iw_protocol_compatible (struct rds_iw_connect_private const*) ; 
 int /*<<< orphan*/  rds_iw_set_flow_control (struct rds_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_iw_set_protocol (struct rds_connection*,int /*<<< orphan*/ ) ; 
 int rds_iw_setup_qp (struct rds_connection*) ; 
 int /*<<< orphan*/  rds_iw_stats_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_iw_transport ; 
 int /*<<< orphan*/  rds_send_drop_acked (struct rds_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdsdebug (char*,...) ; 
 int /*<<< orphan*/  s_iw_connect_raced ; 
 int /*<<< orphan*/  s_iw_listen_closed_stale ; 

int rds_iw_cm_handle_connect(struct rdma_cm_id *cm_id,
				    struct rdma_cm_event *event)
{
	const struct rds_iw_connect_private *dp = event->param.conn.private_data;
	struct rds_iw_connect_private dp_rep;
	struct rds_connection *conn = NULL;
	struct rds_iw_connection *ic = NULL;
	struct rdma_conn_param conn_param;
	struct rds_iw_device *rds_iwdev;
	u32 version;
	int err, destroy = 1;

	/* Check whether the remote protocol version matches ours. */
	version = rds_iw_protocol_compatible(dp);
	if (!version)
		goto out;

	rdsdebug("saddr %pI4 daddr %pI4 RDSv%u.%u\n",
		 &dp->dp_saddr, &dp->dp_daddr,
		 RDS_PROTOCOL_MAJOR(version), RDS_PROTOCOL_MINOR(version));

	conn = rds_conn_create(dp->dp_daddr, dp->dp_saddr, &rds_iw_transport,
			       GFP_KERNEL);
	if (IS_ERR(conn)) {
		rdsdebug("rds_conn_create failed (%ld)\n", PTR_ERR(conn));
		conn = NULL;
		goto out;
	}

	/*
	 * The connection request may occur while the
	 * previous connection exist, e.g. in case of failover.
	 * But as connections may be initiated simultaneously
	 * by both hosts, we have a random backoff mechanism -
	 * see the comment above rds_queue_reconnect()
	 */
	mutex_lock(&conn->c_cm_lock);
	if (!rds_conn_transition(conn, RDS_CONN_DOWN, RDS_CONN_CONNECTING)) {
		if (rds_conn_state(conn) == RDS_CONN_UP) {
			rdsdebug("incoming connect while connecting\n");
			rds_conn_drop(conn);
			rds_iw_stats_inc(s_iw_listen_closed_stale);
		} else
		if (rds_conn_state(conn) == RDS_CONN_CONNECTING) {
			/* Wait and see - our connect may still be succeeding */
			rds_iw_stats_inc(s_iw_connect_raced);
		}
		mutex_unlock(&conn->c_cm_lock);
		goto out;
	}

	ic = conn->c_transport_data;

	rds_iw_set_protocol(conn, version);
	rds_iw_set_flow_control(conn, be32_to_cpu(dp->dp_credit));

	/* If the peer gave us the last packet it saw, process this as if
	 * we had received a regular ACK. */
	if (dp->dp_ack_seq)
		rds_send_drop_acked(conn, be64_to_cpu(dp->dp_ack_seq), NULL);

	BUG_ON(cm_id->context);
	BUG_ON(ic->i_cm_id);

	ic->i_cm_id = cm_id;
	cm_id->context = conn;

	rds_iwdev = ib_get_client_data(cm_id->device, &rds_iw_client);
	ic->i_dma_local_lkey = rds_iwdev->dma_local_lkey;

	/* We got halfway through setting up the ib_connection, if we
	 * fail now, we have to take the long route out of this mess. */
	destroy = 0;

	err = rds_iw_setup_qp(conn);
	if (err) {
		rds_iw_conn_error(conn, "rds_iw_setup_qp failed (%d)\n", err);
		mutex_unlock(&conn->c_cm_lock);
		goto out;
	}

	rds_iw_cm_fill_conn_param(conn, &conn_param, &dp_rep, version);

	/* rdma_accept() calls rdma_reject() internally if it fails */
	err = rdma_accept(cm_id, &conn_param);
	mutex_unlock(&conn->c_cm_lock);
	if (err) {
		rds_iw_conn_error(conn, "rdma_accept failed (%d)\n", err);
		goto out;
	}

	return 0;

out:
	rdma_reject(cm_id, NULL, 0);
	return destroy;
}