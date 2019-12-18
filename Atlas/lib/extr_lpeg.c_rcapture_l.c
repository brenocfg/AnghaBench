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
 int /*<<< orphan*/  Cfunction ; 
 int /*<<< orphan*/  Cquery ; 
 int /*<<< orphan*/  Cstring ; 
#define  LUA_TFUNCTION 130 
#define  LUA_TSTRING 129 
#define  LUA_TTABLE 128 
 int capture_aux (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int luaL_argerror (int /*<<< orphan*/ *,int,char*) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int rcapture_l (lua_State *L) {
  switch (lua_type(L, 2)) {
    case LUA_TFUNCTION: return capture_aux(L, Cfunction, 2);
    case LUA_TTABLE: return capture_aux(L, Cquery, 2);
    case LUA_TSTRING: return capture_aux(L, Cstring, 2);
    default: return luaL_argerror(L, 2, "invalid replacement value");
  }
}