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
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  guint ;
typedef  void* gpointer ;
typedef  int /*<<< orphan*/  gchar ;

/* Variables and functions */
 int /*<<< orphan*/  GPOINTER_TO_UINT (void*) ; 
 int /*<<< orphan*/  g_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_checkstack (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_istable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  lua_settable (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void chassis_stats_setluaval(gpointer key, gpointer val, gpointer userdata) {
    const gchar *name = key;
    const guint value = GPOINTER_TO_UINT(val);
    lua_State *L = userdata;

    g_assert(lua_istable(L, -1));
    lua_checkstack(L, 2);

    lua_pushstring(L, name);
    lua_pushinteger(L, value);
    lua_settable(L, -3);
}