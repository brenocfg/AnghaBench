#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct rds_ib_connection {struct rds_connection* i_cm_id; } ;
struct rds_ib_connect_private {scalar_t__ dp_ack_seq; int /*<<< orphan*/  dp_credit; int /*<<< orphan*/  dp_saddr; int /*<<< orphan*/  dp_daddr; } ;
struct TYPE_14__ {TYPE_5__* path_rec; } ;
struct rds_connection {int /*<<< orphan*/  c_cm_lock; struct rds_connection* context; struct rds_ib_connection* c_transport_data; TYPE_6__ route; } ;
struct rdma_conn_param {int dummy; } ;
struct rdma_cm_id {int /*<<< orphan*/  c_cm_lock; struct rdma_cm_id* context; struct rds_ib_connection* c_transport_data; TYPE_6__ route; } ;
struct TYPE_15__ {int /*<<< orphan*/  initiator_depth; int /*<<< orphan*/  responder_resources; struct rds_ib_connect_private* private_data; } ;
struct TYPE_16__ {TYPE_7__ conn; } ;
struct rdma_cm_event {TYPE_8__ param; } ;
typedef  scalar_t__ __be64 ;
struct TYPE_11__ {scalar_t__ interface_id; } ;
struct TYPE_12__ {TYPE_3__ global; } ;
struct TYPE_9__ {scalar_t__ interface_id; } ;
struct TYPE_10__ {TYPE_1__ global; } ;
struct TYPE_13__ {TYPE_4__ dgid; TYPE_2__ sgid; } ;

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
 scalar_t__ be64_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rdma_accept (struct rds_connection*,struct rdma_conn_param*) ; 
 int /*<<< orphan*/  rdma_reject (struct rds_connection*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct rds_connection* rds_conn_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_conn_drop (struct rds_connection*) ; 
 scalar_t__ rds_conn_state (struct rds_connection*) ; 
 int /*<<< orphan*/  rds_conn_transition (struct rds_connection*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  rds_ib_cm_fill_conn_param (struct rds_connection*,struct rdma_conn_param*,struct rds_ib_connect_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_ib_conn_error (struct rds_connection*,char*,int) ; 
 int /*<<< orphan*/  rds_ib_protocol_compatible (struct rdma_cm_event*) ; 
 int /*<<< orphan*/  rds_ib_set_flow_control (struct rds_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_ib_set_protocol (struct rds_connection*,int /*<<< orphan*/ ) ; 
 int rds_ib_setup_qp (struct rds_connection*) ; 
 int /*<<< orphan*/  rds_ib_stats_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_ib_transport ; 
 int /*<<< orphan*/  rds_send_drop_acked (struct rds_connection*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdsdebug (char*,...) ; 
 int /*<<< orphan*/  s_ib_connect_raced ; 
 int /*<<< orphan*/  s_ib_listen_closed_stale ; 

int rds_ib_cm_handle_connect(struct rdma_cm_id *cm_id,
				    struct rdma_cm_event *event)
{
	__be64 lguid = cm_id->route.path_rec->sgid.global.interface_id;
	__be64 fguid = cm_id->route.path_rec->dgid.global.interface_id;
	const struct rds_ib_connect_private *dp = event->param.conn.private_data;
	struct rds_ib_connect_private dp_rep;
	struct rds_connection *conn = NULL;
	struct rds_ib_connection *ic = NULL;
	struct rdma_conn_param conn_param;
	u32 version;
	int err = 1, destroy = 1;

	/* Check whether the remote protocol version matches ours. */
	version = rds_ib_protocol_compatible(event);
	if (!version)
		goto out;

	rdsdebug("saddr %pI4 daddr %pI4 RDSv%u.%u lguid 0x%llx fguid "
		 "0x%llx\n", &dp->dp_saddr, &dp->dp_daddr,
		 RDS_PROTOCOL_MAJOR(version), RDS_PROTOCOL_MINOR(version),
		 (unsigned long long)be64_to_cpu(lguid),
		 (unsigned long long)be64_to_cpu(fguid));

	conn = rds_conn_create(dp->dp_daddr, dp->dp_saddr, &rds_ib_transport,
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
			rds_ib_stats_inc(s_ib_listen_closed_stale);
		} else
		if (rds_conn_state(conn) == RDS_CONN_CONNECTING) {
			/* Wait and see - our connect may still be succeeding */
			rds_ib_stats_inc(s_ib_connect_raced);
		}
		goto out;
	}

	ic = conn->c_transport_data;

	rds_ib_set_protocol(conn, version);
	rds_ib_set_flow_control(conn, be32_to_cpu(dp->dp_credit));

	/* If the peer gave us the last packet it saw, process this as if
	 * we had received a regular ACK. */
	if (dp->dp_ack_seq)
		rds_send_drop_acked(conn, be64_to_cpu(dp->dp_ack_seq), NULL);

	BUG_ON(cm_id->context);
	BUG_ON(ic->i_cm_id);

	ic->i_cm_id = cm_id;
	cm_id->context = conn;

	/* We got halfway through setting up the ib_connection, if we
	 * fail now, we have to take the long route out of this mess. */
	destroy = 0;

	err = rds_ib_setup_qp(conn);
	if (err) {
		rds_ib_conn_error(conn, "rds_ib_setup_qp failed (%d)\n", err);
		goto out;
	}

	rds_ib_cm_fill_conn_param(conn, &conn_param, &dp_rep, version,
		event->param.conn.responder_resources,
		event->param.conn.initiator_depth);

	/* rdma_accept() calls rdma_reject() internally if it fails */
	err = rdma_accept(cm_id, &conn_param);
	if (err)
		rds_ib_conn_error(conn, "rdma_accept failed (%d)\n", err);

out:
	if (conn)
		mutex_unlock(&conn->c_cm_lock);
	if (err)
		rdma_reject(cm_id, NULL, 0);
	return destroy;
}