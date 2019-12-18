#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * raw_pwds; int /*<<< orphan*/ * raw_ips; } ;
typedef  TYPE_1__ network_backends_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {TYPE_1__* backends; int /*<<< orphan*/  log_path; int /*<<< orphan*/  instance_name; } ;
typedef  TYPE_2__ chassis ;
typedef  int /*<<< orphan*/  GPtrArray ;

/* Variables and functions */
 int /*<<< orphan*/  g_assert (int) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 int lua_istable (int /*<<< orphan*/ *,int) ; 
 void* lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  network_backends_lua_getmetatable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  network_clients_lua_getmetatable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  network_mysqld_lua_init_global_fenv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  network_pwds_lua_getmetatable (int /*<<< orphan*/ *) ; 

void network_mysqld_lua_setup_global(lua_State *L , chassis *chas) {
	network_backends_t **backends_p;

	int stack_top = lua_gettop(L);

	/* TODO: if we share "proxy." with other plugins, this may fail to initialize it correctly, 
	 * because maybe they already have registered stuff in there.
	 * It would be better to have different namespaces, or any other way to make sure we initialize correctly.
	 */
	lua_getglobal(L, "proxy");
	if (lua_isnil(L, -1)) {
		lua_pop(L, 1);

		network_mysqld_lua_init_global_fenv(L);
	
		lua_getglobal(L, "proxy");
	}
	g_assert(lua_istable(L, -1));

	/* at this point we have set up:
	 *  - the script
	 *  - _G.proxy and a bunch of constants in that table
	 *  - _G.proxy.global
	 */
	
	/**
	 * register proxy.global.backends[]
	 *
	 * @see proxy_backends_get()
	 */
	lua_getfield(L, -1, "global");

    // set instance name
	// proxy.global.config.instance , value assigned when cmd start use --instance
	lua_getfield(L, -1, "config");

    lua_pushstring(L, chas->instance_name);
	lua_setfield(L, -2, "instance");

    lua_pushstring(L, chas->log_path);
	lua_setfield(L, -2, "logpath");

    lua_pop(L, 1);

    // 
	backends_p = lua_newuserdata(L, sizeof(network_backends_t *));
	*backends_p = chas->backends;

	network_backends_lua_getmetatable(L);
	lua_setmetatable(L, -2);          /* tie the metatable to the table   (sp -= 1) */

	lua_setfield(L, -2, "backends");

	GPtrArray **raw_ips_p = lua_newuserdata(L, sizeof(GPtrArray *));
	*raw_ips_p = chas->backends->raw_ips;
	network_clients_lua_getmetatable(L);
	lua_setmetatable(L, -2);
	lua_setfield(L, -2, "clients");

	GPtrArray **raw_pwds_p = lua_newuserdata(L, sizeof(GPtrArray *));
	*raw_pwds_p = chas->backends->raw_pwds;
	network_pwds_lua_getmetatable(L);
	lua_setmetatable(L, -2);
	lua_setfield(L, -2, "pwds");

	lua_pop(L, 2);  /* _G.proxy.global and _G.proxy */

	g_assert(lua_gettop(L) == stack_top);
}