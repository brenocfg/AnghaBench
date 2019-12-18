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
struct rds_connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rds_connect_complete (struct rds_connection*) ; 

__attribute__((used)) static int rds_loop_conn_connect(struct rds_connection *conn)
{
	rds_connect_complete(conn);
	return 0;
}