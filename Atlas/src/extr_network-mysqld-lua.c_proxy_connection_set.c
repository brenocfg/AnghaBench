#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  network_socket ;
struct TYPE_7__ {int backend_ndx; int /*<<< orphan*/  connection_close; TYPE_1__* backend; } ;
typedef  TYPE_2__ network_mysqld_con_lua_t ;
struct TYPE_8__ {int /*<<< orphan*/ * server; TYPE_2__* plugin_con_state; } ;
typedef  TYPE_3__ network_mysqld_con ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  gsize ;
struct TYPE_6__ {int /*<<< orphan*/  connected_clients; } ;

/* Variables and functions */
 int /*<<< orphan*/  C (char*) ; 
 int /*<<< orphan*/  LUA_TBOOLEAN ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ luaL_checkself (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  lua_toboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  network_connection_pool_lua_add_connection (TYPE_3__*) ; 
 int /*<<< orphan*/ * network_connection_pool_lua_swap (TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  network_socket_free (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strleq (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proxy_connection_set(lua_State *L) {
	network_mysqld_con *con = *(network_mysqld_con **)luaL_checkself(L);
	network_mysqld_con_lua_t *st;
	gsize keysize = 0;
	const char *key = luaL_checklstring(L, 2, &keysize);

	st = con->plugin_con_state;

	if (strleq(key, keysize, C("backend_ndx"))) {
		/**
		 * in lua-land the ndx is based on 1, in C-land on 0 */
		int backend_ndx = luaL_checkinteger(L, 3) - 1;
		network_socket *send_sock;
			
		if (backend_ndx == -1) {
			/** drop the backend for now
			 */
			network_connection_pool_lua_add_connection(con);
		} else if (NULL != (send_sock = network_connection_pool_lua_swap(con, backend_ndx, NULL))) {
			con->server = send_sock;
		} else if (backend_ndx == -2) {
			if (st->backend != NULL) {
				st->backend->connected_clients--;
				st->backend = NULL;
			}
			st->backend_ndx = -1;
			network_socket_free(con->server);
			con->server = NULL;
		} else {
			st->backend_ndx = backend_ndx;
		}
	} else if (0 == strcmp(key, "connection_close")) {
		luaL_checktype(L, 3, LUA_TBOOLEAN);

		st->connection_close = lua_toboolean(L, 3);
	} else {
		return luaL_error(L, "proxy.connection.%s is not writable", key);
	}

	return 0;
}