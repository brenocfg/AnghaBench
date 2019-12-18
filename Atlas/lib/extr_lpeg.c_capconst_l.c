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
 int /*<<< orphan*/  Cconst ; 
 int /*<<< orphan*/  IEmptyCaptureIdx ; 
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawseti (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfenv (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * newpatt (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  setinstcap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int capconst_l (lua_State *L) {
  int i, j;
  int n = lua_gettop(L);
  Instruction *p = newpatt(L, n);
  lua_createtable(L, n, 0);  /* new environment for the new pattern */
  for (i = j = 1; i <= n; i++) {
    if (lua_isnil(L, i))
      setinstcap(p++, IEmptyCaptureIdx, 0, Cconst, 0);
    else {
      setinstcap(p++, IEmptyCaptureIdx, j, Cconst, 0);
      lua_pushvalue(L, i);
      lua_rawseti(L, -2, j++);
    }
  }
  lua_setfenv(L, -2);   /* set environment */
  return 1;
}