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
struct rds_connection {int /*<<< orphan*/  c_state; } ;

/* Variables and functions */
 scalar_t__ RDS_CONN_CONNECTING ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
rds_conn_connecting(struct rds_connection *conn)
{
	return atomic_read(&conn->c_state) == RDS_CONN_CONNECTING;
}