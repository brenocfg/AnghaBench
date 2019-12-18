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
typedef  scalar_t__ lua_Integer ;
typedef  int /*<<< orphan*/  Instruction ;
typedef  int /*<<< orphan*/  Capture ;

/* Variables and functions */
 int IMAXCAPTURES ; 
 int /*<<< orphan*/  SUBJIDX ; 
 int getcaptures (int /*<<< orphan*/ *,char const*,char const*,int) ; 
 int /*<<< orphan*/ * getpatt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*) ; 
 scalar_t__ luaL_optinteger (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_getfenv (int /*<<< orphan*/ *,int) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 char* match (int /*<<< orphan*/ *,char const*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int matchl (lua_State *L) {
  Capture capture[IMAXCAPTURES];
  const char *r;
  size_t l;
  Instruction *p = getpatt(L, 1, NULL);
  const char *s = luaL_checklstring(L, SUBJIDX, &l);
  int ptop = lua_gettop(L);
  lua_Integer ii = luaL_optinteger(L, 3, 1);
  size_t i = (ii > 0) ?
             (((size_t)ii <= l) ? (size_t)ii - 1 : l) :
             (((size_t)-ii <= l) ? l - ((size_t)-ii) : 0);
  lua_pushnil(L);  /* subscache */
  lua_pushlightuserdata(L, capture);  /* caplistidx */
  lua_getfenv(L, 1);  /* penvidx */
  r = match(L, s, s + i, s + l, p, capture, ptop);
  if (r == NULL) {
    lua_pushnil(L);
    return 1;
  }
  return getcaptures(L, s, r, ptop);
}