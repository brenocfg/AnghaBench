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
struct rds_iw_connection {int /*<<< orphan*/  i_recv_tasklet; } ;
struct rds_connection {struct rds_iw_connection* c_transport_data; } ;
struct ib_cq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rds_iw_stats_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdsdebug (char*,struct rds_connection*,struct ib_cq*) ; 
 int /*<<< orphan*/  s_iw_rx_cq_call ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

void rds_iw_recv_cq_comp_handler(struct ib_cq *cq, void *context)
{
	struct rds_connection *conn = context;
	struct rds_iw_connection *ic = conn->c_transport_data;

	rdsdebug("conn %p cq %p\n", conn, cq);

	rds_iw_stats_inc(s_iw_rx_cq_call);

	tasklet_schedule(&ic->i_recv_tasklet);
}