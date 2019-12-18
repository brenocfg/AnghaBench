#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  event; int /*<<< orphan*/  fd; int /*<<< orphan*/  dst; } ;
typedef  TYPE_1__ network_socket ;
struct TYPE_15__ {TYPE_1__* server; TYPE_3__* config; } ;
typedef  TYPE_2__ network_mysqld_con ;
struct TYPE_16__ {int /*<<< orphan*/  address; TYPE_2__* listen_con; } ;
typedef  TYPE_3__ chassis_plugin_config ;
struct TYPE_17__ {int /*<<< orphan*/  event_base; } ;
typedef  TYPE_4__ chassis ;

/* Variables and functions */
 int EV_PERSIST ; 
 int EV_READ ; 
 int /*<<< orphan*/  event_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_base_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  g_strdup (char*) ; 
 scalar_t__ network_address_set_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_mysqld_add_connection (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  network_mysqld_con_accept ; 
 TYPE_2__* network_mysqld_con_new () ; 
 int /*<<< orphan*/  network_mysqld_server_connection_init (TYPE_2__*) ; 
 scalar_t__ network_socket_bind (TYPE_1__*) ; 
 TYPE_1__* network_socket_new () ; 

__attribute__((used)) static int network_mysqld_debug_plugin_apply_config(chassis *chas, chassis_plugin_config *config) {
	network_mysqld_con *con;
	network_socket *listen_sock;

	if (!config->address) config->address = g_strdup(":4043");

	/** 
	 * create a connection handle for the listen socket 
	 */
	con = network_mysqld_con_new();
	network_mysqld_add_connection(chas, con);
	con->config = config;

	config->listen_con = con;
	
	listen_sock = network_socket_new();
	con->server = listen_sock;

	/* set the plugin hooks as we want to apply them to the new connections too later */
	network_mysqld_server_connection_init(con);

	/* FIXME: network_socket_set_address() */
	if (0 != network_address_set_address(listen_sock->dst, config->address)) {
		return -1;
	}

	/* FIXME: network_socket_bind() */
	if (0 != network_socket_bind(listen_sock)) {
		return -1;
	}

	/**
	 * call network_mysqld_con_accept() with this connection when we are done
	 */
	event_set(&(listen_sock->event), listen_sock->fd, EV_READ|EV_PERSIST, network_mysqld_con_accept, con);
	event_base_set(chas->event_base, &(listen_sock->event));
	event_add(&(listen_sock->event), NULL);

	return 0;
}