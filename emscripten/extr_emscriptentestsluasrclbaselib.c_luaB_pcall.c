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
 int /*<<< orphan*/  LUA_MULTRET ; 
 int LUA_OK ; 
 int finishpcall (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_checkany (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_insert (int /*<<< orphan*/ *,int) ; 
 int lua_pcallk (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcallcont ; 

__attribute__((used)) static int luaB_pcall (lua_State *L) {
  int status;
  luaL_checkany(L, 1);
  lua_pushnil(L);
  lua_insert(L, 1);  /* create space for status result */
  status = lua_pcallk(L, lua_gettop(L) - 2, LUA_MULTRET, 0, 0, pcallcont);
  return finishpcall(L, (status == LUA_OK));
}