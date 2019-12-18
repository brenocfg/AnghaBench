#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rds_ib_recv_work {TYPE_3__* r_frag; } ;
struct rds_ib_connection {int /*<<< orphan*/  i_recv_ring; TYPE_2__* i_cm_id; struct rds_ib_recv_work* i_recvs; int /*<<< orphan*/  i_recv_cq; struct rds_connection* conn; } ;
struct rds_ib_ack_state {int dummy; } ;
struct rds_connection {int /*<<< orphan*/  c_faddr; } ;
struct TYPE_4__ {int /*<<< orphan*/  imm_data; } ;
struct ib_wc {scalar_t__ status; int /*<<< orphan*/  byte_len; TYPE_1__ ex; scalar_t__ wr_id; } ;
struct TYPE_6__ {int /*<<< orphan*/  f_sg; } ;
struct TYPE_5__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 scalar_t__ IB_WC_SUCCESS ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ib_poll_cq (int /*<<< orphan*/ ,int,struct ib_wc*) ; 
 scalar_t__ rds_conn_connecting (struct rds_connection*) ; 
 scalar_t__ rds_conn_up (struct rds_connection*) ; 
 int /*<<< orphan*/  rds_ib_conn_error (struct rds_connection*,char*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_ib_process_recv (struct rds_connection*,struct rds_ib_recv_work*,int /*<<< orphan*/ ,struct rds_ib_ack_state*) ; 
 int /*<<< orphan*/  rds_ib_ring_free (int /*<<< orphan*/ *,int) ; 
 size_t rds_ib_ring_oldest (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_ib_stats_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_ib_wc_status_str (scalar_t__) ; 
 int /*<<< orphan*/  rdsdebug (char*,unsigned long long,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_ib_rx_cq_event ; 

__attribute__((used)) static inline void rds_poll_cq(struct rds_ib_connection *ic,
			       struct rds_ib_ack_state *state)
{
	struct rds_connection *conn = ic->conn;
	struct ib_wc wc;
	struct rds_ib_recv_work *recv;

	while (ib_poll_cq(ic->i_recv_cq, 1, &wc) > 0) {
		rdsdebug("wc wr_id 0x%llx status %u (%s) byte_len %u imm_data %u\n",
			 (unsigned long long)wc.wr_id, wc.status,
			 rds_ib_wc_status_str(wc.status), wc.byte_len,
			 be32_to_cpu(wc.ex.imm_data));
		rds_ib_stats_inc(s_ib_rx_cq_event);

		recv = &ic->i_recvs[rds_ib_ring_oldest(&ic->i_recv_ring)];

		ib_dma_unmap_sg(ic->i_cm_id->device, &recv->r_frag->f_sg, 1, DMA_FROM_DEVICE);

		/*
		 * Also process recvs in connecting state because it is possible
		 * to get a recv completion _before_ the rdmacm ESTABLISHED
		 * event is processed.
		 */
		if (wc.status == IB_WC_SUCCESS) {
			rds_ib_process_recv(conn, recv, wc.byte_len, state);
		} else {
			/* We expect errors as the qp is drained during shutdown */
			if (rds_conn_up(conn) || rds_conn_connecting(conn))
				rds_ib_conn_error(conn, "recv completion on %pI4 had "
						  "status %u (%s), disconnecting and "
						  "reconnecting\n", &conn->c_faddr,
						  wc.status,
						  rds_ib_wc_status_str(wc.status));
		}

		/*
		 * It's very important that we only free this ring entry if we've truly
		 * freed the resources allocated to the entry.  The refilling path can
		 * leak if we don't.
		 */
		rds_ib_ring_free(&ic->i_recv_ring, 1);
	}
}