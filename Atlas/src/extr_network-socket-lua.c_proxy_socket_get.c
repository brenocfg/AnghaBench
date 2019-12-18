#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_6__* response; TYPE_5__* challenge; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; TYPE_4__* charset_results; TYPE_3__* charset_connection; TYPE_2__* charset_client; TYPE_1__* default_db; } ;
typedef  TYPE_7__ network_socket ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  gsize ;
struct TYPE_13__ {int /*<<< orphan*/  response; int /*<<< orphan*/  username; } ;
struct TYPE_12__ {int /*<<< orphan*/  challenge; int /*<<< orphan*/  thread_id; int /*<<< orphan*/  server_version; } ;
struct TYPE_11__ {int /*<<< orphan*/  len; int /*<<< orphan*/  str; } ;
struct TYPE_10__ {int /*<<< orphan*/  len; int /*<<< orphan*/  str; } ;
struct TYPE_9__ {int /*<<< orphan*/  len; int /*<<< orphan*/  str; } ;
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/  str; } ;

/* Variables and functions */
 int /*<<< orphan*/  C (char*) ; 
 int /*<<< orphan*/  G_STRLOC ; 
 int /*<<< orphan*/  S (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_critical (char*,int /*<<< orphan*/ ,void*,void*,char const*) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ luaL_checkself (int /*<<< orphan*/ *) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int network_address_lua_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strleq (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proxy_socket_get(lua_State *L) {
	network_socket *sock = *(network_socket **)luaL_checkself(L);
	gsize keysize = 0;
	const char *key = luaL_checklstring(L, 2, &keysize);

	/**
	 * we to split it in .client and .server here
	 */

	if (strleq(key, keysize, C("default_db"))) {
		lua_pushlstring(L, sock->default_db->str, sock->default_db->len);
		return 1;
	}else if (strleq(key, keysize, C("charset_client"))) {
		lua_pushlstring(L, sock->charset_client->str, sock->charset_client->len);
		return 1;
	}else if (strleq(key, keysize, C("charset_connection"))) {
		lua_pushlstring(L, sock->charset_connection->str, sock->charset_connection->len);
		return 1;
	}else if (strleq(key, keysize, C("charset_results"))) {
		lua_pushlstring(L, sock->charset_results->str, sock->charset_results->len);
		return 1;
	}else if (strleq(key, keysize, C("address"))) {
		return luaL_error(L, ".address is deprecated. Use .src.name or .dst.name instead");
	} else if (strleq(key, keysize, C("src"))) {
		return network_address_lua_push(L, sock->src);
	} else if (strleq(key, keysize, C("dst"))) {
		return network_address_lua_push(L, sock->dst);
	}
      
	if (sock->response) {
		if (strleq(key, keysize, C("username"))) {
			lua_pushlstring(L, S(sock->response->username));
			return 1;
		} else if (strleq(key, keysize, C("scrambled_password"))) {
			lua_pushlstring(L, S(sock->response->response));
			return 1;
		}
	}

	if (sock->challenge) { /* only the server-side has mysqld_version set */
		if (strleq(key, keysize, C("mysqld_version"))) {
			lua_pushinteger(L, sock->challenge->server_version);
			return 1;
		} else if (strleq(key, keysize, C("thread_id"))) {
			lua_pushinteger(L, sock->challenge->thread_id);
			return 1;
		} else if (strleq(key, keysize, C("scramble_buffer"))) {
			lua_pushlstring(L, S(sock->challenge->challenge));
			return 1;
		}
	}
	g_critical("%s: sock->challenge: %p, sock->response: %p (looking for %s)", 
			G_STRLOC,
			(void *)sock->challenge,
			(void *)sock->response,
			key
			);

	lua_pushnil(L);

	return 1;
}