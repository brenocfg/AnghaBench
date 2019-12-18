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
 int /*<<< orphan*/  lua_chassis_log_message ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static void remap_print(lua_State *L) {
	int n = lua_gettop(L);

	lua_getglobal(L, "os"); /* sp = 1 */
	lua_getglobal(L, "print"); /* sp = 2 */
	lua_setfield(L, -2, "print"); /* sp = 1*/
    lua_pop(L, 1); /* table os. sp = 0*/
	
	lua_register(L, "print", lua_chassis_log_message);
	
	g_assert(n == lua_gettop(L));
}