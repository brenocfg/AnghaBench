#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_13__ ;

/* Type definitions */
struct TYPE_20__ {TYPE_2__* recv_queue; } ;
typedef  TYPE_5__ network_socket ;
typedef  int network_mysqld_lua_stmt_ret ;
struct TYPE_19__ {TYPE_13__* queries; } ;
struct TYPE_21__ {TYPE_4__ injected; int /*<<< orphan*/ * L; } ;
typedef  TYPE_6__ network_mysqld_con_lua_t ;
struct TYPE_22__ {TYPE_5__* client; TYPE_3__* config; void* state; TYPE_6__* plugin_con_state; } ;
typedef  TYPE_7__ network_mysqld_con ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_24__ {TYPE_8__* data; } ;
struct TYPE_23__ {int len; char* str; } ;
struct TYPE_18__ {int /*<<< orphan*/  lua_script; } ;
struct TYPE_17__ {TYPE_1__* chunks; } ;
struct TYPE_16__ {TYPE_9__* head; } ;
struct TYPE_15__ {int /*<<< orphan*/  length; } ;
typedef  TYPE_8__ GString ;
typedef  TYPE_9__ GList ;

/* Variables and functions */
 int /*<<< orphan*/  C (char*) ; 
 char COM_QUERY ; 
 void* CON_STATE_SEND_ERROR ; 
 int NET_HEADER_SIZE ; 
#define  PROXY_NO_DECISION 133 
 int PROXY_SEND_INJECTION ; 
#define  PROXY_SEND_QUERY 132 
#define  PROXY_SEND_RESULT 131 
#define  REGISTER_CALLBACK_EXECUTE_FAILED 130 
#define  REGISTER_CALLBACK_LOAD_FAILED 129 
#define  REGISTER_CALLBACK_SUCCESS 128 
 scalar_t__ g_ascii_strncasecmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_assert (scalar_t__) ; 
 int /*<<< orphan*/  g_critical (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_getfenv (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_getfield_literal (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_isfunction (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isnumber (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_istable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_pcall (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int lua_tonumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  network_injection_queue_reset (TYPE_13__*) ; 
 int /*<<< orphan*/  network_mysqld_con_lua_handle_proxy_response (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int network_mysqld_con_lua_register_callback (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_mysqld_con_send_error (TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static network_mysqld_lua_stmt_ret admin_lua_read_query(network_mysqld_con *con) {
	network_mysqld_con_lua_t *st = con->plugin_con_state;
	char command = -1;
	network_socket *recv_sock = con->client;
	GList   *chunk  = recv_sock->recv_queue->chunks->head;
	GString *packet = chunk->data;

	if (packet->len < NET_HEADER_SIZE) return PROXY_SEND_QUERY; /* packet too short */

	command = packet->str[NET_HEADER_SIZE + 0];

	if (COM_QUERY == command) {
		/* we need some more data after the COM_QUERY */
		if (packet->len < NET_HEADER_SIZE + 2) return PROXY_SEND_QUERY;

		/* LOAD DATA INFILE is nasty */
		if (packet->len - NET_HEADER_SIZE - 1 >= sizeof("LOAD ") - 1 &&
		    0 == g_ascii_strncasecmp(packet->str + NET_HEADER_SIZE + 1, C("LOAD "))) return PROXY_SEND_QUERY;
	}

	network_injection_queue_reset(st->injected.queries);

	/* ok, here we go */

#ifdef HAVE_LUA_H
	switch(network_mysqld_con_lua_register_callback(con, con->config->lua_script)) {
		case REGISTER_CALLBACK_SUCCESS:
			break;
		case REGISTER_CALLBACK_LOAD_FAILED:
			network_mysqld_con_send_error(con->client, C("MySQL Proxy Lua script failed to load. Check the error log."));
			con->state = CON_STATE_SEND_ERROR;
			return PROXY_SEND_RESULT;
		case REGISTER_CALLBACK_EXECUTE_FAILED:
			network_mysqld_con_send_error(con->client, C("MySQL Proxy Lua script failed to execute. Check the error log."));
			con->state = CON_STATE_SEND_ERROR;
			return PROXY_SEND_RESULT;
	}

	if (st->L) {
		lua_State *L = st->L;
		network_mysqld_lua_stmt_ret ret = PROXY_NO_DECISION;

		g_assert(lua_isfunction(L, -1));
		lua_getfenv(L, -1);
		g_assert(lua_istable(L, -1));

		/**
		 * reset proxy.response to a empty table 
		 */
		lua_getfield(L, -1, "proxy");
		g_assert(lua_istable(L, -1));

		lua_newtable(L);
		lua_setfield(L, -2, "response");

		lua_pop(L, 1);
		
		/**
		 * get the call back
		 */
		lua_getfield_literal(L, -1, C("read_query"));
		if (lua_isfunction(L, -1)) {

			/* pass the packet as parameter */
			lua_pushlstring(L, packet->str + NET_HEADER_SIZE, packet->len - NET_HEADER_SIZE);

			if (lua_pcall(L, 1, 1, 0) != 0) {
				/* hmm, the query failed */
				g_critical("(read_query) %s", lua_tostring(L, -1));

				lua_pop(L, 2); /* fenv + errmsg */

				/* perhaps we should clean up ?*/

				return PROXY_SEND_QUERY;
			} else {
				if (lua_isnumber(L, -1)) {
					ret = lua_tonumber(L, -1);
				}
				lua_pop(L, 1);
			}

			switch (ret) {
			case PROXY_SEND_RESULT:
				/* check the proxy.response table for content,
				 *
				 */
	
				if (network_mysqld_con_lua_handle_proxy_response(con, con->config->lua_script)) {
					/**
					 * handling proxy.response failed
					 *
					 * send a ERR packet
					 */
			
					network_mysqld_con_send_error(con->client, C("(lua) handling proxy.response failed, check error-log"));
				}
	
				break;
			case PROXY_NO_DECISION:
				/**
				 * PROXY_NO_DECISION and PROXY_SEND_QUERY may pick another backend
				 */
				break;
			case PROXY_SEND_QUERY:
				/* send the injected queries
				 *
				 * injection_new(..., query);
				 * 
				 *  */

				if (st->injected.queries->length) {
					ret = PROXY_SEND_INJECTION;
				}
	
				break;
			default:
				break;
			}
			lua_pop(L, 1); /* fenv */
		} else {
			lua_pop(L, 2); /* fenv + nil */
		}

		g_assert(lua_isfunction(L, -1));

		if (ret != PROXY_NO_DECISION) {
			return ret;
		}
	}
#endif
	return PROXY_NO_DECISION;
}