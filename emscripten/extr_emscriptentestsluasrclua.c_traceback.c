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
 int /*<<< orphan*/  luaL_callmeta (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  luaL_traceback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  lua_isnoneornil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int traceback (lua_State *L) {
  const char *msg = lua_tostring(L, 1);
  if (msg)
    luaL_traceback(L, L, msg, 1);
  else if (!lua_isnoneornil(L, 1)) {  /* is there an error object? */
    if (!luaL_callmeta(L, 1, "__tostring"))  /* try its 'tostring' metamethod */
      lua_pushliteral(L, "(no error message)");
  }
  return 1;
}