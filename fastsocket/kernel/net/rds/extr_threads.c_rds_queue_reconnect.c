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
struct rds_connection {unsigned long c_reconnect_jiffies; int /*<<< orphan*/  c_conn_w; int /*<<< orphan*/  c_faddr; int /*<<< orphan*/  c_laddr; int /*<<< orphan*/  c_flags; } ;
typedef  int /*<<< orphan*/  rand ;

/* Variables and functions */
 int /*<<< orphan*/  RDS_RECONNECT_PENDING ; 
 int /*<<< orphan*/  get_random_bytes (unsigned long*,int) ; 
 unsigned long min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  rds_sysctl_reconnect_max_jiffies ; 
 unsigned long rds_sysctl_reconnect_min_jiffies ; 
 int /*<<< orphan*/  rds_wq ; 
 int /*<<< orphan*/  rdsdebug (char*,...) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rds_queue_reconnect(struct rds_connection *conn)
{
	unsigned long rand;

	rdsdebug("conn %p for %pI4 to %pI4 reconnect jiffies %lu\n",
	  conn, &conn->c_laddr, &conn->c_faddr,
	  conn->c_reconnect_jiffies);

	set_bit(RDS_RECONNECT_PENDING, &conn->c_flags);
	if (conn->c_reconnect_jiffies == 0) {
		conn->c_reconnect_jiffies = rds_sysctl_reconnect_min_jiffies;
		queue_delayed_work(rds_wq, &conn->c_conn_w, 0);
		return;
	}

	get_random_bytes(&rand, sizeof(rand));
	rdsdebug("%lu delay %lu ceil conn %p for %pI4 -> %pI4\n",
		 rand % conn->c_reconnect_jiffies, conn->c_reconnect_jiffies,
		 conn, &conn->c_laddr, &conn->c_faddr);
	queue_delayed_work(rds_wq, &conn->c_conn_w,
			   rand % conn->c_reconnect_jiffies);

	conn->c_reconnect_jiffies = min(conn->c_reconnect_jiffies * 2,
					rds_sysctl_reconnect_max_jiffies);
}