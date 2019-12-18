#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  uuid; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ network_backend_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  gsize ;

/* Variables and functions */
 int /*<<< orphan*/  C (char*) ; 
 int /*<<< orphan*/  g_string_assign_len (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  g_string_truncate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ luaL_checkself (int /*<<< orphan*/ *) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,char const*) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tointeger (int /*<<< orphan*/ *,int) ; 
 char* lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 scalar_t__ strleq (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proxy_backend_set(lua_State *L) {
	network_backend_t *backend = *(network_backend_t **)luaL_checkself(L);
	gsize keysize = 0;
	const char *key = luaL_checklstring(L, 2, &keysize);

	if (strleq(key, keysize, C("state"))) {
		backend->state = lua_tointeger(L, -1);
	} else if (strleq(key, keysize, C("uuid"))) {
		if (lua_isstring(L, -1)) {
			size_t s_len = 0;
			const char *s = lua_tolstring(L, -1, &s_len);

			g_string_assign_len(backend->uuid, s, s_len);
		} else if (lua_isnil(L, -1)) {
			g_string_truncate(backend->uuid, 0);
		} else {
			return luaL_error(L, "proxy.global.backends[...].%s has to be a string", key);
		}
	} else {
		return luaL_error(L, "proxy.global.backends[...].%s is not writable", key);
	}
	return 1;
}