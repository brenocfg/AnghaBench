#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  weight; TYPE_2__* uuid; int /*<<< orphan*/  type; int /*<<< orphan*/  state; int /*<<< orphan*/  addr; int /*<<< orphan*/  connected_clients; } ;
typedef  TYPE_1__ network_backend_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  gsize ;
struct TYPE_4__ {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  C (char*) ; 
 int /*<<< orphan*/  S (TYPE_2__*) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ luaL_checkself (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  network_address_lua_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strleq (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proxy_backend_get(lua_State *L) {
	network_backend_t *backend = *(network_backend_t **)luaL_checkself(L);
	gsize keysize = 0;
	const char *key = luaL_checklstring(L, 2, &keysize);

	if (strleq(key, keysize, C("connected_clients"))) {
		lua_pushinteger(L, backend->connected_clients);
	} else if (strleq(key, keysize, C("dst"))) {
		network_address_lua_push(L, backend->addr);
	} else if (strleq(key, keysize, C("state"))) {
		lua_pushinteger(L, backend->state);
	} else if (strleq(key, keysize, C("type"))) {
		lua_pushinteger(L, backend->type);
	} else if (strleq(key, keysize, C("uuid"))) {
		if (backend->uuid->len) {
			lua_pushlstring(L, S(backend->uuid));
		} else {
			lua_pushnil(L);
		}
	} else if (strleq(key, keysize, C("weight"))) {
		lua_pushinteger(L, backend->weight);
	} else {
		lua_pushnil(L);
	}

	return 1;
}