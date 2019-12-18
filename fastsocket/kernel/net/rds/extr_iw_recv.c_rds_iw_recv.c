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
struct rds_iw_connection {int /*<<< orphan*/  i_recv_mutex; } ;
struct rds_connection {struct rds_iw_connection* c_transport_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_HIGHUSER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ rds_conn_up (struct rds_connection*) ; 
 int /*<<< orphan*/  rds_iw_attempt_ack (struct rds_iw_connection*) ; 
 scalar_t__ rds_iw_recv_refill (struct rds_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_iw_stats_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdsdebug (char*,struct rds_connection*) ; 
 int /*<<< orphan*/  s_iw_rx_refill_from_thread ; 

int rds_iw_recv(struct rds_connection *conn)
{
	struct rds_iw_connection *ic = conn->c_transport_data;
	int ret = 0;

	rdsdebug("conn %p\n", conn);

	/*
	 * If we get a temporary posting failure in this context then
	 * we're really low and we want the caller to back off for a bit.
	 */
	mutex_lock(&ic->i_recv_mutex);
	if (rds_iw_recv_refill(conn, GFP_KERNEL, GFP_HIGHUSER, 0))
		ret = -ENOMEM;
	else
		rds_iw_stats_inc(s_iw_rx_refill_from_thread);
	mutex_unlock(&ic->i_recv_mutex);

	if (rds_conn_up(conn))
		rds_iw_attempt_ack(ic);

	return ret;
}