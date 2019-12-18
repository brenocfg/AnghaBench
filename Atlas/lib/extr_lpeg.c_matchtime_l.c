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
typedef  int /*<<< orphan*/  Instruction ;

/* Variables and functions */
 int /*<<< orphan*/  Cclose ; 
 int /*<<< orphan*/  Cruntime ; 
 int /*<<< orphan*/  ICloseRunTime ; 
 int /*<<< orphan*/  IOpenCapture ; 
 int /*<<< orphan*/  LUA_TFUNCTION ; 
 int /*<<< orphan*/  addpatt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int getpattl (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * newpatt (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  optimizecaptures (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setinstcap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  value2fenv (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int matchtime_l (lua_State *L) {
  int l1 = getpattl(L, 1);
  Instruction *op = newpatt(L, 1 + l1 + 1);
  Instruction *p = op;
  luaL_checktype(L, 2, LUA_TFUNCTION);
  setinstcap(p++, IOpenCapture, value2fenv(L, 2), Cruntime, 0);
  p += addpatt(L, p, 1);
  setinstcap(p, ICloseRunTime, 0, Cclose, 0);
  optimizecaptures(op);
  return 1;
}