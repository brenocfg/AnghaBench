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
struct rds_ib_connection {int dummy; } ;
struct rds_connection {struct rds_ib_connection* c_transport_data; } ;

/* Variables and functions */
 scalar_t__ rds_conn_up (struct rds_connection*) ; 
 int /*<<< orphan*/  rds_ib_attempt_ack (struct rds_ib_connection*) ; 
 int /*<<< orphan*/  rdsdebug (char*,struct rds_connection*) ; 

int rds_ib_recv(struct rds_connection *conn)
{
	struct rds_ib_connection *ic = conn->c_transport_data;
	int ret = 0;

	rdsdebug("conn %p\n", conn);
	if (rds_conn_up(conn))
		rds_ib_attempt_ack(ic);

	return ret;
}