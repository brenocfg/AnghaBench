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
struct rds_iw_connection {struct rdma_cm_id* i_cm_id; int /*<<< orphan*/  i_flowctl; } ;
struct rds_iw_connect_private {int dummy; } ;
struct rds_connection {struct rds_iw_connection* c_transport_data; } ;
struct rdma_conn_param {int dummy; } ;
struct rdma_cm_id {struct rds_connection* context; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDS_PROTOCOL_3_0 ; 
 int /*<<< orphan*/  RDS_PROTOCOL_VERSION ; 
 int rdma_connect (struct rdma_cm_id*,struct rdma_conn_param*) ; 
 int /*<<< orphan*/  rds_iw_cm_fill_conn_param (struct rds_connection*,struct rdma_conn_param*,struct rds_iw_connect_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_iw_conn_error (struct rds_connection*,char*,int) ; 
 int /*<<< orphan*/  rds_iw_set_protocol (struct rds_connection*,int /*<<< orphan*/ ) ; 
 int rds_iw_setup_qp (struct rds_connection*) ; 
 int /*<<< orphan*/  rds_iw_sysctl_flow_control ; 

int rds_iw_cm_initiate_connect(struct rdma_cm_id *cm_id)
{
	struct rds_connection *conn = cm_id->context;
	struct rds_iw_connection *ic = conn->c_transport_data;
	struct rdma_conn_param conn_param;
	struct rds_iw_connect_private dp;
	int ret;

	/* If the peer doesn't do protocol negotiation, we must
	 * default to RDSv3.0 */
	rds_iw_set_protocol(conn, RDS_PROTOCOL_3_0);
	ic->i_flowctl = rds_iw_sysctl_flow_control;	/* advertise flow control */

	ret = rds_iw_setup_qp(conn);
	if (ret) {
		rds_iw_conn_error(conn, "rds_iw_setup_qp failed (%d)\n", ret);
		goto out;
	}

	rds_iw_cm_fill_conn_param(conn, &conn_param, &dp, RDS_PROTOCOL_VERSION);

	ret = rdma_connect(cm_id, &conn_param);
	if (ret)
		rds_iw_conn_error(conn, "rdma_connect failed (%d)\n", ret);

out:
	/* Beware - returning non-zero tells the rdma_cm to destroy
	 * the cm_id. We should certainly not do it as long as we still
	 * "own" the cm_id. */
	if (ret) {
		struct rds_iw_connection *ic = conn->c_transport_data;

		if (ic->i_cm_id == cm_id)
			ret = 0;
	}
	return ret;
}