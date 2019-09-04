#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int nups; } ;
typedef  TYPE_1__ lua_Debug ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_TFUNCTION ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 int luaL_checkint (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_getinfo (int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int checkupval (lua_State *L, int argf, int argnup) {
  lua_Debug ar;
  int nup = luaL_checkint(L, argnup);
  luaL_checktype(L, argf, LUA_TFUNCTION);
  lua_pushvalue(L, argf);
  lua_getinfo(L, ">u", &ar);
  luaL_argcheck(L, 1 <= nup && nup <= ar.nups, argnup, "invalid upvalue index");
  return nup;
}