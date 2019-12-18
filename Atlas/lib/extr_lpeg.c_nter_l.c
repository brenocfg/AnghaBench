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
 int /*<<< orphan*/  IOpenCall ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 int /*<<< orphan*/  lua_isnoneornil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * newpatt (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  setinst (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  value2fenv (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int nter_l (lua_State *L) {
  Instruction *p;
  luaL_argcheck(L, !lua_isnoneornil(L, 1), 1, "non-nil value expected");
  p = newpatt(L, 1);
  setinst(p, IOpenCall, value2fenv(L, 1));
  return 1;
}