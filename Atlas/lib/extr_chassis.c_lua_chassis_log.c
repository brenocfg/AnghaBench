#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {int currentline; char* source; char* short_src; } ;
typedef  TYPE_1__ lua_Debug ;
struct TYPE_6__ {scalar_t__ base_dir; } ;
typedef  TYPE_2__ chassis ;

/* Variables and functions */
 int /*<<< orphan*/  CHASSIS_LUA_REGISTRY_KEY ; 
 char const G_DIR_SEPARATOR ; 
 int /*<<< orphan*/  G_LOG_DOMAIN ; 
#define  G_LOG_LEVEL_CRITICAL 133 
#define  G_LOG_LEVEL_DEBUG 132 
#define  G_LOG_LEVEL_ERROR 131 
#define  G_LOG_LEVEL_INFO 130 
#define  G_LOG_LEVEL_MESSAGE 129 
#define  G_LOG_LEVEL_WARNING 128 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  g_log (int /*<<< orphan*/ ,int const,char*,char const*,int,char const*) ; 
 scalar_t__ g_str_has_prefix (char const*,scalar_t__) ; 
 int luaL_checkoption (int /*<<< orphan*/ *,int,char*,char const* const*) ; 
 char* luaL_optstring (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_getinfo (int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  lua_getstack (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_topointer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 

__attribute__((used)) static int lua_chassis_log(lua_State *L) {
    static const char *const log_names[] = {"error", "critical",
        "warning", "message", "info", "debug", NULL};
	static const int log_levels[] = {G_LOG_LEVEL_ERROR, G_LOG_LEVEL_CRITICAL,
        G_LOG_LEVEL_WARNING, G_LOG_LEVEL_MESSAGE,
        G_LOG_LEVEL_INFO, G_LOG_LEVEL_DEBUG};

    int option = luaL_checkoption(L, 1, "message", log_names);
	const char *log_message = luaL_optstring(L, 2, "nil");
	const char *source = NULL;
	const char *first_source = "unknown";
	int currentline = -1;
	int first_line = -1;
	int stackdepth = 1;
	lua_Debug ar;
	chassis *chas;
	
	/* try to get some information about who logs this message */
	do {
		/* walk up the stack to try to find a file name */
        if (!lua_getstack(L, stackdepth, &ar)) break;
        if (!lua_getinfo(L, "Sl", &ar)) break;

		currentline = ar.currentline;
        source = ar.source;
		/* save the first short_src we have encountered,
		   in case we exceed our max stackdepth to check
		 */
		if (stackdepth == 1) {
			first_source = ar.short_src;
			first_line = ar.currentline;
		}
		/* below: '@' comes from Lua's dofile, our lua-load-factory doesn't set it when we load a file. */
	} while (++stackdepth < 11 && source && source[0] != '/' && source[0] != '@'); /* limit walking the stack to a sensible value */

	if (source) {
		if (source[0] == '@') {
			/* skip Lua's "this is from a file" indicator */
			source++;
		}
        lua_getfield(L, LUA_REGISTRYINDEX, CHASSIS_LUA_REGISTRY_KEY);
        chas = (chassis*) lua_topointer(L, -1);
        lua_pop(L, 1);
        if (chas && chas->base_dir) {
            if (g_str_has_prefix(source, chas->base_dir)) {
                source += strlen(chas->base_dir);
                /* skip a leading dir separator */
                if (source[0] == G_DIR_SEPARATOR) source++;
            }
        }
	}
    g_log(G_LOG_DOMAIN, log_levels[option], "(%s:%d) %s", (source ? source : first_source),
			(source ? currentline : first_line), log_message);
	
	return 0;
}