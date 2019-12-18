#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  scalar_t__ guint ;
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_3__ {scalar_t__ len; } ;
typedef  TYPE_1__ GPtrArray ;

/* Variables and functions */
 int /*<<< orphan*/  g_ptr_array_index (TYPE_1__*,scalar_t__) ; 
 scalar_t__ luaL_checkself (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * lua_tostring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proxy_clients_exist(lua_State *L) {
	GPtrArray *raw_ips = *(GPtrArray **)luaL_checkself(L);
	gchar *client = lua_tostring(L, -1);
	guint i;
	for (i = 0; i < raw_ips->len; ++i) {
		if (strcmp(client, g_ptr_array_index(raw_ips, i)) == 0) {
			lua_pushinteger(L, 1);
			return 1;
		}
	}
	lua_pushinteger(L, 0);
	return 1;
}