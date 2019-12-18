#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int proxy_queue_add_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {int /*<<< orphan*/  resultset_is_needed; } ;
typedef  TYPE_1__ injection ;
typedef  int /*<<< orphan*/  GString ;
typedef  int /*<<< orphan*/  GQueue ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  PROXY_QUEUE_ADD_APPEND 129 
#define  PROXY_QUEUE_ADD_PREPEND 128 
 int /*<<< orphan*/  g_assert_not_reached () ; 
 int /*<<< orphan*/  g_string_append_len (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/ * g_string_sized_new (size_t) ; 
 TYPE_1__* injection_new (int,int /*<<< orphan*/ *) ; 
 int luaL_argerror (int /*<<< orphan*/ *,int,char*) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 scalar_t__ luaL_checkself (int /*<<< orphan*/ *) ; 
 int luaL_opt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  luaL_typerror (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_isboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_istable ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_toboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  network_injection_queue_append (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  network_injection_queue_prepend (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  proxy_lua_dumpstack_verbose (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int proxy_queue_add(lua_State *L, proxy_queue_add_t type) {
	GQueue *q = *(GQueue **)luaL_checkself(L);
	int resp_type = luaL_checkinteger(L, 2);
	size_t str_len;
	const char *str = luaL_checklstring(L, 3, &str_len);
	injection *inj;

	GString *query = g_string_sized_new(str_len);
	g_string_append_len(query, str, str_len);

	inj = injection_new(resp_type, query);
	inj->resultset_is_needed = FALSE;

	/* check the 4th (last) param */
	switch (luaL_opt(L, lua_istable, 4, -1)) {
	case -1:
		/* none or nil */
		break;
	case 1:
		lua_getfield(L, 4, "resultset_is_needed");
		if (lua_isnil(L, -1)) {
			/* no defined */
		} else if (lua_isboolean(L, -1)) {
			inj->resultset_is_needed = lua_toboolean(L, -1);
		} else {
			switch (type) {
			case PROXY_QUEUE_ADD_APPEND:
				return luaL_argerror(L, 4, ":append(..., { resultset_is_needed = boolean } ), is %s");
			case PROXY_QUEUE_ADD_PREPEND:
				return luaL_argerror(L, 4, ":prepend(..., { resultset_is_needed = boolean } ), is %s");
			}
		}

		lua_pop(L, 1);
		break;
	default:
		proxy_lua_dumpstack_verbose(L);
		luaL_typerror(L, 4, "table");
		break;
	}

	switch (type) {
	case PROXY_QUEUE_ADD_APPEND:
		network_injection_queue_append(q, inj);
		return 0;
	case PROXY_QUEUE_ADD_PREPEND:
		network_injection_queue_prepend(q, inj);
		return 0;
	}

	g_assert_not_reached();
}