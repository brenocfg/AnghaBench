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
struct TYPE_4__ {int /*<<< orphan*/  con_cleanup; int /*<<< orphan*/  con_send_local_infile_result; int /*<<< orphan*/  con_read_local_infile_result; int /*<<< orphan*/  con_read_local_infile_data; int /*<<< orphan*/  con_send_query_result; int /*<<< orphan*/  con_read_query_result; int /*<<< orphan*/  con_read_query; int /*<<< orphan*/  con_read_auth_result; int /*<<< orphan*/  con_read_auth; int /*<<< orphan*/  con_read_handshake; int /*<<< orphan*/  con_connect_server; int /*<<< orphan*/  con_init; } ;
struct TYPE_5__ {TYPE_1__ plugins; } ;
typedef  TYPE_2__ network_mysqld_con ;

/* Variables and functions */
 int /*<<< orphan*/  proxy_connect_server ; 
 int /*<<< orphan*/  proxy_disconnect_client ; 
 int /*<<< orphan*/  proxy_init ; 
 int /*<<< orphan*/  proxy_read_auth ; 
 int /*<<< orphan*/  proxy_read_auth_result ; 
 int /*<<< orphan*/  proxy_read_handshake ; 
 int /*<<< orphan*/  proxy_read_local_infile_data ; 
 int /*<<< orphan*/  proxy_read_local_infile_result ; 
 int /*<<< orphan*/  proxy_read_query ; 
 int /*<<< orphan*/  proxy_read_query_result ; 
 int /*<<< orphan*/  proxy_send_local_infile_result ; 
 int /*<<< orphan*/  proxy_send_query_result ; 

int network_mysqld_proxy_connection_init(network_mysqld_con *con) {
	con->plugins.con_init                      = proxy_init;
	con->plugins.con_connect_server            = proxy_connect_server;
	con->plugins.con_read_handshake            = proxy_read_handshake;
	con->plugins.con_read_auth                 = proxy_read_auth;
	con->plugins.con_read_auth_result          = proxy_read_auth_result;
	con->plugins.con_read_query                = proxy_read_query;
	con->plugins.con_read_query_result         = proxy_read_query_result;
	con->plugins.con_send_query_result         = proxy_send_query_result;
	con->plugins.con_read_local_infile_data = proxy_read_local_infile_data;
	con->plugins.con_read_local_infile_result = proxy_read_local_infile_result;
	con->plugins.con_send_local_infile_result = proxy_send_local_infile_result;
	con->plugins.con_cleanup                   = proxy_disconnect_client;

	return 0;
}