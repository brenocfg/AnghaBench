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
 int luaL_error (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_getfenv (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_gettable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int,int) ; 
 int lua_tointeger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  val2str (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int getposition (lua_State *L, int t, int i) {
  int res;
  lua_getfenv(L, -1);
  lua_rawgeti(L, -1, i);  /* get key from pattern's environment */
  lua_gettable(L, t);  /* get position from positions table */
  res = lua_tointeger(L, -1);
  if (res == 0) {  /* key has no registered position? */
    lua_rawgeti(L, -2, i);  /* get key again */
    return luaL_error(L, "%s is not defined in given grammar", val2str(L, -1));
  }
  lua_pop(L, 2);  /* remove environment and position */
  return res;
}