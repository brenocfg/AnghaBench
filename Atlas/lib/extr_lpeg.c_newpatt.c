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
 int /*<<< orphan*/  IEnd ; 
 int MAXPATTSIZE ; 
 int /*<<< orphan*/  PATTERN_T ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaL_getmetatable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_newuserdata (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  setinst (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Instruction *newpatt (lua_State *L, size_t n) {
  Instruction *p;
  if (n >= MAXPATTSIZE - 1)
    luaL_error(L, "pattern too big");
  p = (Instruction *)lua_newuserdata(L, (n + 1) * sizeof(Instruction));
  luaL_getmetatable(L, PATTERN_T);
  lua_setmetatable(L, -2);
  setinst(p + n, IEnd, 0);
  return p;
}