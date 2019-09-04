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
typedef  int b_uint ;

/* Variables and functions */
 int ALLONES ; 
 int LUA_NBITS ; 
 int b_shift (int /*<<< orphan*/ *,int,int) ; 
 int luaL_checkint (int /*<<< orphan*/ *,int) ; 
 int luaL_checkunsigned (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushunsigned (int /*<<< orphan*/ *,int) ; 
 int trim (int) ; 

__attribute__((used)) static int b_arshift (lua_State *L) {
  b_uint r = luaL_checkunsigned(L, 1);
  int i = luaL_checkint(L, 2);
  if (i < 0 || !(r & ((b_uint)1 << (LUA_NBITS - 1))))
    return b_shift(L, r, -i);
  else {  /* arithmetic shift for 'negative' number */
    if (i >= LUA_NBITS) r = ALLONES;
    else
      r = trim((r >> i) | ~(~(b_uint)0 >> i));  /* add signal bit */
    lua_pushunsigned(L, r);
    return 1;
  }
}