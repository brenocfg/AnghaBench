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
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GPtrArray ;

/* Variables and functions */
 int /*<<< orphan*/ * g_ptr_array_index (int /*<<< orphan*/ *,int) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ luaL_checkself (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int proxy_pwds_get(lua_State *L) {
	GPtrArray *raw_pwds = *(GPtrArray **)luaL_checkself(L);
	int index = luaL_checkinteger(L, 2) - 1; /** lua is indexes from 1, C from 0 */
	gchar *user_pwd = g_ptr_array_index(raw_pwds, index);
	lua_pushlstring(L, user_pwd, strlen(user_pwd));
	return 1;
}