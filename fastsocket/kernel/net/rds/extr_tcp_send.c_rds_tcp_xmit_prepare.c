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
struct rds_tcp_connection {int /*<<< orphan*/  t_sock; } ;
struct rds_connection {struct rds_tcp_connection* c_transport_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  rds_tcp_cork (int /*<<< orphan*/ ,int) ; 

void rds_tcp_xmit_prepare(struct rds_connection *conn)
{
	struct rds_tcp_connection *tc = conn->c_transport_data;

	rds_tcp_cork(tc->t_sock, 1);
}