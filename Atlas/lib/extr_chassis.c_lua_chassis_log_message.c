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

/* Variables and functions */
 int /*<<< orphan*/  g_assert (int) ; 
 int lua_chassis_log (int /*<<< orphan*/ *) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_insert (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_remove (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int lua_chassis_log_message(lua_State *L) {
	int n = lua_gettop(L);
	int retval;
	lua_pushliteral(L, "message");
	lua_insert(L, 1);
	retval = lua_chassis_log(L);
	lua_remove(L, 1);
	g_assert(n == lua_gettop(L));
	return retval;
}