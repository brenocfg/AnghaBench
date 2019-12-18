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
struct rds_connection {int /*<<< orphan*/  c_conn_w; int /*<<< orphan*/  c_flags; } ;

/* Variables and functions */
 scalar_t__ RDS_CONN_DOWN ; 
 int /*<<< orphan*/  RDS_RECONNECT_PENDING ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ rds_conn_state (struct rds_connection*) ; 
 int /*<<< orphan*/  rds_wq ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rds_conn_connect_if_down(struct rds_connection *conn)
{
	if (rds_conn_state(conn) == RDS_CONN_DOWN &&
	    !test_and_set_bit(RDS_RECONNECT_PENDING, &conn->c_flags))
		queue_delayed_work(rds_wq, &conn->c_conn_w, 0);
}