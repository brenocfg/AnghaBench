#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * srv; } ;
typedef  TYPE_1__ network_mysqld_con ;
typedef  int /*<<< orphan*/  chassis ;

/* Variables and functions */

void network_mysqld_add_connection(chassis *srv, network_mysqld_con *con) {
	con->srv = srv;
/*
	g_mutex_lock(&con_mutex);
	g_ptr_array_add(srv->priv->cons, con);
	g_mutex_unlock(&con_mutex);
*/
}