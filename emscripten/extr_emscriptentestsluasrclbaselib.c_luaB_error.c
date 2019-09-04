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
 int luaL_optint (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  luaL_where (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_concat (int /*<<< orphan*/ *,int) ; 
 int lua_error (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_isstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int luaB_error (lua_State *L) {
  int level = luaL_optint(L, 2, 1);
  lua_settop(L, 1);
  if (lua_isstring(L, 1) && level > 0) {  /* add extra information? */
    luaL_where(L, level);
    lua_pushvalue(L, 1);
    lua_concat(L, 2);
  }
  return lua_error(L);
}