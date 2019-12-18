#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  con_read_query; int /*<<< orphan*/  con_read_auth; int /*<<< orphan*/  con_init; } ;
struct TYPE_5__ {TYPE_1__ plugins; } ;
typedef  TYPE_2__ network_mysqld_con ;

/* Variables and functions */
 int /*<<< orphan*/  server_con_init ; 
 int /*<<< orphan*/  server_read_auth ; 
 int /*<<< orphan*/  server_read_query ; 

__attribute__((used)) static int network_mysqld_server_connection_init(network_mysqld_con *con) {
	con->plugins.con_init             = server_con_init;

	con->plugins.con_read_auth        = server_read_auth;

	con->plugins.con_read_query       = server_read_query;

	return 0;
}