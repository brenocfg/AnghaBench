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
 int /*<<< orphan*/  LUA_ENVIRONINDEX ; 
 int /*<<< orphan*/  PATTERN_T ; 
 int /*<<< orphan*/  luaL_newmetatable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_replace (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_settable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  metapattreg ; 
 int /*<<< orphan*/  pattreg ; 

int luaopen_lpeg (lua_State *L) {
  lua_newtable(L);
  lua_replace(L, LUA_ENVIRONINDEX);  /* empty env for new patterns */
  luaL_newmetatable(L, PATTERN_T);
  luaL_register(L, NULL, metapattreg);
  luaL_register(L, "lpeg", pattreg);
  lua_pushliteral(L, "__index");
  lua_pushvalue(L, -2);
  lua_settable(L, -4);
  return 1;
}