#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  size_t guint ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_5__ {char* name; int /*<<< orphan*/ * stats; int /*<<< orphan*/ * (* get_stats ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ chassis_plugin ;
struct TYPE_6__ {int /*<<< orphan*/  stats; TYPE_1__* modules; } ;
typedef  TYPE_3__ chassis ;
struct TYPE_4__ {size_t len; TYPE_2__** pdata; } ;
typedef  int /*<<< orphan*/  GHashTable ;

/* Variables and functions */
 int /*<<< orphan*/  CHASSIS_LUA_REGISTRY_KEY ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * chassis_stats_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chassis_stats_setluaval ; 
 scalar_t__ g_ascii_strcasecmp (char const*,char*) ; 
 int /*<<< orphan*/  g_hash_table_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_hash_table_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int luaL_argerror (int /*<<< orphan*/ *,int,char*) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ lua_topointer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub2 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lua_chassis_stats(lua_State *L) {
    const char *plugin_name = NULL;
    chassis *chas = NULL;
    chassis_plugin *plugin = NULL;
    guint i = 0;
    gboolean found_stats = FALSE;
    int nargs = lua_gettop(L);

    if (nargs == 0) {
        plugin_name = NULL;
    } else if (nargs == 1) {        /* grab only the stats we were asked to fetch */
        plugin_name = luaL_checkstring(L, 1);
    } else {
        return luaL_argerror(L, 2, "currently only zero or one arguments are allowed");
    }
    lua_newtable(L);    /* the table for the stats, either containing sub tables or the stats for the single plugin requested */

    /* retrieve the chassis stored in the registry */
    lua_getfield(L, LUA_REGISTRYINDEX, CHASSIS_LUA_REGISTRY_KEY);
    chas = (chassis*) lua_topointer(L, -1);
    lua_pop(L, 1);

    /* get the global chassis stats */
    if (nargs == 0 && chas) {
        GHashTable *stats_hash = chassis_stats_get(chas->stats);
        if (stats_hash == NULL) {
            found_stats = FALSE;
        } else {
            found_stats = TRUE;

            lua_newtable(L);
            g_hash_table_foreach(stats_hash, chassis_stats_setluaval, L);
            lua_setfield(L, -2, "chassis");
            g_hash_table_destroy(stats_hash);
        }
    }

    if (chas && chas->modules) {
        for (i = 0; i < chas->modules->len; i++) {
            plugin = chas->modules->pdata[i];
            if (plugin->stats != NULL && plugin->get_stats != NULL) {
                GHashTable *stats_hash = NULL;
                
                if (plugin_name == NULL) {
                    /* grab all stats and key them by plugin name */
                    stats_hash = plugin->get_stats(plugin->stats);
                    if (stats_hash != NULL) {
                        found_stats = TRUE;
                    }
                    /* the per-plugin table */
                    lua_newtable(L);
                    g_hash_table_foreach(stats_hash, chassis_stats_setluaval, L);
                    lua_setfield(L, -2, plugin->name);
                    
                    g_hash_table_destroy(stats_hash);
                    
                } else if (g_ascii_strcasecmp(plugin_name, "chassis") == 0) {
                  /* get the global chassis stats */
                    stats_hash = chassis_stats_get(chas->stats);
                    if (stats_hash == NULL) {
                        found_stats = FALSE;
                        break;
                    }
                    found_stats = TRUE;

                    g_hash_table_foreach(stats_hash, chassis_stats_setluaval, L);
                    g_hash_table_destroy(stats_hash);
                    break;
                } else if (g_ascii_strcasecmp(plugin_name, plugin->name) == 0) {
                    /* check for the correct name and get the stats */
                    stats_hash = plugin->get_stats(plugin->stats);
                    if (stats_hash == NULL) {
                        found_stats = FALSE;
                        break;
                    }
                    found_stats = TRUE;
                    
                    /* the table to use is already on the stack */
                    g_hash_table_foreach(stats_hash, chassis_stats_setluaval, L);
                    g_hash_table_destroy(stats_hash);
                    break;
                }
            }
        }
    }
    /* can also be FALSE if we couldn't find the chassis */
    if (!found_stats) {
        lua_pop(L, 1);  /* pop the unused stats table */
        lua_pushnil(L);
        return 1;
    }
    return 1;
}