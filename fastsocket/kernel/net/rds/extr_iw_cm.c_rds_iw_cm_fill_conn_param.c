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
typedef  int /*<<< orphan*/  u32 ;
struct rds_iw_connection {int /*<<< orphan*/  i_credits; scalar_t__ i_flowctl; } ;
struct rds_iw_connect_private {int responder_resources; int initiator_depth; int private_data_len; struct rds_iw_connect_private* private_data; int /*<<< orphan*/  dp_credit; int /*<<< orphan*/  dp_ack_seq; int /*<<< orphan*/  dp_protocol_minor_mask; int /*<<< orphan*/  dp_protocol_minor; int /*<<< orphan*/  dp_protocol_major; int /*<<< orphan*/  dp_daddr; int /*<<< orphan*/  dp_saddr; } ;
struct rds_connection {int /*<<< orphan*/  c_faddr; int /*<<< orphan*/  c_laddr; struct rds_iw_connection* c_transport_data; } ;
struct rdma_conn_param {int responder_resources; int initiator_depth; int private_data_len; struct rdma_conn_param* private_data; int /*<<< orphan*/  dp_credit; int /*<<< orphan*/  dp_ack_seq; int /*<<< orphan*/  dp_protocol_minor_mask; int /*<<< orphan*/  dp_protocol_minor; int /*<<< orphan*/  dp_protocol_major; int /*<<< orphan*/  dp_daddr; int /*<<< orphan*/  dp_saddr; } ;

/* Variables and functions */
 unsigned int IB_GET_POST_CREDITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IB_SET_POST_CREDITS (unsigned int) ; 
 int /*<<< orphan*/  RDS_IW_SUPPORTED_PROTOCOLS ; 
 int /*<<< orphan*/  RDS_PROTOCOL_MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDS_PROTOCOL_MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (unsigned int) ; 
 int /*<<< orphan*/  memset (struct rds_iw_connect_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rds_iw_piggyb_ack (struct rds_iw_connection*) ; 

__attribute__((used)) static void rds_iw_cm_fill_conn_param(struct rds_connection *conn,
			struct rdma_conn_param *conn_param,
			struct rds_iw_connect_private *dp,
			u32 protocol_version)
{
	struct rds_iw_connection *ic = conn->c_transport_data;

	memset(conn_param, 0, sizeof(struct rdma_conn_param));
	/* XXX tune these? */
	conn_param->responder_resources = 1;
	conn_param->initiator_depth = 1;

	if (dp) {
		memset(dp, 0, sizeof(*dp));
		dp->dp_saddr = conn->c_laddr;
		dp->dp_daddr = conn->c_faddr;
		dp->dp_protocol_major = RDS_PROTOCOL_MAJOR(protocol_version);
		dp->dp_protocol_minor = RDS_PROTOCOL_MINOR(protocol_version);
		dp->dp_protocol_minor_mask = cpu_to_be16(RDS_IW_SUPPORTED_PROTOCOLS);
		dp->dp_ack_seq = rds_iw_piggyb_ack(ic);

		/* Advertise flow control */
		if (ic->i_flowctl) {
			unsigned int credits;

			credits = IB_GET_POST_CREDITS(atomic_read(&ic->i_credits));
			dp->dp_credit = cpu_to_be32(credits);
			atomic_sub(IB_SET_POST_CREDITS(credits), &ic->i_credits);
		}

		conn_param->private_data = dp;
		conn_param->private_data_len = sizeof(*dp);
	}
}