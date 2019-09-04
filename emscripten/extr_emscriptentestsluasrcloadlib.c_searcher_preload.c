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
 int LUA_REGISTRYINDEX ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char const*) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushfstring (int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static int searcher_preload (lua_State *L) {
  const char *name = luaL_checkstring(L, 1);
  lua_getfield(L, LUA_REGISTRYINDEX, "_PRELOAD");
  lua_getfield(L, -1, name);
  if (lua_isnil(L, -1))  /* not found? */
    lua_pushfstring(L, "\n\tno field package.preload['%s']", name);
  return 1;
}