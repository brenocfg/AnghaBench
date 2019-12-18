#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_11__ {scalar_t__ code; int offset; } ;
struct TYPE_12__ {TYPE_1__ i; } ;
typedef  TYPE_2__ Instruction ;

/* Variables and functions */
 scalar_t__ ICall ; 
 scalar_t__ IJmp ; 
 scalar_t__ IOpenCall ; 
 scalar_t__ IRet ; 
 int /*<<< orphan*/  LUA_MINSTACK ; 
 int MAXPATTSIZE ; 
 int /*<<< orphan*/  addpatt (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  checkrule (int /*<<< orphan*/ *,TYPE_2__*,int,int,int,int) ; 
 int getposition (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 int /*<<< orphan*/  luaL_checkstack (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_gettable (int /*<<< orphan*/ *,int) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_insert (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_next (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_replace (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 int lua_tonumber (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* newpatt (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  optimizejumps (TYPE_2__*) ; 
 int pattsize (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  setinst (TYPE_2__*,scalar_t__,int) ; 
 scalar_t__ sizei (TYPE_2__*) ; 
 size_t target (TYPE_2__*,int) ; 
 int /*<<< orphan*/  testpattern (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static Instruction *fix_l (lua_State *L, int t) {
  Instruction *p;
  int i;
  int totalsize = 2;  /* include initial call and jump */
  int n = 0;  /* number of rules */
  int base = lua_gettop(L);
  lua_newtable(L);  /* to store relative positions of each rule */
  lua_pushinteger(L, 1);  /* default initial rule */
  /* collect patterns and compute sizes */
  lua_pushnil(L);
  while (lua_next(L, t) != 0) {
    int l;
    if (lua_tonumber(L, -2) == 1 && lua_isstring(L, -1)) {
      lua_replace(L, base + 2);  /* use this value as initial rule */
      continue;
    }
    if (!testpattern(L, -1))
      luaL_error(L, "invalid field in grammar");
    l = pattsize(L, -1) + 1;  /* space for pattern + ret */
    if (totalsize >= MAXPATTSIZE - l)
      luaL_error(L, "grammar too large");
    luaL_checkstack(L, LUA_MINSTACK, "grammar has too many rules");
    lua_insert(L, -2);  /* put key on top */
    lua_pushvalue(L, -1);  /* duplicate key (for lua_next) */
    lua_pushvalue(L, -1);  /* duplicate key (to index positions table)) */
    lua_pushinteger(L, totalsize);  /* position for this rule */
    lua_settable(L, base + 1);  /* store key=>position in positions table */
    totalsize += l;
    n++;
  }
  luaL_argcheck(L, n > 0, t, "empty grammar");
  p = newpatt(L, totalsize);  /* create new pattern */
  p++;  /* save space for call */
  setinst(p++, IJmp, totalsize - 1);  /* after call, jumps to the end */
  for (i = 1; i <= n; i++) {  /* copy all rules into new pattern */
    p += addpatt(L, p, base + 1 + i*2);
    setinst(p++, IRet, 0);
  }
  p -= totalsize;  /* back to first position */
  totalsize = 2;  /* go through each rule's position */
  for (i = 1; i <= n; i++) {  /* check all rules */
    int l = pattsize(L, base + 1 + i*2) + 1;
    checkrule(L, p, totalsize, totalsize + l, base + 1, base + 2 + i*2);
    totalsize += l;
  }
  lua_pushvalue(L, base + 2);  /* get initial rule */
  lua_gettable(L, base + 1);  /* get its position in postions table */
  i = lua_tonumber(L, -1);  /* convert to number */
  lua_pop(L, 1);
  if (i == 0)  /* is it defined? */
    luaL_error(L, "initial rule not defined in given grammar");
  setinst(p, ICall, i);  /* first instruction calls initial rule */
  /* correct calls */
  for (i = 0; i < totalsize; i += sizei(p + i)) {
    if (p[i].i.code == IOpenCall) {
      int pos = getposition(L, base + 1, p[i].i.offset);
      p[i].i.code = (p[target(p, i + 1)].i.code == IRet) ? IJmp : ICall;
      p[i].i.offset = pos - i;
    }
  }
  optimizejumps(p);
  lua_replace(L, t);  /* put new pattern in old's position */
  lua_settop(L, base);  /* remove rules and positions table */
  return p;
}