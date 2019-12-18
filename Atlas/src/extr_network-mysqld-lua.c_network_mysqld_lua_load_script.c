#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  L; } ;
typedef  TYPE_1__ lua_scope ;

/* Variables and functions */
 int /*<<< orphan*/  G_STRLOC ; 
 int /*<<< orphan*/  g_assert (int) ; 
 int /*<<< orphan*/  g_critical (char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_error (char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int lua_gettop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_isfunction (int /*<<< orphan*/ ,int) ; 
 scalar_t__ lua_isstring (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_scope_load_script (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_type (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_typename (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int network_mysqld_lua_load_script(lua_scope *sc, const char *lua_script) {
	int stack_top = lua_gettop(sc->L);

	if (!lua_script) return -1;
	
	/* a script cache
	 *
	 * we cache the scripts globally in the registry and move a copy of it 
	 * to the new script scope on success.
	 */
	lua_scope_load_script(sc, lua_script);

	if (lua_isstring(sc->L, -1)) {
		g_critical("%s: lua_load_file(%s) failed: %s", 
				G_STRLOC, 
				lua_script, lua_tostring(sc->L, -1));

		lua_pop(sc->L, 1); /* remove the error-msg from the stack */
		
		return -1;
	} else if (!lua_isfunction(sc->L, -1)) {
		g_error("%s: luaL_loadfile(%s): returned a %s", 
				G_STRLOC, 
				lua_script, lua_typename(sc->L, lua_type(sc->L, -1)));
	}

	g_assert(lua_gettop(sc->L) - stack_top == 1);

	return 0;
}