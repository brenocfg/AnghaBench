#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {int backend_ndx; TYPE_10__* backend; } ;
typedef  TYPE_5__ network_mysqld_con_lua_t ;
struct TYPE_17__ {TYPE_9__* server; int /*<<< orphan*/  srv; TYPE_5__* plugin_con_state; } ;
typedef  TYPE_6__ network_mysqld_con ;
typedef  int /*<<< orphan*/  network_connection_pool_entry ;
typedef  int /*<<< orphan*/  network_connection_pool ;
struct TYPE_19__ {int is_authed; int /*<<< orphan*/  event; int /*<<< orphan*/  fd; TYPE_7__* response; TYPE_4__* dst; TYPE_2__* src; } ;
struct TYPE_18__ {int /*<<< orphan*/  username; } ;
struct TYPE_15__ {TYPE_3__* name; } ;
struct TYPE_14__ {int /*<<< orphan*/  str; } ;
struct TYPE_13__ {TYPE_1__* name; } ;
struct TYPE_12__ {int /*<<< orphan*/  str; } ;
struct TYPE_11__ {int /*<<< orphan*/  connected_clients; } ;

/* Variables and functions */
 int /*<<< orphan*/  C (char*) ; 
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  G_STRLOC ; 
 int /*<<< orphan*/  chassis_event_add_local (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * chassis_event_thread_pool (TYPE_10__*) ; 
 int /*<<< orphan*/  event_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_atomic_int_compare_and_exchange (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_atomic_int_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_string_assign_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_warning (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * network_connection_pool_add (int /*<<< orphan*/ *,TYPE_9__*) ; 
 TYPE_7__* network_mysqld_auth_response_new () ; 
 int /*<<< orphan*/  network_mysqld_con_idle_handle ; 

int network_connection_pool_lua_add_connection(network_mysqld_con *con) {
	network_connection_pool_entry *pool_entry = NULL;
	network_mysqld_con_lua_t *st = con->plugin_con_state;

	/* con-server is already disconnected, got out */
	if (!con->server) return 0;

    /* TODO bug fix */
    /* when mysql return unkonw packet, response is null, insert the socket into pool cause segment fault. */
    /* ? should init socket->challenge  ? */
    /* if response is null, conn has not been authed, use an invalid username. */
    if(!con->server->response)
    {
        g_warning("%s: (remove) remove socket from pool, response is NULL, src is %s, dst is %s",
            G_STRLOC, con->server->src->name->str, con->server->dst->name->str);

        con->server->response = network_mysqld_auth_response_new();
        g_string_assign_len(con->server->response->username, C("mysql_proxy_invalid_user"));
    }

	/* the server connection is still authed */
	con->server->is_authed = 1;

	/* insert the server socket into the connection pool */
	network_connection_pool* pool = chassis_event_thread_pool(st->backend);
	pool_entry = network_connection_pool_add(pool, con->server);

	if (pool_entry) {
		event_set(&(con->server->event), con->server->fd, EV_READ, network_mysqld_con_idle_handle, pool_entry);
		chassis_event_add_local(con->srv, &(con->server->event)); /* add a event, but stay in the same thread */
	}

    if (!g_atomic_int_compare_and_exchange(&st->backend->connected_clients, 0, 0)) {
        g_atomic_int_dec_and_test(&st->backend->connected_clients);    
        //g_critical("add_connection: %08x's connected_clients is %d\n", backend,  backend->connected_clients);
    }

//	st->backend->connected_clients--;
	st->backend = NULL;
	st->backend_ndx = -1;
	
	con->server = NULL;

	return 0;
}