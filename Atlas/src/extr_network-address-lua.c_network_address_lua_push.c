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
typedef  int /*<<< orphan*/  network_address ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/ ** lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  network_address_lua_getmetatable (int /*<<< orphan*/ *) ; 

int network_address_lua_push(lua_State *L, network_address *addr) {
	network_address **address_p;

	if (!addr) {
		lua_pushnil(L);
		return 1;
	}

	address_p = lua_newuserdata(L, sizeof(network_address));
	*address_p = addr;

	network_address_lua_getmetatable(L);
	lua_setmetatable(L, -2); /* tie the metatable to the table   (sp -= 1) */

	return 1;
}