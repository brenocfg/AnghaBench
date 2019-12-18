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
struct rds_ib_connection {scalar_t__ i_ack_recv; int /*<<< orphan*/  i_recv_ring; int /*<<< orphan*/  i_recv_cq; struct rds_connection* conn; } ;
struct rds_ib_ack_state {scalar_t__ ack_recv; scalar_t__ ack_recv_valid; int /*<<< orphan*/  ack_required; int /*<<< orphan*/  ack_next; scalar_t__ ack_next_valid; int /*<<< orphan*/  member_0; } ;
struct rds_connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_CQ_SOLICITED ; 
 int /*<<< orphan*/  ib_req_notify_cq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rds_conn_up (struct rds_connection*) ; 
 int /*<<< orphan*/  rds_ib_attempt_ack (struct rds_ib_connection*) ; 
 int /*<<< orphan*/  rds_ib_recv_refill (struct rds_connection*,int /*<<< orphan*/ ) ; 
 scalar_t__ rds_ib_ring_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ rds_ib_ring_low (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_ib_set_ack (struct rds_ib_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_ib_stats_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_poll_cq (struct rds_ib_connection*,struct rds_ib_ack_state*) ; 
 int /*<<< orphan*/  rds_send_drop_acked (struct rds_connection*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_ib_rx_ring_empty ; 

void rds_ib_recv_tasklet_fn(unsigned long data)
{
	struct rds_ib_connection *ic = (struct rds_ib_connection *) data;
	struct rds_connection *conn = ic->conn;
	struct rds_ib_ack_state state = { 0, };

	rds_poll_cq(ic, &state);
	ib_req_notify_cq(ic->i_recv_cq, IB_CQ_SOLICITED);
	rds_poll_cq(ic, &state);

	if (state.ack_next_valid)
		rds_ib_set_ack(ic, state.ack_next, state.ack_required);
	if (state.ack_recv_valid && state.ack_recv > ic->i_ack_recv) {
		rds_send_drop_acked(conn, state.ack_recv, NULL);
		ic->i_ack_recv = state.ack_recv;
	}
	if (rds_conn_up(conn))
		rds_ib_attempt_ack(ic);

	/* If we ever end up with a really empty receive ring, we're
	 * in deep trouble, as the sender will definitely see RNR
	 * timeouts. */
	if (rds_ib_ring_empty(&ic->i_recv_ring))
		rds_ib_stats_inc(s_ib_rx_ring_empty);

	if (rds_ib_ring_low(&ic->i_recv_ring))
		rds_ib_recv_refill(conn, 0);
}