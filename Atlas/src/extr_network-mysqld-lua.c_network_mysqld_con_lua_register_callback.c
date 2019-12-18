#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  network_mysqld_register_callback_ret ;
struct TYPE_8__ {int /*<<< orphan*/ * queries; } ;
struct TYPE_9__ {int /*<<< orphan*/ * L; int /*<<< orphan*/  L_ref; TYPE_1__ injected; } ;
typedef  TYPE_2__ network_mysqld_con_lua_t ;
struct TYPE_10__ {TYPE_5__* srv; TYPE_2__* plugin_con_state; } ;
typedef  TYPE_3__ network_mysqld_con ;
struct TYPE_11__ {int /*<<< orphan*/  L; } ;
typedef  TYPE_4__ lua_scope ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  con ;
struct TYPE_12__ {TYPE_4__* sc; } ;
typedef  int /*<<< orphan*/  GQueue ;

/* Variables and functions */
 int LUA_GLOBALSINDEX ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  REGISTER_CALLBACK_EXECUTE_FAILED ; 
 int /*<<< orphan*/  REGISTER_CALLBACK_LOAD_FAILED ; 
 int /*<<< orphan*/  REGISTER_CALLBACK_SUCCESS ; 
 int /*<<< orphan*/  g_assert (int) ; 
 int /*<<< orphan*/  g_critical (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_getfenv (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ lua_getmetatable (int /*<<< orphan*/ *,int) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int lua_isfunction (int /*<<< orphan*/ *,int) ; 
 int lua_istable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lua_newthread (int /*<<< orphan*/ ) ; 
 void* lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_pcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setfenv (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_xmove (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  network_mysqld_con_getmetatable (int /*<<< orphan*/ *) ; 
 scalar_t__ network_mysqld_lua_load_script (TYPE_4__*,char const*) ; 
 int /*<<< orphan*/  network_mysqld_lua_setup_global (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  proxy_getqueuemetatable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  response_get ; 
 int /*<<< orphan*/  response_set ; 

network_mysqld_register_callback_ret network_mysqld_con_lua_register_callback(network_mysqld_con *con, const char *lua_script) {
	lua_State *L = NULL;
	network_mysqld_con_lua_t *st   = con->plugin_con_state;

	lua_scope  *sc = con->srv->sc;

	GQueue **q_p;
	network_mysqld_con **con_p;
	int stack_top;

	if (!lua_script) return REGISTER_CALLBACK_SUCCESS;

	if (st->L) {
		/* we have to rewrite _G.proxy to point to the local proxy */
		L = st->L;

		g_assert(lua_isfunction(L, -1));

		lua_getfenv(L, -1);
		g_assert(lua_istable(L, -1));

		lua_getglobal(L, "proxy");
		lua_getmetatable(L, -1); /* meta(_G.proxy) */

		lua_getfield(L, -3, "__proxy"); /* fenv.__proxy */
		lua_setfield(L, -2, "__index"); /* meta[_G.proxy].__index = fenv.__proxy */

		lua_getfield(L, -3, "__proxy"); /* fenv.__proxy */
		lua_setfield(L, -2, "__newindex"); /* meta[_G.proxy].__newindex = fenv.__proxy */

		lua_pop(L, 3);

		g_assert(lua_isfunction(L, -1));

		return REGISTER_CALLBACK_SUCCESS; /* the script-env already setup, get out of here */
	}

	/* handles loading the file from disk/cache*/
	if (0 != network_mysqld_lua_load_script(sc, lua_script)) {
		/* loading script failed */
		return REGISTER_CALLBACK_LOAD_FAILED;
	}

	/* sets up global tables */
	network_mysqld_lua_setup_global(sc->L, con->srv);

	/**
	 * create a side thread for this connection
	 *
	 * (this is not pre-emptive, it is just a new stack in the global env)
	 */
	L = lua_newthread(sc->L);

	st->L_ref = luaL_ref(sc->L, LUA_REGISTRYINDEX);

	stack_top = lua_gettop(L);

	/* get the script from the global stack */
	lua_xmove(sc->L, L, 1);
	g_assert(lua_isfunction(L, -1));

	lua_newtable(L); /* my empty environment aka {}              (sp += 1) 1 */

	lua_newtable(L); /* the meta-table for the new env           (sp += 1) 2 */

	lua_pushvalue(L, LUA_GLOBALSINDEX);                       /* (sp += 1) 3 */
	lua_setfield(L, -2, "__index"); /* { __index = _G }          (sp -= 1) 2 */
	lua_setmetatable(L, -2); /* setmetatable({}, {__index = _G}) (sp -= 1) 1 */

	lua_newtable(L); /* __proxy = { }                            (sp += 1) 2 */

	g_assert(lua_istable(L, -1));

	q_p = lua_newuserdata(L, sizeof(GQueue *));               /* (sp += 1) 3 */
	*q_p = st->injected.queries;

	/*
	 * proxy.queries
	 *
	 * implement a queue
	 *
	 * - append(type, query)
	 * - prepend(type, query)
	 * - reset()
	 * - len() and #proxy.queue
	 *
	 */
	proxy_getqueuemetatable(L);

	lua_pushvalue(L, -1); /* meta.__index = meta */
	lua_setfield(L, -2, "__index");

	lua_setmetatable(L, -2);


	lua_setfield(L, -2, "queries"); /* proxy.queries = <userdata> */

	/*
	 * proxy.connection is (mostly) read-only
	 *
	 * .thread_id  = ... thread-id against this server
	 * .backend_id = ... index into proxy.global.backends[ndx]
	 *
	 */

	con_p = lua_newuserdata(L, sizeof(con));                          /* (sp += 1) */
	*con_p = con;

	network_mysqld_con_getmetatable(L);
	lua_setmetatable(L, -2);          /* tie the metatable to the udata   (sp -= 1) */

	lua_setfield(L, -2, "connection"); /* proxy.connection = <udata>     (sp -= 1) */

	/*
	 * proxy.response knows 3 fields with strict types:
	 *
	 * .type = <int>
	 * .errmsg = <string>
	 * .resultset = { 
	 *   fields = { 
	 *     { type = <int>, name = <string > }, 
	 *     { ... } }, 
	 *   rows = { 
	 *     { ..., ... }, 
	 *     { ..., ... } }
	 * }
	 */
	lua_newtable(L);
#if 0
	lua_newtable(L); /* the meta-table for the response-table    (sp += 1) */
	lua_pushcfunction(L, response_get);                       /* (sp += 1) */
	lua_setfield(L, -2, "__index");                           /* (sp -= 1) */
	lua_pushcfunction(L, response_set);                       /* (sp += 1) */
	lua_setfield(L, -2, "__newindex");                        /* (sp -= 1) */
	lua_setmetatable(L, -2); /* tie the metatable to response    (sp -= 1) */
#endif
	lua_setfield(L, -2, "response");

	lua_setfield(L, -2, "__proxy");

	/* patch the _G.proxy to point here */
	lua_getglobal(L, "proxy");
	g_assert(lua_istable(L, -1));

	if (0 == lua_getmetatable(L, -1)) { /* meta(_G.proxy) */
		/* no metatable yet */

		lua_newtable(L);
	}
	g_assert(lua_istable(L, -1));

	lua_getfield(L, -3, "__proxy"); /* fenv.__proxy */
	g_assert(lua_istable(L, -1));
	lua_setfield(L, -2, "__index"); /* meta[_G.proxy].__index = fenv.__proxy */

	lua_getfield(L, -3, "__proxy"); /* fenv.__proxy */
	lua_setfield(L, -2, "__newindex"); /* meta[_G.proxy].__newindex = fenv.__proxy */

	lua_setmetatable(L, -2);

	lua_pop(L, 1);  /* _G.proxy */

	g_assert(lua_isfunction(L, -2));
	g_assert(lua_istable(L, -1));

	lua_setfenv(L, -2); /* on the stack should be a modified env (sp -= 1) */

	/* cache the script in this connection */
	g_assert(lua_isfunction(L, -1));
	lua_pushvalue(L, -1);

	/* run the script once to get the functions set in the global scope */
	if (lua_pcall(L, 0, 0, 0) != 0) {
		g_critical("(lua-error) [%s]\n%s", lua_script, lua_tostring(L, -1));

		lua_pop(L, 1); /* errmsg */

		luaL_unref(sc->L, LUA_REGISTRYINDEX, st->L_ref);

		return REGISTER_CALLBACK_EXECUTE_FAILED;
	}

	st->L = L;

	g_assert(lua_isfunction(L, -1));
	g_assert(lua_gettop(L) - stack_top == 1);

	return REGISTER_CALLBACK_SUCCESS;
}