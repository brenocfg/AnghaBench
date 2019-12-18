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
typedef  int /*<<< orphan*/  network_backends_t ;
typedef  int /*<<< orphan*/  network_backend_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  backend ;

/* Variables and functions */
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ luaL_checkself (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  network_backend_lua_getmetatable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * network_backends_get (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int proxy_backends_get(lua_State *L) {
	network_backend_t *backend; 
	network_backend_t **backend_p;

	network_backends_t *bs = *(network_backends_t **)luaL_checkself(L);
	int backend_ndx = luaL_checkinteger(L, 2) - 1; /** lua is indexes from 1, C from 0 */
	
	/* check that we are in range for a _int_ */
	if (NULL == (backend = network_backends_get(bs, backend_ndx))) {
		lua_pushnil(L);

		return 1;
	}

	backend_p = lua_newuserdata(L, sizeof(backend)); /* the table underneath proxy.global.backends[ndx] */
	*backend_p = backend;

	network_backend_lua_getmetatable(L);
	lua_setmetatable(L, -2);

	return 1;
}